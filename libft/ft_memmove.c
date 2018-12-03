/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adacher <adrien_1109@hotmail.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/17 05:25:00 by adacher           #+#    #+#             */
/*   Updated: 2015/02/17 05:25:01 by adacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memmove(void *dest, const void *src, size_t n)
{
	char	tmp[n];
	char	*pdest;
	char	*psrc;
	size_t	i;

	i = 0;
	pdest = (char *)dest;
	psrc = (char *)src;
	if (n == 0)
		return (0);
	while (i < n)
	{
		tmp[i] = psrc[i];
		i++;
	}
	i = 0;
	while (i < n)
	{
		pdest[i] = tmp[i];
		i++;
	}
	return (pdest);
}
