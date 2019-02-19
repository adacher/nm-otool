#include <otool.h>

static void check_cpu_type64(struct fat_arch_64 *fatarch)
{
	ft_putchar(' ');
	if (swap_64(fatarch->cputype) == CPU_TYPE_I386)
		ft_putendl("(architecture i386):");
	else if (swap_64(fatarch->cputype) == CPU_TYPE_POWERPC)
		ft_putendl("(architecture ppc):");
	else
		ft_putendl("(unknown architecture):");
}

static int check64_x86_64(uint32_t nbarch, struct fat_arch_64 *fatarch, void *ptr)
{
	uint32_t i;

	i = 0;
	while (i < nbarch)
	{
		if (swap_64(fatarch->cputype) == CPU_TYPE_X86_64)
		{
			do_bits_64(ptr + swap_64(fatarch->offset));
			return (1);
		}
		fatarch += 1;
		i++;
	}
	return (0);
}

static int browse_fat_64(struct fat_header *header, void *ptr, char *av)
{
	struct fat_arch_64	*fatarch;
	uint64_t nbarch;
	uint64_t i;

	i = 0;
	fatarch = (struct fat_arch_64 *)(header + 1);
	nbarch = swap_64(header->nfat_arch);
	if (check64_x86_64(nbarch, fatarch, ptr) == 1)
		return (1);
	while (i < nbarch)
	{
		ft_putstr(av);
		check_cpu_type64(fatarch);
		otool(ptr + swap_64(fatarch->offset), av, 0);
		fatarch += 1;
		i++;
	}
	return (0);
}

void do_fat_64(void *ptr, char *av)
{
	struct fat_header	*header;

	header = (struct fat_header *)ptr;
	if (browse_fat_64(header, ptr, av) == 1)
		return ;	
}