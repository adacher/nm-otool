#include <ft_nm.h>

static int				archive_header_size(char *ar_name)
{
	char		*s;
	int			nb;

	s = ft_strstr(ar_name, "/");
	nb = 0;
	if (s)
		nb = ft_atoi(s + 1);
	if (nb > 0)
		return (nb);
	else
		return (-1);
}

static void         display_object_name(struct ar_hdr *ar_h, char *av)
{
	ft_putstr(av);
	ft_putchar('(');
	ft_putstr((char*)(ar_h + 1));
	ft_putendl("):");
}

static void				treat_object(void *ptr, char *av)
{
	struct ar_hdr		*lib;
	unsigned int		magic;

	lib = ptr;
	display_object_name(lib, av);
	ptr += sizeof(* lib) + archive_header_size(lib->ar_name);
	magic = *(int *)ptr;
	if (magic == MH_MAGIC)
		macho_32(ptr);
	else if (magic == MH_MAGIC_64)
		macho_64(ptr);
}

void    archive_lib(void *ptr, char *av, uint32_t filesize, void *tmp)
{
    struct ar_hdr			*lib;

    lib = (struct ar_hdr *)ptr;
	ft_putstr("Archive : ");
    ft_putendl(av);
    while (ptr + ft_atoi(lib->ar_size) + sizeof(*lib)
			<= tmp + filesize)
	{
        treat_object(ptr, av);
        ptr += ft_atoi(lib->ar_size) + sizeof(*lib);
		lib = (struct ar_hdr *)(ptr);
    }
}