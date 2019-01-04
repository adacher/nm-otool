#include <ft_nm.h>

void display_av(char *av)
{
	ft_putstr(av);
	ft_putendl(":");
}

int			no_file(char *av)
{
	ft_putstr(av);
	ft_putstr(": No such file or directory.\n");
	return (0);
}

int			file_is_dir(char *av)
{
	ft_putstr(av);
	ft_putstr(": Is a directory.\n");
	return (0);
}

int			unvalid_object(char *av)
{
	ft_putstr(av);
	ft_putendl(" The file was not recognized as a valid object file\n");
	return (0);
}

int		check_format(void *ptr, char *av)
{
	uint32_t 			magic;

	magic = *(uint32_t *)ptr;
	if (magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
		return (1);
	else if (magic == MH_MAGIC || magic == MH_CIGAM)
		return (1);
	else if (magic == FAT_MAGIC_64 || magic == FAT_CIGAM_64)
		return (1);
	else if (magic == FAT_MAGIC || magic == FAT_CIGAM)
		return (1);
	else if (!(ft_strncmp(ptr, ARMAG, SARMAG)))
		return (1);
	else
		return (unvalid_object(av));
}