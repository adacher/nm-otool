#include <otool.h>

static int find_header_size(char *ar_name)
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

static void         display_object_name(struct ar_hdr *arptr, char *av)
{
	ft_putstr(av);
	ft_putchar('(');
	ft_putstr((char*)(arptr + 1));
	ft_putendl("):");
}

static void		treat_object(void *data, char *av, size_t filesize, struct ar_hdr *arptr)
{
	data += sizeof(*arptr) + find_header_size(arptr->ar_name);
	display_object_name(arptr, av);
	otool(data, av, filesize);
}

void    archive_lib(void *ptr, char *av, size_t filesize)
{
    struct ar_hdr 	ar;
	struct ar_hdr	*arptr;
	void			*data;

	ar = *(struct ar_hdr *)(ptr + SARMAG);
	data = ptr + SARMAG + sizeof(struct ar_hdr) + ft_atoi(ar.ar_size);
	arptr = (struct ar_hdr *)data;
	ft_putstr("Archive : ");
    ft_putendl(av);
   	while (data + ft_atoi(arptr->ar_size) + sizeof(ar) <= ptr + filesize)
	{
        treat_object(data, av, filesize, arptr);
		data += ft_atoi(arptr->ar_size) + sizeof(ar);
		arptr = (struct ar_hdr *)data;
    }
}