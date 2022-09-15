#include <filesystem/aosfs.h>

#define ROOT        "$0://root/"

void
aosfs_mount_to_device(struct device* dev, struct fs* fsptr)
{
	struct mount_point* mp;

	void* aosfs_ptr = fs_create("AOS32", 0xFFFF0000, dev, fsptr);
	if (aosfs_ptr == NULL)
		return EROFS;
	else
		fs_mount(aosfs_ptr, 0x80, mp);
	
	
}
