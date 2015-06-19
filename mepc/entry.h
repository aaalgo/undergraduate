/**
  * \file entry.h
  * \author Dong Wei
  * 
  * Header file for symbol table entry definition.
  * everything that has a symbol, including constants, variables, types,
  * fields of a record, parameters ..., is describled with entry_t.
  * As a result, entry_t contains a flag indicating the type of the entry,
  * and a large union of fields describing different objects.
  *   This file defines the entry structure and declares a list of 
  * construct functions for entries of different type.
  */

#ifndef __PASCAL_ENTRY__
#define __PASCAL_ENTRY__

/// entry for constants 
#define ENTRY_CONST	1
/// entry for data 
#define ENTRY_DATA	2
/// entry for local variables(located in stack) 
#define ENTRY_STACK	3
/// entry for record fields 
#define ENTRY_FIELD	4
/// entry for temporary variable 
#define ENTRY_TEMP	5
/// entry for labels 
#define ENTRY_LABEL	6
/// entry for ferences to variables 
#define ENTRY_REFERENCE	7
/// entry type is atomie, further distinguished by ATOMIC_xxx 
#define ENTRY_ATOMIC	8
/// entry type is scalor type. 
#define ENTRY_SCALAR	9
/// entry type is scalar of some type. 
#define ENTRY_SUBRANGE	10
/// entry type is array. 
#define ENTRY_ARRAY	11
/// entry type is record. 
#define ENTRY_RECORD	12
/// entry type is pointer. 
#define ENTRY_POINTER	13
/// unknown entry type. 
#define ENTRY_UNKNOWN	14
/// entry type is real. 
#define ENTRY_REAL	15
/// integer type 
#define ATOMIC_INTEGER	1
/// char type 
#define ATOMIC_CHAR	2
/// bool type 
#define ATOMIC_BOOL	3
/// pointer type 
#define ATOMIC_POINTER	4
/// real type 
#define ATOMIC_REAL	8
/// string type 
#define ATOMIC_STRING	9
/// entry for procedures 
#define ENTRY_PROCEDURE 20
/// entry for parameters 
#define ENTRY_PARAM	21
/// entry for result 
#define ENTRY_RESULT	22
/// parameter passed by value 
#define PARAM_BYVALUE	1
/// parameter passed by reference 
#define PARAM_BYREFERENCE 2
/// Pascal style procedure. 
/**
  * Pascal style procedure invokation here is somewhat difference from
  * the standard way. The parameter space is cleaned by the callee and
  * the parameters are passed from the right to the left.
  */
  
#define PROCEDURE_PASCAL 1
/// c style procedure. 
/**
  * In the c style procedure invokation, the parameter space is revoked
  * by the caller.
  */
  
#define PROCEDURE_CDECL	2

/// The big symbol table entry struct. 
/** Everything that has a name in the Pascal language is
  * described by a symbol table entry. The type field indicates
  * the type of the entry, and the information of different type
  * of entry can be accessed by referring to the member of the
  * union field a.
  */
  
struct entry
{
	/// Link to the next field. 
	entry_t *next;
	/// Name of the entry. 
	char *name;
	/// Type of the entry. 
	int type;
	/// Further information. 
	int flag;
	/// Size of the entry. 
	int size;
	/// A big union of data for different types. 
	union
	{
		/// Data for constant entry. 
		struct
		{
			/// Pointer to the type entry. 
			entry_t *type;
			/// Pointer to the value. 
			expression_t *expr;
		} constant;
		/// Data for stack variable entry. 
		struct
		{
			/// Pointer to the type entry. 
			entry_t *type;
			int offset;
		} stack;
		/// Data for a record field. 
		struct
		{
			/// Pointer to the type entry. 
			entry_t *type;
			/// Offset of the field. 
			int offset;
		} field;
		/// Data for a procedure/function parameter. 
		struct
		{
			/// Pointer to the type entry. 
			entry_t *type;
			/// Offset of the parameter. 
			int offset;
		} param;
		/// Data for a temparary variable. 
		struct
		{
			/// Pointer to the type entry. 
			entry_t *type;
			/// Identifier of the variable. 
			/**
			  * Every temparary variable has a
			  * unique id.
			  * \see new_temp
			  */			  
			int id;
		} temp;
		/// Data for a label. 
		struct
		{	
			/// Identifier of the label. 
			/**
			  * Every label has a unique id.
			  * \see new_label.
			  */			  
			int label;
			/// Patch list. 
			/**
			  * For every label whose address has not been
			  * fixed, a patch list is maintained. The patch
			  * list of a label contains the addresses of
			  * the instructions that refers to this label
			  * (i.e. jumps to this label). When the address
			  * of the label is fixed, all instructions in 
			  * the patch list is patched using the address and
			  * then the patch list is freed.
			  */			  
			queue_t *queue;
		} label;
		/// Data for a atomic type. 
		struct
		{
			/// min value 
			int min;
			/// max value 
			int max;
			/// type of the entry 
			int type;
		} atomic;
		/// Data for a subrange type. 
		struct
		{
			/// The minimum value of the range. 
			int min;
			/// The maximum value of the range. 
			int max;
			/// base type 
			entry_t *base;
		} subrange;
		/// Data for a scalar type. 
		struct
		{
			/// The minimum value of the type. 
			int min;
			/// The maxmum value of the type. 
			int max;
		} scalar;
		/// Data for an array. 
		struct
		{
			/// Base address. 
			entry_t *base;
			/// A list of subscriptions. 
			queue_t *sub;
		} array;
		/// Data for record entry. 
		struct
		{
			/// Pointer to a list of record fields. 
			table_t *fields;
		} record;
		/// Data for procedure entry. 
		struct
		{
			/// Return type. 
			entry_t *rtype;
			/// Parameters(listed in a tabel). 
			table_t *param;
			/// Total size of the parameters. 
			int psize;
			/// The Procedure ID
			int id;
		} procedure;
	} a;
};

/// Free an entry. 
/**
  * Entries of all types are freed using this function.
  */
  
void entry_free (entry_t *entry);

/// Allocate an arbituary entry. 
entry_t *entry_alloc (void);

/// Allocate a real entry. 
static inline entry_t *real_alloc (char *name)
{
	entry_t *entry = entry_alloc();
	entry->type = ENTRY_REAL;
	entry->name = name;
	entry->flag = 0;
	entry->size = 8;
	return entry;
}

/// Allocate a constant entry. 
entry_t *const_alloc (char *name, expression_t *e);

/// Allocate an entry for a label. 
entry_t *label_alloc (char *name);

/// Allocate an entry of atomic type. 
entry_t *atomic_alloc (char *name, int type, int size, int min,
		int max);

/// Allocate an entry of subrange type. 
entry_t *subrange_alloc (expression_t *min, expression_t *max);

/// Allocate an entry of array type. 
entry_t *array_alloc(entry_t *base, queue_t *sub);

/// Allocate an entry of recored type. 
entry_t *record_alloc (table_t *fields);

/// Duplicate an entry. 
entry_t *entry_copy (entry_t *o);
#define type_copy entry_copy

/// Allocate an entry of scalar type. 
entry_t *scalar_alloc (queue_t *);

/// Allocate an entry for a scalar type element. 
expression_t *scalar_elem_alloc (entry_t *base, int value);

/// Allocate an entry for a record field. 
entry_t *field_alloc (entry_t *type, char *name, int offset);

/// Allocate an entry for a parameter. 
entry_t *param_alloc (entry_t *type, char *name, int offst, int flag);

/// Allocate an entry for a variable. 
entry_t *variable_alloc (entry_t *type, char *name, int offset);

/// Allocate an entry for an integer. 
entry_t *int_alloc (int i);

/// Allocate an entry for a procedure. 
entry_t *proc_alloc (char *name, entry_t *rtype, table_t *param, int flag, int psize);

/// Allocate an entry for a result. 
entry_t *result_alloc (char *name, entry_t *type);

#endif
