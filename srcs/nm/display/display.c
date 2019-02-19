#include <nm.h>

static void print_function_name(char *str)
{
    unsigned int i;

    i = 0;
    while (str[i])
    {
        if (ft_isprint(str[i]))
        {
            ft_putchar(str[i]);
            i++;
        }
        else
        {
            ft_putchar('\n');
            return ;
        }
    }
    ft_putchar('\n');
}

void				nm_mask_64(uint64_t value, uint8_t type)
{
	if (!value)
	{
		if (type != N_UNDF)
			ft_putstr("0000000000000000");
		else
			ft_putstr("                ");
		return ;
	}
	mask_64(value);
}

void				nm_mask_32(uint64_t value, uint8_t type)
{
	if (!value)
	{
		if (type != N_UNDF)
			ft_putstr("00000000");
		else
			ft_putstr("        ");
		return ;
	}
	mask_32(value);
}

void display_32(t_section *psects, t_symdata *psymbols)
{
    while (psymbols)
    {
        if (psymbols->stab == 0)
        {
            nm_mask_32(psymbols->value, psymbols->type);
            ft_putchar(' ');
            display_symbol(psects, psymbols);
            ft_putchar(' ');
            print_function_name(psymbols->str);
        }
        psymbols = psymbols->next;
    }
}

void display_64(t_section *psects, t_symdata *psymbols)
{
    while (psymbols)
    {
        if (psymbols->stab == 0)
        {
            nm_mask_64(psymbols->value, psymbols->type);
            ft_putchar(' ');
            display_symbol(psects, psymbols);
            ft_putchar(' ');
            print_function_name(psymbols->str);
        }
        psymbols = psymbols->next;
    }
}