/**
  * \file config.h
  * \author Dong Wei
  * \brief Configuring constant and macro definitions.
  */

#ifndef __DSMS_CONFIG__
#define __DSMS_CONFIG__

/** Maximum identifier length. */
#define MAX_ID_LEN 32

#define MAX_STREAM		128
#define MAX_STATIC_FIELD	16
#define PACKET_TOTAL_SIZE 	0x8000000
#define PACKET_PAGE_SIZE 	0x400
#define BUFFER_TOTAL_SIZE	0x800
#define BUFFER_MAGIC		0x888888
#define SCHED_BUCKET_NUM	16
#define ARGUS_MAX_PRIORITY		64
#define DEFAULT_DEST_NUM	8
#define MAX_BUFFERS		4
#define PRIORITY_WEIGHT (ARGUS_MAX_PRIORITY / (SCHED_BUCKET_NUM >> 1))

#define EMPTY_BEFORE_DEACTIVATE


#define MAX_SOURCE		16
#define MAX_GROUP		16
#define MAX_FILTER		16
#define MAX_AGGRE		32
#define MAX_MAP			16

#define MAX_QUERY		128

#define AGG_HAS_BUCNUM	128


#endif

