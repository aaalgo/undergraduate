#ifndef __ARGUS_SQLOPR__
#define __ARGUS_SQLOPR__

#include <aggre.h>

operator_t *count_tumble_create (int window_size);
operator_t *count_slide_create (int window_size);
operator_t *time_tumble_create (int window_size, int begin_time);
operator_t *time_slide_create (int window_size, int update_freq);

operator_t *filter_create (schema_t *schema, lnode_t filter);

operator_t *map_create (schema_t *inSchema, schema_t *outSchema, lnode_t map);
operator_t *display_create (char *buf);
operator_t *sender_create (argus_callback_f, void *);

operator_t *group_create (schema_t *outSchema, schema_t *inSchema,
		lnode_t groupField,		/* list of grouped fields */
		lnode_t aggreInfo		/* the aggretations */
		);

int join_pair_create (lnode_t filter, schema_t *schema, operator_t **j1, operator_t **j2);
		
#endif
