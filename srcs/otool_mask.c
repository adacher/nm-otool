#include <ft_otool.h>

void				mask_32(unsigned long long n)
{
	unsigned long long 	mask;
	unsigned char		digit;
	char				output[17];
	int					i;
	int					max;

	mask = 0x00000000f0000000;
	max = 8;
	output[max] = '\0';
	i = -1;
	while (++i < max)
	{
		digit = (n & mask) >> (4 * (max - i - 1));
		mask = mask >> 4;
		if (digit > 9)
			output[i] = ('a' + (digit - 10));
		else
			output[i] = '0' + digit;
	}
	ft_putstr(output);
}

void				mask_64(unsigned long long n)
{
	unsigned long long 	mask;
	unsigned char		digit;
	char				output[17];
	int					i;
	int					max;

	mask = 0xf000000000000000;
	max = 16;
	output[max] = '\0';
	i = -1;
	while (++i < max)
	{
		digit = (n & mask) >> (4 * (max - i - 1));
		mask = mask >> 4;
		if (digit > 9)
			output[i] = ('a' + (digit - 10));
		else
			output[i] = '0' + digit;
	}
	ft_putstr(output);
}
