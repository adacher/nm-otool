#include <nm.h>

static void check_cpu_type32(struct fat_arch *fatarch)
{
	ft_putchar(' ');
	if (swap_32(fatarch->cputype) == CPU_TYPE_I386)
		ft_putendl("(for architecture i386):");
	else if (swap_32(fatarch->cputype) == CPU_TYPE_POWERPC)
		ft_putendl("(for architecture ppc):");
	else
		ft_putendl("(for unknown architecture):");
}

static int check32_x86_64(uint32_t nbarch, struct fat_arch *fatarch, void *ptr, size_t filesize)
{
	uint32_t i;

	i = 0;
	while (i < nbarch)
	{
		if (swap_32(fatarch->cputype) == CPU_TYPE_X86_64)
		{
			do_bits_64(ptr + swap_32(fatarch->offset), filesize);
			return (1);
		}
		fatarch += 1;
		i++;
	}
	return (0);
}

static int browse_fat_32(struct fat_header *header, void *ptr, size_t filesize, char *av)
{
	struct fat_arch	*fatarch;
	uint32_t nbarch;
	uint32_t i;

	i = 0;
	fatarch = (struct fat_arch *)(header + 1);
	nbarch = swap_32(header->nfat_arch);
	if (check32_x86_64(nbarch, fatarch, ptr, filesize) == 1)
		return (1);
	while (i < nbarch)
	{
		ft_putchar('\n');
		ft_putstr(av);
		check_cpu_type32(fatarch);
		nm(ptr + swap_32(fatarch->offset), av, filesize);
		fatarch += 1;
		i++;
	}
	return (0);
}

void do_fat_32(void *ptr, size_t filesize, char *av)
{
	struct fat_header	*header;

	header = (struct fat_header *)ptr;
	if (browse_fat_32(header, ptr, filesize, av) == 1)
		return ;
}