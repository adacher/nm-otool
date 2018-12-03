/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adacher <adrien_1109@hotmail.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/17 04:57:37 by adacher           #+#    #+#             */
/*   Updated: 2015/02/17 04:57:38 by adacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrchr(const char *s, int c)
{
	int i;
	int mem;

	i = 0;
	mem = -1;
	if (!s)
		return (NULL);
	while (s[i] != '\0')
	{
		if ((char)c == s[i])
			mem = i;
		i++;
	}
	if (c == '\0' && s[i] == '\0')
		return ((char*)&s[i]);
	if (mem != -1)
		return ((char *)&s[mem]);
	return (NULL);
}
