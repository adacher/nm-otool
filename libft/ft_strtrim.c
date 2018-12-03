/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adacher <adrien_1109@hotmail.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/17 05:48:31 by adacher           #+#    #+#             */
/*   Updated: 2015/02/17 05:48:33 by adacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_blank(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

static int	end_blanks(char const *s, size_t len)
{
	size_t i;

	i = 0;
	while (is_blank(s[len]))
	{
		i++;
		len--;
	}
	return (i);
}

char		*ft_strtrim(char const *s)
{
	size_t	i;
	size_t	nblanks_start;
	size_t	nblanks_end;
	size_t	len;
	char	*newstr;

	i = 0;
	if (!s)
		return (NULL);
	len = ft_strlen(s) - 1;
	while (is_blank(s[i]))
		i++;
	nblanks_start = i;
	nblanks_end = end_blanks(s, len);
	if (ft_strlen(s) == nblanks_start)
	{
		newstr = (char *)ft_memalloc(sizeof(char));
		if (!newstr)
			return (NULL);
		newstr[0] = '\0';
		return (newstr);
	}
	newstr = ft_strsub(s, nblanks_start, (ft_strlen(s) - (nblanks_end +
		nblanks_start)));
	return (newstr);
}
