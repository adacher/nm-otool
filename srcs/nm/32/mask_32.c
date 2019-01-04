#include <ft_nm.h>

static void				mask_32_2(uint64_t value)
{
	uint64_t 			mask;
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
		digit = (value & mask) >> (4 * (max - i - 1));
		mask = mask >> 4;
		if (digit > 9)
			output[i] = ('a' + (digit - 10));
		else
			output[i] = '0' + digit;
	}
	ft_putstr(output);
}

void				mask_32(uint64_t value, uint8_t type)
{
	if (!value)
	{
		if (type != N_UNDF)
			ft_putstr("00000000");
		else
			ft_putstr("        ");
		return ;
	}
	mask_32_2(value);
}