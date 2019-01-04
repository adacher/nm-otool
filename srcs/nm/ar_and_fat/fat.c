#include <ft_nm.h>

#define SWAP32(x) ((((x) & 0xff000000) >> 24) | (((x) & 0xff0000) >> 8) | (((x) & 0xff00) << 8) | (((x) & 0xff) << 24))

void swap_struct_fatarch(struct fat_header *header, uint32_t magic, uint32_t nbarch, void *ptr, size_t filesize)
{
	struct fat_arch	*fatarch;

	magic = 0;
	fatarch = (struct fat_arch *)(header + 1);
	while (nbarch)
	{
		if (SWAP32(fatarch->cputype) == CPU_TYPE_X86_64)
			bits_64(ptr + SWAP32(fatarch->offset), filesize);
		else if (SWAP32(fatarch->cputype) == CPU_TYPE_I386)
			bits_32(ptr + SWAP32(fatarch->offset), filesize);
		fatarch += 1;
		nbarch--;
	}
}

void do_fat(void *ptr, size_t filesize)
{
	uint32_t			magic;
	uint32_t			nbarch;
	struct fat_header	*header;

	header = (struct fat_header *)ptr;
	magic = SWAP32(header->magic);
	nbarch = SWAP32(header->nfat_arch);
	swap_struct_fatarch(header, magic, nbarch, ptr, filesize);
	filesize = 0;
	//if (filesize > SWAP32(arch->offset) + sizeof(SWAP32((arch->cputype)) + SWAP32((arch->cpusubtype)))
	//	return ;
	
}