#include <ft_otool.h> 

char  convert_unit(unsigned long long n, char *str, size_t len)
{
	str[len] = n % 16;
	if (str[len] > 9)
		str[len] = ('a' + (n % 16 - 10));
	else
		str[len] = ('0' + (n % 16));
	return (str[len]);
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
    while (sect->offset + offset + header < sect->offset + sect->size + header)
    {
		mask_32(sect->addr + offset);
        i = 0;
        ft_putchar('\t');
        while (i < 16)
        {
            display_hex(*(header + sect->offset + offset + i));
            ft_putchar(' ');
            if ((char *)header + sect->offset + offset + i + 1 >=
			(char *)header + sect->offset + sect->size)
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
    while (sect->offset + offset + header < sect->offset + sect->size + header)
    {
		mask_64(sect->addr + offset);
        i = 0;
        ft_putchar('\t');
        while (i < 16)
        {
			if (header)
            	display_hex(*(header + sect->offset + offset + i));
            ft_putchar(' ');
            if ((char *)header + sect->offset + offset + i + 1 >=
			(char *)header + sect->offset + sect->size)
				break ;
            i++;
        }
        offset += 16;
        ft_putchar('\n');
    }
}