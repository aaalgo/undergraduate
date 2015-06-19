/* filename: ext2.h
   by Dong Wei */
#include <clib.h>
#include <ext2.h>
#include <floppy.h>

void *dma_buf = (void *)4096;
super_block_t *sb = NULL;
grp_desc_t *grd = NULL;

int ext2_init (void)
{
	floppy_read(2, dma_buf);
	sb = page_alloc();
	grd = (pchar)sb + sizeof(super_block_t);	
	memcpy(sb, dma_buf, sizeof(super_block_t));	
}

int dump_super_block (void)
{
	super_block_t *sb;
	sb = (super_block_t *)4096;
	vtprintf(0, "sizeof(sb)= %d\n", sizeof(super_block_t));
	vtprintf(0, "inode_count %d\n", sb->s_inode_count);
	vtprintf(0, "block_count %d\n", sb->s_block_count);
	vtprintf(0, "r_block_count %d\n", sb->s_r_block_count);
	vtprintf(0, "free_block_count %d\n", sb->s_free_block_count);
	vtprintf(0, "free_inode_count %d\n", sb->s_free_inode_count);
	vtprintf(0, "first_data_block %d\n", sb->s_first_data_block);
	vtprintf(0, "log_block_size %d\n", sb->s_log_block_size);
	vtprintf(0, "log_frag_size %d\n", sb->s_log_frag_size);
	vtprintf(0, "blocks_per_group %d\n", sb->s_blocks_per_group);
	vtprintf(0, "inodes_per_group %d\n", sb->s_inodes_per_group);
	vtprintf(0, "mnt_count %d\n", sb->s_mnt_count);
	vtprintf(0, "max_mount %d\n", sb->s_mnt_count);
	vtprintf(0, "volume_name %s\n", sb->s_volume_name);
	vtprintf(0, "last_mounted %s\n", sb->s_last_mounted);
	vtprintf(0, "inode_size %d\n", sb->s_inode_size);
	vtprintf(0, "first_ino %d\n", sb->s_first_ino);
	return TRUE;
}
