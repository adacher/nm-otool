#include <ft_nm.h>

static void		nm(void *ptr, char *av, size_t filesize, void *tmp)
{
	int			magic;
	struct ar_hdr	lib;
	void			*data;

	magic = *(int *)ptr;
	if (magic == (int)MH_MAGIC_64)
		macho_64(ptr, filesize);
	else if (magic == (int)MH_MAGIC)
		macho_32(ptr);
	else if (magic == (int)FAT_CIGAM_64)
		fat_64(ptr);
	else if (magic == (int)FAT_CIGAM)
		fat_32(ptr);
	else if (!(ft_strncmp(ptr, ARMAG, SARMAG)))
	{
		lib = *(struct ar_hdr*)(ptr + SARMAG);
		data = ptr + SARMAG + sizeof(struct ar_hdr)
			+ ft_atoi(lib.ar_size);
		ptr = data;
		archive_lib(ptr, av, filesize, tmp);
	}
}

static void check_ac(int ac, char *ptr, char *av, uint32_t filesize)
{
	void *tmp;

	tmp = ptr;
	if (ac > 2)
	{
		if (ft_strncmp(ptr, ARMAG, SARMAG))
		{
			ft_putchar('\n');
			display_av(av);
		}
		nm(ptr, av, filesize, tmp);
	}
	else
		nm(ptr, av, filesize, tmp);
}

static int		try_a_out(void)
{
	int			fd;
	char		*ptr;
	struct stat	buf;
	size_t		filesize;

	if ((fd = open("a.out", O_RDONLY)) < 0)
		return (no_file("a.out"));
	if (fstat(fd, &buf) < 0)
		return (unvalid_object("a.out"));
	if (S_ISDIR(buf.st_mode))
			return (file_is_dir("a.out"));
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) ==
	MAP_FAILED)
		return (unvalid_object("a.out"));
	filesize = buf.st_size;
	if (check_format(ptr, "a.out") == 1)
		nm(ptr, NULL, filesize, NULL);
	if (munmap(ptr, buf.st_size) < 0)
		return (unvalid_object("a.out"));
	//close (fd); // ?
	return (0);
}

static int		try_nm(int ac, char *av)
{
	int			fd;
	char		*ptr;
	struct stat buf;
	size_t filesize;

	if ((fd = open(av, O_RDONLY)) < 0)
		return (no_file(av));
	if (fstat(fd, &buf) < 0)
		return (unvalid_object(av));
	if (S_ISDIR(buf.st_mode))
		return (file_is_dir(av));
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) ==
			MAP_FAILED)
		return (unvalid_object(av));
	filesize = buf.st_size;
	if (ac >= 2 && (check_format(ptr, av) == 1))
		check_ac(ac, ptr, av, filesize);
	if (munmap(ptr, buf.st_size) < 0)
		return (unvalid_object(av));
	close (fd); // ?
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