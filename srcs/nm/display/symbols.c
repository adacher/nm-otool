#include <nm.h>

static void symbol_not_in_section(t_symdata *psymbols)
{
    if (psymbols->type == N_SECT)
        return ;
    else if (psymbols->type == N_UNDF)
    {
        if (psymbols->value != 0)
            (psymbols->ext == 0) ? ft_putchar('c') : ft_putchar('C');
        else
            ft_putchar('U');
    }
    else if (psymbols->type == N_PBUD)
        ft_putchar('u');
    else if (psymbols->type == N_ABS)
        (psymbols->ext == 0) ? ft_putchar('a') : ft_putchar('A');
    else if (psymbols->type == N_INDR)
        (psymbols->ext == 0) ? ft_putchar('i') : ft_putchar('I');
    else
        ft_putchar('?');
}

static void symbol_is_in_section(t_section *psects, t_symdata *psymbols)
{
    uint8_t nsect;

    if (psymbols->type == N_SECT)
    {
        nsect = psymbols->nsect;
        while (psects)
        {
            if (nsect == psects->index)
            {
                if (!(ft_strcmp(psects->name, "__text")))
                    (psymbols->ext == 0) ? ft_putchar('t') : ft_putchar('T');
                else if (!(ft_strcmp(psects->name, "__bss")))
                    (psymbols->ext == 0) ? ft_putchar('b') : ft_putchar('B');
                else if (!(ft_strcmp(psects->name, "__data")))
                    (psymbols->ext == 0) ? ft_putchar('d') : ft_putchar('D');
                else
                    (psymbols->ext == 0) ? ft_putchar('s') : ft_putchar('S');
                return ;
            }
            psects = psects->next;
        }   
    }
}

void display_symbol(t_section *psects, t_symdata *psymbols)
{
    symbol_is_in_section(psects, psymbols);
    symbol_not_in_section(psymbols);
}