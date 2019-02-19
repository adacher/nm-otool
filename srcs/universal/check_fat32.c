#include <universal.h>

int verify_content_f32(void *ptr, struct fat_arch *fatarch, size_t filesize)
{
    struct mach_header *header;

    header = (void *)ptr + swap_32(fatarch->offset);
    if (header->magic == MH_MAGIC || header->magic == MH_CIGAM)
		return (verify_32(header, filesize));
	if (header->magic == MH_MAGIC_64 || header->magic == MH_CIGAM_64)
		return (verify_64(header, filesize));
	return (0);
}

int verify_fatlc_32(void *ptr, struct fat_header *header, uint32_t nbarch, size_t filesize)
{
    struct fat_arch *fatarch;
    uint32_t i;
    size_t checksize;
    size_t checkoffset;

    i = 0;
    checksize = 0;
    checkoffset = 0;
    fatarch = (struct fat_arch *)(header + 1);
    while (i < nbarch)
    {
        checkoffset += swap_32(fatarch->offset);
        checksize += sizeof(*fatarch);
        if (checkoffset > filesize)
            return (0);
        if ((checkoffset + sizeof(fatarch->cputype + fatarch->cpusubtype)) > filesize)
            return (0); // a enlever
        if (checksize > filesize)
            return (0);
        if (verify_content_f32(ptr, fatarch, filesize) == 0)
            return (0);
        fatarch += 1;
        i++;
    }
    return (1);
}

int verify_fat_32(void *ptr, size_t filesize)
{
    struct fat_header *header;
    uint32_t nbarch;

    header = (struct fat_header *)ptr;
    nbarch = swap_32(header->nfat_arch);
    return (verify_fatlc_32(ptr, header, nbarch, filesize));
}