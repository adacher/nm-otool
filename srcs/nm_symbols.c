#include <ft_nm.h>

static char sym_part_one(t_data *info, char type)
{
    if ((info->type & N_TYPE) == N_INDR)
        type = 'I';
    if ((info->type & N_TYPE) == N_STAB)
        type = '-';
    if ((info->type & N_TYPE) == N_UNDF)
    {
        if ((info->type & N_EXT) && info->value != 0)
            type = 'C';
        else if ((info->type & N_TYPE) == N_PBUD)
            type = 'u';
        else
            type = 'U';
    }
    if ((info->type & N_TYPE) == N_ABS)
        type = 'A';
    return (type);
}

static char sym_part_two(t_data *info, char type, char *sect)
{
    if ((info->type & N_TYPE) == N_SECT)
	{
        if (sect)
        {
            if ((!ft_strcmp(sect, "__text")
			    || !ft_strcmp(sect, "__data")
			    || !ft_strcmp(sect, "__bss")))
                type = ft_toupper(sect[2]);
            else
                type = 'S';
        }
	}
    return (type);
}

void display_symbol(t_data *info, char **tab)
{
    char			type;
	char			*sect;

	type = 0;
    type = sym_part_one(info, type);
    if (!type)
    {
        sect = tab[info->sect - 1];
        type = sym_part_two(info, type, sect);
    }
    ft_putchar(' ');
    if (!(info->type & N_EXT))
        ft_putchar(ft_tolower(type));
    else
        ft_putchar(type);
	ft_putchar(' ');
	ft_putendl(info->str);
}