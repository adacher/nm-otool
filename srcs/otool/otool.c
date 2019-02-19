#include <otool.h>

void			otool(void *ptr, char *av, size_t filesize)
{
	uint32_t		magic;

	magic = *(uint32_t *)ptr;
	if (magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
		do_bits_64(ptr);
	else if (magic == MH_MAGIC || magic == MH_CIGAM)
		do_bits_32(ptr);
	else if (magic == FAT_MAGIC_64 || magic == FAT_CIGAM_64)
		do_fat_64(ptr, av);
	else if (magic == FAT_MAGIC || magic == FAT_CIGAM)
		do_fat_32(ptr, av);
	else if (!(ft_strncmp(ptr, ARMAG, SARMAG)))
		archive_lib(ptr, av, filesize);
	else
		return ;	
}

static int			start_otool(char *ptr, char *av, size_t filesize)
{
	if (!(check_file_content(ptr, filesize)))
	{
		ft_putstr(av);
		ft_putstr(" : ");
		ft_putendl("Object file is corrupted");
		return (0);
	}
	ft_putstr(av);
	ft_putendl(":");
	otool(ptr, av, filesize);
	return (1);
}

static int			input_operations(int ac, char *av)
{
	int				fd;
	char			*ptr;
	struct stat		buf;

	if ((fd = open(av, O_RDONLY)) < 0)
		return (no_file(av));
	if (fstat(fd, &buf) < 0)
		return (invalid_object(av));
	if (S_ISDIR(buf.st_mode))
		return (file_is_dir(av));
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) ==
			MAP_FAILED)
		return (invalid_object(av));
	if (ac >= 2 && check_format(ptr, av) == 1)
	{
		if (!(start_otool(ptr, av, buf.st_size)))
			return (0);
	}
	if (munmap(ptr, buf.st_size) < 0)
		return (invalid_object(av));
	close (fd);
	return (1);
}

int main(int ac, char **av)
{
	int i;

	i = 1;
	if (ac < 2)
		ft_putendl("ft_tool: at least one file must be specified");
	while (i < ac)
	{
		if ((input_operations(ac, av[i])) != 0)
			i++;
		else
			return (0);
	}	
	return (0);
}