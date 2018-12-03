#include <ft_otool.h>

int			reverse_endian(int x)
{
	x = ((x << 8) & 0xFF00FF00) | ((x >> 8) & 0xFF00FF);
	return (x << 16) | (x >> 16);
}

void		fat_32(void *ptr)
{
	int					i;
	int					narch;
	struct fat_header	*fat;
	struct fat_arch		*arch;

	i = -1;
	fat = (struct fat_header*)ptr;
	narch = reverse_endian(fat->nfat_arch);
	arch = (struct fat_arch*)(fat + 1);
	while (++i < (int)narch)
	{
		if (reverse_endian(arch->cputype) == CPU_TYPE_X86_64 ||
			reverse_endian(arch->cputype) == CPU_TYPE_X86)
		{
			otool(ptr + reverse_endian(arch->offset), NULL, 0, NULL);
			return ;
		}
		arch = arch + 1;
	}
}

void		fat_64(void *ptr)
{
	int					i;
	int					narch;
	struct fat_header	*fat;
	struct fat_arch_64	*arch;

	i = -1;
	fat = (struct fat_header*)ptr;
	narch = reverse_endian(fat->nfat_arch);
	arch = (struct fat_arch_64*)(fat + 1);
	while (++i < (int)narch)
	{
		if (reverse_endian(arch->cputype) == CPU_TYPE_X86_64 ||
			reverse_endian(arch->cputype) == CPU_TYPE_X86)
		{
			otool(ptr + reverse_endian(arch->offset), NULL, 0, NULL);
			return ;
		}
		arch = arch + 1;
	}
}