#include <nm.h>

void		nm(void *ptr, char *av, size_t filesize)
{
	uint32_t		magic;

	magic = *(uint32_t *)ptr;
	if (magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
		do_bits_64(ptr, filesize);
	else if (magic == MH_MAGIC || magic == MH_CIGAM)
		do_bits_32(ptr, filesize);
	else if (magic == FAT_MAGIC_64 || magic == FAT_CIGAM_64)
		do_fat_64(ptr, filesize, av);
	else if (magic == FAT_MAGIC || magic == FAT_CIGAM)
		do_fat_32(ptr, filesize, av);
	else if (!(ft_strncmp(ptr, ARMAG, SARMAG)))
		archive_lib(ptr, av, filesize);
	else
		return ;	
}

static int start_nm(int ac, char *ptr, char *av, size_t filesize)
{
	if (!(check_file_content(ptr, filesize)))
	{
		ft_putstr(av);
		ft_putstr(" : ");
		ft_putendl("Object file is corrupted");
		return (0);
	}
	if (ac > 2)
	{
		if (ft_strncmp(ptr, ARMAG, SARMAG))
		{
			ft_putchar('\n');
			display_av(av);
		}
		nm(ptr, av, filesize);
	}
	else
		nm(ptr, av, filesize);
	return (1);
}

static int		try_a_out(void)
{
	int			fd;
	char		*ptr;
	struct stat	buf;

	if ((fd = open("a.out", O_RDONLY)) < 0)
		return (no_file("a.out"));
	if (fstat(fd, &buf) < 0)
		return (invalid_object("a.out"));
	if (S_ISDIR(buf.st_mode))
		return (file_is_dir("a.out"));
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) ==
	MAP_FAILED)
		return (invalid_object("a.out"));
	if (check_format(ptr, "a.out") == 1)
	{
		if (!(check_file_content(ptr, buf.st_size)))
		{
			ft_putendl("a.out object file is corrupted");
			return (0);
		}
		nm(ptr, NULL, buf.st_size);
	}
	if (munmap(ptr, buf.st_size) < 0)
		return (invalid_object("a.out"));
	close (fd);
	return (1);
}

static int		input_operations(int ac, char *av)
{
	int			fd;
	char		*ptr;
	struct stat buf;

	if ((fd = open(av, O_RDONLY)) < 0)
		return (no_file(av));
	if (fstat(fd, &buf) < 0)
		return (invalid_object(av));
	if (S_ISDIR(buf.st_mode))
		return (file_is_dir(av));
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) ==
			MAP_FAILED)
		return (invalid_object(av));
	if (ac >= 2 && (check_format(ptr, av) == 1))
	{
		if (!(start_nm(ac, ptr, av, buf.st_size)))
			return (0);
	}
	if (munmap(ptr, buf.st_size) < 0)
		return (invalid_object(av));
	close (fd);
	return (1);
}

int			main(int ac, char **av)
{
	int		i;

	i = 1;
	if (ac < 2)
	{
		if (try_a_out() != 1)
			ft_putchar('\n');
	}
	while (i < ac)
	{
		input_operations(ac, av[i]);
		i++;
	}
	return (0);
}