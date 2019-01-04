#include <ft_nm.h>

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

void display_32(t_section *psects, t_symdata *psymbols)
{
    while (psymbols)
    {
        if (psymbols->stab == 0)
        {
            mask_32(psymbols->value, psymbols->type);
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
            mask_64(psymbols->value, psymbols->type);
            ft_putchar(' ');
            display_symbol(psects, psymbols);
            ft_putchar(' ');
            print_function_name(psymbols->str);
        }
        psymbols = psymbols->next;
    }
}