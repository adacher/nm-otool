#include <ft_otool.h>

int fd_bug(char *av)
{
    ft_putstr(av);
    ft_putendl(": No such file or directory");
    return (-1);
}

int object_bug(char *av)
{
    ft_putstr(av);
    ft_putendl(": is not an object file");
    return (-2);
}

int dir_bug(char *av)
{
    ft_putchar('\'');
    ft_putstr(av);
    ft_putchar('\'');
    ft_putendl(": Is a directory");
    return (-1);
}

int check_format(char *ptr, char *av)
{
   unsigned int magic;

	magic = *(int *)ptr;
	if (magic == MH_MAGIC_64)
		return (1);
	else if (magic == MH_MAGIC)
		return (1);
	else if (magic == FAT_CIGAM_64)
		return (1);
	else if (magic == FAT_CIGAM)
		return (1);
    else if (!(ft_strncmp(ptr, ARMAG, SARMAG)))
        return (1);
    else
       return (object_bug(av));
    return (0);
}