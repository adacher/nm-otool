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
	return (EXIT_FAILURE);
}

int			file_is_dir(char *av)
{
	ft_putstr(av);
	ft_putstr(": Is a directory.\n");
	return (EXIT_FAILURE);
}

int			unvalid_object(char *av)
{
	ft_putstr(av);
	ft_putstr(" The file was not recognized as a valid object file\n");
	return (EXIT_FAILURE);
}

int		check_format(void *ptr, char *av)
{
	int			magic;

	magic = *(int *)ptr;

	if (magic == (int)MH_MAGIC_64)
		return (1);
	else if (magic == (int)MH_MAGIC)
		return (1);
	else if (magic == (int)FAT_CIGAM_64)
		return (1);
	else if (magic == (int)FAT_CIGAM)
		return (1);
	else if (!(ft_strncmp(ptr, ARMAG, SARMAG)))
		return (1);
	else
	{
		unvalid_object(av);
		ft_putchar('\n');
		return (0);
	}
}