/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adacher <adrien_1109@hotmail.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/17 05:07:24 by adacher           #+#    #+#             */
/*   Updated: 2016/02/04 11:43:59 by adacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		i;
	char	*yolo;

	i = 0;
	if (s != 0 && (*f) != 0)
	{
		yolo = (char*)ft_memalloc(ft_strlen(s) + 1);
		if (!yolo)
			return (NULL);
		while (s[i] != '\0')
		{
			yolo[i] = (*f)(s[i]);
			i++;
		}
		return (yolo);
	}
	return (0);
}
