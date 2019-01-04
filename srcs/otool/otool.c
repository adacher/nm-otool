#include <ft_otool.h>

void			otool(void *ptr, char *av, uint32_t filesize, void *tmp)
{
	unsigned int	magic;
	struct ar_hdr	lib;
	void			*data;

	magic = *(int *)ptr;
	if (magic == MH_MAGIC_64)
		macho_64(ptr, NULL);
	else if (magic == MH_MAGIC)
		macho_32(ptr, NULL);
	else if (magic == FAT_CIGAM_64)
		fat_64(ptr);
	else if (magic == FAT_CIGAM)
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

static void			launch_otool(char *ptr, char *av, uint32_t filesize)
{
	void *tmp;

	tmp = NULL;
	if (ft_strncmp(ptr, ARMAG, SARMAG))
	{
		ft_putstr(av);
		ft_putendl(":");
	}
	else
		tmp = ptr;
	otool(ptr, av, filesize, tmp);
}

static int			try_otool(int ac, char *av)
{
	int				fd;
	char			*ptr;
	struct stat		buf;
	uint32_t		filesize;

	if ((fd = open(av, O_RDONLY)) < 0)
		return (fd_bug(av));
	if (fstat(fd, &buf) < 0)
		return (object_bug(av));
	if (S_ISDIR(buf.st_mode))
		return (dir_bug(av));
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) ==
			MAP_FAILED)
		return (object_bug(av));
	filesize = buf.st_size;
	if (ac >= 2 && check_format(ptr, av) == 1)
		launch_otool(ptr, av, filesize);
	if (munmap(ptr, buf.st_size) < 0)
		return (object_bug(av));
	return (0);
}

int main(int ac, char **av)
{
	int i;

	i = 1;
	if (ac < 2)
		ft_putendl("ft_tool: at least one file must be specified");
	while (i < ac)
	{
		if ((try_otool(ac, av[i])) != -1)
			i++;
		else
			return (0);
	}	
	return (0);
}