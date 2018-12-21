#include <ft_nm.h>

static t_data  *init_list(struct symtab_command *sym, struct nlist_64 *nlist, char *str, t_data *fill)
{
    uint32_t i;

    i = 0;
    while (i < sym->nsyms)
    {
        if (!(nlist[i].n_type & N_STAB))
            create_64(&fill, str + nlist[i].n_un.n_strx, nlist[i]); // A CHANGER LE TOUT
        i++;
    }
	return (fill);
}

void display_m64(void *ptr, char **tab, struct symtab_command *sym, size_t filesize)
{
    char     *str;
    struct nlist_64 *nlist;
    t_data          *fill;
    t_data          *tmp;

	if (filesize < sym->stroff + sym->strsize)
		return ;
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
		display_symbol(fill, tab); // a changer
		tmp = fill->next;
		free(fill);
		fill = tmp;
	}
	free(tab);
}