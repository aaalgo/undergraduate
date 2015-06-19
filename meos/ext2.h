/* filename: ext2.h
   by Dong Wei */
#ifndef __MEOS_EXT2__
#define __MEOS_EXT2__

typedef struct
{
	__u32	s_inode_count;
	__u32	s_block_count;
	__u32	s_r_block_count;
	__u32	s_free_block_count;
	__u32	s_free_inode_count;
	__u32	s_first_data_block;
	__u32	s_log_block_size;
	__u32	s_log_frag_size;
	__u32	s_blocks_per_group;
	__u32	s_frags_per_group;
	__u32	s_inodes_per_group;
	__u32	s_mtime;
	__u32	s_wtime;
	__u16	s_mnt_count;
	__u16	s_max_mnt_count;
	__u16	s_magic;
	__u16	s_state;
	__u16	s_errors;
	__u16	s_minor_rev_level;
	__u32	s_lastcheck;
	__u32	s_checkinterval;
	__u32	s_create_os;
	__u32	s_rev_level;
	__u16	s_def_resuid;
	__u16	s_def_resgid;
	__u32	s_first_ino;
	__u16	s_inode_size;
	__u16	s_block_group_nr;
	__u32	s_feature_compat;
	__u32	s_feature_incompat;
	__u32	s_feature_ro_compat;
	__u8	s_uuid[16];
	char	s_volume_name[16];
	char	s_last_mounted[64];
	__u32	s_algorithm_usage_bitmap;
	__u8	s_prealloc_blocks;
	__u8	s_prealloc_dir_blocks;
	__u16	s_padding1;
	__u32	s_reserved[204];
} super_block_t;
 
typedef struct
{
	__u32	bg_block_bitmap;
	__u32	bg_inode_bitmap;
	__u32	bg_inode_table;
	__u16	bg_free_blocks_count;
	__u16	bg_free_inodes_count;
	__u16	bg_used_dirs_count;
	__u16	bg_pad;
	__u32	bg_reserved[3];
} grp_desc_t;


typedef struct
{
	__u16	i_mode;
	__u16	i_uid;
	__u32	i_size;
	__u32	i_atime;
	__u32	i_ctime;
	__u32	i_mtime;
	__u32	i_dtime;
	__u16	i_gid;
	__u16	i_links_count;
	__u32	i_blocks;
	__u32	i_flags;
	__u32	osd1;
	__u32	i_block;
	__u32	i_generation;
	__u32	i_file_acl;
	__u32	i_dir_acl;
	__u32	i_faddr;
	__u32	osd2[3];	
} inode_t;

#endif
