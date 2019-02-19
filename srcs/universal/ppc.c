#include <universal.h>

uint64_t		ppc_64(uint64_t n)
{
	uint8_t	ppc;

	ppc = *get_ppc();
	if (ppc != 0)
		return (swap_64(n));
	return (n);
}

uint32_t		ppc_32(uint32_t n)
{
	uint8_t	ppc;

	ppc = *get_ppc();
	if (ppc != 0)
		return (swap_32(n));
	return (n);
}

uint8_t	*get_ppc(void)
{
	static u_int8_t	ppc = 0;

	return (&ppc);
}

void			set_ppc(u_int8_t ppc)
{
	*get_ppc() = ppc;
}