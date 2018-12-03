/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adacher <adrien_1109@hotmail.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/17 04:13:22 by adacher           #+#    #+#             */
/*   Updated: 2015/02/17 04:13:23 by adacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	if (!s2 || !s2[0])
		return ((char *)s1);
	while (s1[j] != '\0' && j < n)
	{
		i = 0;
		while (s2[i] == s1[j + i] && j + i < n && s2[i] != '\0'
				&& s1[j + i] != '\0')
			i++;
		if (s2[i] == '\0')
			return ((char *)s1 + j);
		j++;
	}
	return (0);
}
