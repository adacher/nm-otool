#include <ft_nm.h>

void		nm(void *ptr, char *av, size_t filesize, void *tmp)
{
	uint32_t		magic;
	struct ar_hdr	lib;
	void			*data;

	magic = *(uint32_t *)ptr;
	if (magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
		bits_64(ptr, filesize); //x86_64 
	else if (magic == MH_MAGIC || magic == MH_CIGAM)
		bits_32(ptr, filesize); //xi386
	else if (magic == FAT_MAGIC_64 || magic == FAT_CIGAM_64)
		printf("FAT_MAGIC_64\n"); //print_fat_header(ptr);
	else if (magic == FAT_MAGIC || magic == FAT_CIGAM)
		do_fat(ptr, filesize); //print_fat_header(ptr);
	else if (!(ft_strncmp(ptr, ARMAG, SARMAG)))
	{
		lib = *(struct ar_hdr*)(ptr + SARMAG);
		data = ptr + SARMAG + sizeof(struct ar_hdr)
			+ ft_atoi(lib.ar_size);
		ptr = data;
		archive_lib(ptr, av, filesize, tmp);
	}
}

static int start_nm(int ac, char *ptr, char *av, size_t filesize)
{
	void *tmp;

	tmp = ptr;
	if (!(check_file_content(ptr, filesize)))
	{
		ft_putstr(av);
		ft_putstr(" : ");
		ft_putendl("Object file is corrupted");
		return (0);
	}
	if (ac > 2)
	{
		if (ft_strncmp(ptr, ARMAG, SARMAG)) // NEST PAS UNE LIBRAIRIE
		{
			ft_putchar('\n');
			display_av(av);
		}
		nm(ptr, av, filesize, tmp);
	}
	else
		nm(ptr, av, filesize, tmp);
	return (0);
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
		nm(ptr, NULL, buf.st_size, NULL);
	if (munmap(ptr, buf.st_size) < 0)
		return (unvalid_object("a.out"));
	close (fd);
	return (0);
}

static int		input_operations(int ac, char *av)
{
	int			fd;
	char		*ptr;
	struct stat buf;

	if ((fd = open(av, O_RDONLY)) < 0)
		return (no_file(av));
	if (fstat(fd, &buf) < 0)
		return (unvalid_object(av)); // invalid non pas unvalid
	if (S_ISDIR(buf.st_mode))
		return (file_is_dir(av));
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) ==
			MAP_FAILED)
		return (unvalid_object(av));
	if (ac >= 2 && (check_format(ptr, av) == 1))
	{
		if (!(start_nm(ac, ptr, av, buf.st_size)))
			return (0);
	}
	if (munmap(ptr, buf.st_size) < 0)
		return (unvalid_object(av));
	close (fd);
	return (1);
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
		print = input_operations(ac, av[i]);
	//	if (av[i + 1] != NULL && print == 0)
	//		ft_putchar('\n');
	//	if (av[i + 1] == NULL && print == 0)
	//		ft_putchar('\n');
		i++;
	}
	return (0);
}