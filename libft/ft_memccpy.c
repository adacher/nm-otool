/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adacher <adrien_1109@hotmail.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/17 05:24:26 by adacher           #+#    #+#             */
/*   Updated: 2015/02/17 05:24:27 by adacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	char			*s1_;
	const char		*s2_;

	s2_ = src;
	s1_ = dst;
	while (n--)
	{
		if (*s2_ == c)
		{
			*s1_++ = *s2_++;
			return (s1_);
		}
		*s1_++ = *s2_++;
	}
	return (NULL);
}
