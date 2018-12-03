#include <ft_nm.h>

void			print_letter(t_data *lt, char **tab)
{
	char			type;
	char			*section_name;

	type = 0;
	type = ((lt->type & N_TYPE) == N_INDR) ? 'I' : type;
	type = (!type && (lt->type & N_TYPE) == N_STAB) ? '-' : type;
	type = (!type && (lt->type & N_TYPE) == N_UNDF
		&& (lt->type & N_EXT) && lt->value != 0) ? 'C' : type;
	type = (!type && (lt->type & N_TYPE) == N_UNDF
		&& (lt->type & N_TYPE) == N_PBUD) ? 'u' : type;
	type = (!type && (lt->type & N_TYPE) == N_UNDF) ? 'U' : type;
	type = (!type && (lt->type & N_TYPE) == N_ABS) ? 'A' : type;
	if (!type && (lt->type & N_TYPE) == N_SECT)
	{
		section_name = tab[lt->sect - 1];
		type = (section_name && (!ft_strcmp(section_name, "__text")
			|| !ft_strcmp(section_name, "__data")
			|| !ft_strcmp(section_name, "__bss"))) ?
		ft_toupper(section_name[2]) : 'S';
	}
	ft_putchar(' ');
	ft_putchar(!(lt->type & N_EXT) ? ft_tolower(type) : type);
	ft_putchar(' ');
	ft_putendl(lt->str);
}

t_data  *init_list(struct symtab_command *sym, struct nlist_64 *nlist, char *str, t_data *fill)
{
    uint32_t i;

    i = 0;
    while (i < sym->nsyms)
    {
        if (!(nlist[i].n_type & N_STAB))
            add_list_64(&fill, str + nlist[i].n_un.n_strx, nlist[i]); // A CHANGER LE TOUT
        i++;
    }
	return (fill);
}

void display_m64(void *ptr, char **tab, struct symtab_command *sym)
{
    char     *str;
    struct nlist_64 *nlist;
    t_data          *fill;
    t_data          *tmp;

    str = (void *)ptr + sym->stroff;
    nlist = (void *)ptr + sym->symoff;
	fill = NULL;
   	fill = init_list(sym, nlist, str, fill);
    while (fill)
	{
		if (!(fill->value) && (fill->type & N_TYPE) != N_UNDF) // fill->value == 0
			ft_putstr("0000000000000000");
		else
			mask_64(fill->value);
		print_letter(fill, tab); // a changer
		tmp = fill->next;
		free(fill);
		fill = tmp;
	}
	free(tab);
}