#include <otool.h> 

static void check_ifppc_output(uint32_t i)
{
    if (*get_ppc())
    {
        if (i % 4 == 3)
            ft_putchar(' ');
    }
    else
        ft_putchar(' ');
}

static void				display_hex(char byte)
{
	char			str[2];
	short			count;
	short			char_hex;
	unsigned char	cast;

	cast = (unsigned char)byte;
	count = -1;
	while (++count != 2)
	{
		char_hex = cast % 16;
		cast /= 16;
		if (char_hex < 10)
			str[count] = char_hex + '0';
		else
			str[count] = (char_hex - 10) + 'a';
	}
	ft_putchar(str[1]);
	ft_putchar(str[0]);
}

void display_m32(struct section *sect, char *header)
{
    uint32_t offset;
    uint32_t i;

    offset = 0;
    while (ppc_32(sect->offset) + offset + header < ppc_32(sect->offset) + ppc_32(sect->size) + header)
    {
		mask_32(ppc_32(sect->addr) + offset);
        i = 0;
        ft_putchar('\t');
        while (i < 16)
        {
            display_hex(*(header + ppc_32(sect->offset) + offset + i));
            check_ifppc_output(i);
            if ((char *)header + ppc_32(sect->offset) + offset + i + 1 >=
            (char *)header + ppc_32(sect->offset) + ppc_32(sect->size))
				break ;
            i++;
        }
        offset += 16;
        ft_putchar('\n');
    }
}

void display_m64(struct section_64 *sect, char *header)
{
    uint32_t offset;
    uint32_t i;

    offset = 0;
    while (ppc_64(sect->offset) + offset + header < ppc_64(sect->offset) + ppc_64(sect->size) + header)
    {
		mask_64(ppc_64(sect->addr) + offset);
        i = 0;
        ft_putchar('\t');
        while (i < 16)
        {
            display_hex(*(header + ppc_64(sect->offset) + offset + i));
            check_ifppc_output(i);
            if ((char *)header + ppc_64(sect->offset) + offset + i + 1 >=
			(char *)header + ppc_64(sect->offset) + ppc_64(sect->size))
				break ;
            i++;
        }
        offset += 16;
        ft_putchar('\n');
    }
}