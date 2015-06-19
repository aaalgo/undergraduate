/**
  * \file group.c
  * \author J.Zhao 2004/09/12 
  */
#include <argus.h>

struct group_aggre
{
	int 	fieldID;/* field index*/
	aggre_t *aggre;	/* aggre struc*/ 
};

/* hash table's bucket */
typedef struct bucket
{
	// tuple number
	int	tupleNum;
	
	// group by fields
	char	*groupFields;
	
	// aggregate result
	void	**aggreResult;
		
	// open hash's next node	
	struct	bucket *next;

	// recent tuple information
	int	tupleID;	// tuple ID
	tuple_t	*pTup;		// tuple pointer

	// status information
	int ins_ok;

	// change tag
	int changed;
	
	
	
}bucket_t;

/* group operator information */
struct group
{
	// operator
	operator_t opr;

	/* output tuple schema	*/
	schema_t *outSchema;
	
	/* input tuple schema	*/
	schema_t *inSchema;
		
	/* number of grouped fields*/
	int groupFieldNum;
	
	/* array of grouped fields */
	int *groupFieldIndex;

	/* group field total size  */
	int groupFieldSize;
	
	/* number of aggregations  */
	int aggreNum;
	
	/* aggretation information */
	struct group_aggre *aggreInfo;
	
	// define hash table
	bucket_t *hashTable[AGG_HAS_BUCNUM];
};

unsigned hash(struct group *group_op,tuple_t *tup)
{
	// define and initialize hash value
	unsigned hashValue = 0;

	// define help variable	
	int fieldID = 0;
	
	int fieldIndex = 0;
	
	unsigned (*field_hash)(void *) = NULL;
	
	void *pField_Value = NULL;

	type_t *field_type = NULL;
	
	// calculate hash value
	for(fieldID = 0; fieldID < group_op->groupFieldNum; fieldID++)
	{
		// get field index
		fieldIndex = group_op->groupFieldIndex[fieldID];
		
		if(fieldIndex >= group_op->inSchema->nof)
		{
			assert(0);
		}
		
		// get field type
		field_type = group_op->inSchema->field[fieldIndex].type;

		// get hash function
		field_hash = field_type->hash;
		
		// get value pointer
		pField_Value = (void *)&(tup->data[group_op->inSchema->field[fieldIndex].offset]);
		
		// hash the value
		hashValue += field_hash(pField_Value);		
	}

	hashValue = hashValue % AGG_HAS_BUCNUM;

	// return hash value
	return hashValue;
}

bucket_t *findBucket(struct group *group_op,tuple_t *tup, unsigned hashValue)
{
	// define help variable
	bucket_t *pBucket = NULL;

	int find = 0;

	int fieldIndex = 0;

	int fieldID = 0;

	type_t *pType = NULL;

	void *pValue1 = NULL;

	void *pValue2 = NULL;

	// get bucket pointer
	pBucket = group_op->hashTable[hashValue];
	
	// find bucket
	while(pBucket != NULL)
	{
		find = 1;
		
		// check all the group by fields	
		for(fieldID = 0 ; fieldID < group_op->groupFieldNum ; fieldID++)
		{
			// a field index of input tuple
			fieldIndex = group_op->groupFieldIndex[fieldID];
				
			// a type of specified field
			pType = group_op->inSchema->field[fieldIndex].type;

			// value pointer in input tuple
			pValue1 = (void *)&(tup->data[group_op->inSchema->field[fieldIndex].offset]);
		
			// value pointer in output tuple
			pValue2 = (void *)&(pBucket->groupFields[group_op->outSchema->field[fieldID].offset]);
			
			// compare specified field 	
			if(pType->comp(pValue1,pValue2) != 0)
			{
				find = 0;

				break;
			}	
		}
			
		// find the bucket
		if(find == 1)
		{
			return pBucket;
		}

		pBucket = pBucket->next;
	}
	
	// not found
	return NULL;
}

int processTuple(struct group *group_op,int type,tuple_t *tup)
{
	// define help variables
	size_t i = 0;

	int j = 0;
	
	unsigned hashValue = 0;

	bucket_t *pBucket = NULL;

	int fieldIndex = 0;

	int fieldID = 0;

	type_t *pType = NULL;

	void *pValue1 = NULL;

	void *pValue2 = NULL;

	// get hash value
	hashValue = hash(group_op,tup);

	// find bucket
	pBucket = findBucket(group_op,tup,hashValue);

	// no specified bucket
	if(pBucket == NULL)
	{
		if(type == TUPLE_INS)
		{
			// create new bucket
			pBucket = type_alloc(bucket_t);

			// assign tuple number for new bucket;
			pBucket->tupleNum = 1;

			// assign group by fields for new bucket
			pBucket->groupFields = type_calloc(group_op->groupFieldSize,char);
			
			for(fieldID = 0 ; fieldID < group_op->groupFieldNum ; fieldID++)
			{
				// a field index of input tuple
				fieldIndex = group_op->groupFieldIndex[fieldID];
				
				// a type of specified field
				pType = group_op->inSchema->field[fieldIndex].type;

				// value pointer in input tuple
				pValue1 = (void *)&(tup->data[group_op->inSchema->field[fieldIndex].offset]);
		
				// value pointer in output tuple
				pValue2 = (void *)&(pBucket->groupFields[group_op->outSchema->field[fieldID].offset]);
			
				// copy specified field 	
				if(pType->copy != NULL)
				{
					pType->copy(pValue2,pValue1);
				}	
				else 
				{
					memcpy(pValue2, pValue1, pType->size);
				}
			}			

			// assign value for aggregate result
			pBucket->aggreResult = type_calloc(group_op->aggreNum,void *);

			for(j = 0 ; j < group_op->aggreNum ; j++)
			{
				pBucket->aggreResult[j] = group_op->aggreInfo[j].aggre->init();

				group_op->aggreInfo[j].aggre->update(pBucket->aggreResult[j],&(tup->data[group_op->inSchema->field[group_op->aggreInfo[j].fieldID].offset]),TUPLE_INS);
			}

			// assign vlaue for new tuple information
			pBucket->tupleID = -1;
			pBucket->pTup = NULL;

			pBucket->ins_ok = 0;
			pBucket->changed = 1;

			// attatch the bucket
			pBucket->next = group_op->hashTable[hashValue];

			group_op->hashTable[hashValue] = pBucket;	

			// release tuple
			tuple_unlock(tup);
		}
		// invalid tuple type
		else
		{
			assert(0);
		}
			
	}
	else // pBucket != NULL
	{
		if(type == TUPLE_INS)
		{
			// change tuple number
			pBucket->tupleNum++;
		}
		else if(type == TUPLE_DEL)
		{
			if(pBucket->tupleNum == 0)
			{
				assert(0);
			}
			else
			{
				// change tuple number
				pBucket->tupleNum--;
			}
		}
		else
		{
			assert(0);
		}

		// update aggregate result
		for(j = 0 ; j < group_op->aggreNum ; j++)
		{
			group_op->aggreInfo[j].aggre->update(pBucket->aggreResult[j],&(tup->data[group_op->inSchema->field[group_op->aggreInfo[j].fieldID].offset]),type);
		}

		// set changed tag
		pBucket->changed = 1;	

		// release tuple
		tuple_unlock(tup);	
	}
	
	return 0;
}

tuple_t *buildTuple(struct group *group_op,bucket_t *pBucket)
{
	// define tuple pointer
	tuple_t *pTuple = NULL;

	int fieldID = 0;

	type_t *pType = NULL;

	void *pValue1 = NULL;

	void *pValue2 = NULL;

	size_t i = 0;	

	// allocate memory for tuple
	pTuple = tuple_alloc(schema_data_size(group_op->outSchema), group_op->outSchema);

	// copy group by field data
	for(fieldID = 0 ; fieldID < group_op->groupFieldNum ; fieldID++)
	{
		// a type of specified field
		pType = group_op->outSchema->field[fieldID].type;

		// value pointer in bucket output tuple
		pValue1 = (void *)&(pBucket->groupFields[group_op->outSchema->field[fieldID].offset]);
		
		// value pointer in direct output tuple
		pValue2 = (void *)&(pTuple->data[group_op->outSchema->field[fieldID].offset]);
			
		// copy specified field 	
		if(pType->copy != NULL)
		{
			pType->copy(pValue2,pValue1);
		}	
		else 
		{
			memcpy(pValue2, pValue1, pType->size);
		}		
	}

	// copy aggregate field data
	for(fieldID = 0 ; fieldID < group_op->aggreNum ; fieldID++)
	{
		// a type of specified field
		pType = group_op->outSchema->field[fieldID + group_op->groupFieldNum].type;

		// value pointer in bucket output tuple
		pValue1 = pBucket->aggreResult[fieldID];
		
		// value pointer in direct output tuple
		pValue2 = (void *)&(pTuple->data[group_op->outSchema->field[fieldID + group_op->groupFieldNum].offset]);
			
		// copy specified field 
		group_op->aggreInfo[fieldID].aggre->value(pValue1, pValue2);
	}	

	// return tuple pointer
	return pTuple;
	
}

int updateResult(struct group *group_op, int time)
{
	// define help variable
	int i = 0;
	int j = 0;

	bucket_t *pTemp  = NULL;
	tuple_t * pTuple = NULL;

	// traverse hash table
	for(i = 0 ; i < AGG_HAS_BUCNUM ; i++)
	{
		pTemp = group_op->hashTable[i];

		while(pTemp != NULL)
		{
			// processe changed bucket
			if(pTemp->changed == 1)
			{
				// IStream tuple has not been dispatched
				if((pTemp->ins_ok == 0))
				{
					// tuple number is zero
					if(pTemp->tupleNum == 0)
					{
						// nothing to do	
					}
					// tuple number > 0
					else
					{
						// build new tuple
						pTuple = buildTuple(group_op,pTemp);
						
						// dispatch TUPLE_INS
						tuple_lock(pTuple);
						dispatch_tuple(group_op->opr.schedopr,TUPLE_INS, time, pTuple);

						// set status information
						pTemp->ins_ok = 1;
						pTemp->tupleID = pTuple->id;
						if (pTemp->pTup != NULL) tuple_unlock(pTemp->pTup);
						pTemp->pTup = pTuple;
					}					
				}
				// IStream tuple has not been dispatched
				else if((pTemp->ins_ok == 1))
				{
					// tuple number is zero
					if(pTemp->tupleNum == 0)
					{
						// dispatch TUPLE_DEL
						dispatch_tuple(group_op->opr.schedopr,TUPLE_DEL, time, pTemp->pTup);						
						// reset status information
						pTemp->ins_ok = 0;
						pTemp->tupleID = -1;
						pTemp->pTup = NULL;
					}
					// tuple number > 0
					else
					{
						// build a new tuple
						pTuple = buildTuple(group_op,pTemp);
						pTuple->id = pTemp->tupleID;

						// set new current tuple
						tuple_unlock(pTemp->pTup);
						pTemp->pTup = pTuple;

						// dispatch TUPLE_REPLACE tuple
						tuple_lock(pTuple);
						dispatch_tuple(group_op->opr.schedopr,TUPLE_REPLACE, time, pTuple);					
					}					
					
				}
				// invalid status
				else
				{
					assert(0);
				}

				// reset change signal
				pTemp->changed = 0;
			}
			// move to next bucket
			pTemp = pTemp->next;
		}
	}

	return 0;
}

int cleanResult(struct group *group_op, int time)
{
	// define help variable
	int i = 0;
	int j = 0;
	
	bucket_t *pTemp = NULL;

	// traverse hash table
	for(i = 0 ; i < AGG_HAS_BUCNUM ; i++)
	{
		pTemp = group_op->hashTable[i];
		
		while(pTemp != NULL)
		{
			// reset information
			pTemp->tupleNum = 0;
			pTemp->tupleID	= -1;
			if (pTemp->pTup) tuple_unlock(pTemp->pTup);	
			pTemp->pTup	= NULL;
			pTemp->ins_ok  = 0;
			pTemp->changed = 0;

			// reset aggregate information
			for(j = 0 ; j < group_op->aggreNum ; j++)
			{
				// delete aggregate result
				group_op->aggreInfo[j].aggre->cleanup(pTemp->aggreResult[j]);

				// initialize aggrgate result
				pTemp->aggreResult[j] = group_op->aggreInfo[j].aggre->init();
			}
			// move to open hash's next bucket
			pTemp = pTemp->next;
		}
	}

	// dispatch clean signal
	dispatch_tuple(group_op->opr.schedopr,TUPLE_CLEAN, time, NULL);

	return 0;
}

int group_receive(struct group *group_op,int type, int time, tuple_t *tup)
{
	if(type & TUPLE_ADDED)
	{
		//nothing to do
	}

	// process insert tuple
	if(type & TUPLE_INS)
	{
		processTuple(group_op,TUPLE_INS,tup);	
	}
	
	// process delete tuple
	if(type & TUPLE_DEL)
	{
		processTuple(group_op,TUPLE_DEL,tup);
	}

	// process update signal
	if(type & TUPLE_UPDATE)
	{
		updateResult(group_op, time);
	}

	// process clean signal
	if(type & TUPLE_CLEAN)
	{
		cleanResult(group_op, time);
	}
	
	return 0;
}

int group_destroy(struct group *pGroup)
{
	// define help variable
	int i = 0;
	int j = 0;
	
	bucket_t *pTemp  = NULL;
	bucket_t *pTemp2 = NULL;
	
	// free bucket memory inside hash table	
	for(i = 0 ; i < AGG_HAS_BUCNUM ; i++)
	{
		pTemp = pGroup->hashTable[i];
		
		while(pTemp != NULL)
		{
			pTemp2 = pTemp->next;
			
			free(pTemp->groupFields);
			
			for(j = 0 ; j < pGroup->aggreNum ; j++)
			{
				pGroup->aggreInfo[j].aggre->cleanup(pTemp->aggreResult[j]);
			}
			
			free(pTemp->aggreResult);
			
			// unlock tuple 
			if(pTemp->pTup != NULL)
			{
				tuple_unlock(pTemp->pTup);
			}
			
			free(pTemp);
			
			pTemp = pTemp2;
		}
	}
	// free memory inside operator
	free(pGroup->groupFieldIndex);
	free(pGroup->aggreInfo);
	free(pGroup->inSchema);
	free(pGroup->outSchema);
	// free group operator
	free(pGroup);
	
	return 0;
}

operator_t *group_create (
		schema_t *outSchema,		/* output tuple schema		*/
		schema_t *inSchema,		/* input tuple schema		*/
/*		int	groupFieldNum,		number of grouped fields	*/
/*		int	groupFieldIndex[],	array of grouped fields	*/
		lnode_t groupField,		/* a linked list of grouped fields */
/*		int	aggreNum,		number of aggretations	*/
/*		struct	group_aggre aggreInfo[]	aggregation information	*/
		lnode_t aggreField		/* a linked list of aggre fields */
		)
{
	int groupFieldNum = llist_count(groupField);
	int aggreNum = llist_count(aggreField);
	/* the in passed lnode_t is the head node of the link list,
	 * the actual first node of the list is the next node pointed to by
	 * the head node */
	struct sql_group *grp = (struct sql_group *)llist_next(groupField);
	struct sql_aggre *agg = (struct sql_aggre *)llist_next(aggreField);
	// define help variable
	int i = 0;

	// define group operator pointer
	struct group *pGroup = NULL;
	
	// allocate memory for group operator
	pGroup = type_alloc(struct group);
	
	// set receive function and destroy function for group operator
	pGroup->opr.receive = (operator_receive_f)group_receive;
	pGroup->opr.destroy = (operator_destroy_f)group_destroy;
	
	// initialize operator information
	pGroup->groupFieldNum = groupFieldNum;
	pGroup->aggreNum = aggreNum;
	
	pGroup->groupFieldIndex = type_calloc(groupFieldNum,int);
	pGroup->aggreInfo = type_calloc(aggreNum,struct group_aggre);

/* Modified by Dong Wei, changing from array to linked list */	
	i = 0;
	while (grp != NULL)
	{
		pGroup->groupFieldIndex[i] = grp->field;
		grp = (struct sql_group *)llist_next(grp->link);
		i++;
	}
	assert(i == pGroup->groupFieldNum);

	i = 0;
	while (agg != NULL)
	{
		pGroup->aggreInfo[i].fieldID = agg->field;
		pGroup->aggreInfo[i].aggre = agg->aggre;
		agg = (struct sql_aggre *)llist_next(agg->link);
		i++;
	}
	assert(i == pGroup->aggreNum);
	
	pGroup->inSchema  = schema_dup(inSchema);
	pGroup->outSchema = schema_dup(outSchema);

	// calculate group fields size
	pGroup->groupFieldSize = 0;
	
	for(i = 0 ; i < groupFieldNum ; i++)
	{
		pGroup->groupFieldSize += inSchema->field[pGroup->groupFieldIndex[i]].type->size;	
	}
	
	// initialize hash table
	for(i = 0 ; i< AGG_HAS_BUCNUM ; i++)
	{
		pGroup->hashTable[i] = NULL;
	}
	
	// return group operator pointer
	return (operator_t *)pGroup;	
}
