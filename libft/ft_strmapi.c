/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adacher <adrien_1109@hotmail.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/17 05:10:23 by adacher           #+#    #+#             */
/*   Updated: 2016/02/04 11:43:49 by adacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*yolo;
	int		i;

	i = 0;
	if (s != 0 && (*f) != 0)
	{
		yolo = (char*)ft_memalloc(ft_strlen(s) + 1);
		if (!yolo)
			return (NULL);
		while (s[i] != '\0')
		{
			yolo[i] = (*f)(i, s[i]);
			i++;
		}
		return (yolo);
	}
	return (0);
}
