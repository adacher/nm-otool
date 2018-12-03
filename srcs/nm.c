#include <ft_nm.h>

//bug fichier .o tres peu de contenu.

static void		nm(void *ptr)
{
	int			magic;

	magic = *(int *)ptr;
	if (magic == (int)MH_MAGIC_64)
		macho_64(ptr);
	else if (magic == (int)MH_MAGIC)
		macho_32(ptr);
	else if (magic == (int)FAT_CIGAM_64)
		fat_64(ptr);
	else if (magic == (int)FAT_CIGAM)
		fat_32(ptr);
}

static void check_ac(int ac, char *ptr, char *av)
{
	if (ac > 2)
	{
		ft_putchar('\n');
		display_av(av);
		nm(ptr);
	}
	else
		nm(ptr);
}

static int		try_a_out(void)
{
	int			fd;
	char		*ptr;
	struct stat	buf;

	if ((fd = open("a.out", O_RDONLY)) < 0)
		return (no_file("a.out"));
	if (fstat(fd, &buf) < 0)
		return (unvalid_object("a.out"));
	if (S_ISDIR(buf.st_mode))
			return (file_is_dir("a.out"));
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) ==
	MAP_FAILED)
		return (unvalid_object("a.out"));
	if (check_format(ptr, "a.out") == 1)
		nm(ptr);
	if (munmap(ptr, buf.st_size) < 0)
		return (unvalid_object("a.out"));
	return (0);
}

static int		try_nm(int ac, char *av)
{
	int			fd;
	char		*ptr;
	struct stat buf;
	
	if ((fd = open(av, O_RDONLY)) < 0)
		return (no_file(av));
	if (fstat(fd, &buf) < 0)
		return (unvalid_object(av));
	if (S_ISDIR(buf.st_mode))
		return (file_is_dir(av));
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) ==
			MAP_FAILED)
		return (unvalid_object(av));
	if (ac >= 2 && (check_format(ptr, av) == 1))
		check_ac(ac, ptr, av);
	if (munmap(ptr, buf.st_size) < 0)
		return (unvalid_object(av));
	return (0);
}

int			main(int ac, char **av)
{
	int		i;
	int		print;

	i = 1;
	if (ac < 2)
		if (try_a_out() != 0)
			ft_putchar('\n');
	while (i < ac)
	{
		print = try_nm(ac, av[i]);
		if (av[i + 1] != NULL && print != 0)
			ft_putchar('\n');
		if (av[i + 1] == NULL && print != 0)
			ft_putchar('\n');
		i++;
	}
	return (0);
}