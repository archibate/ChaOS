#include <c4/vspace.h>

int vs_map_cap(vspace_t *vs, cap_t *cap, off_t off, size_t size)
{
	if (!cap_valid(cap))
		return -ENOCAP;
	if (!cap->c_dev != CDEV_MEM)
		return -EINVAL;
	if (off > region_size(cap->c_reg))
		return -EFAULT;
	if (PGOFF(off) || PGOFF(size))
		return -EINVAL;
	if (PGOFF(cap->c_beg) || PGOFF(cap->c_end))
		return -EINVAL;

	vs_maps(vs, va, PGINFO(cap->c_beg, cap->c_attr));

	return 0;
}
