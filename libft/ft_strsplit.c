/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adacher <adacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/16 13:24:05 by adacher           #+#    #+#             */
/*   Updated: 2015/10/16 13:24:35 by adacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <string.h>

static int		is_del(char c, char ch)
{
	if (c == ch)
		return (1);
	return (0);
}

static int		find_nb_w(char *str, char ch)
{
	int result;

	result = 0;
	while (*str)
	{
		while (is_del(*str, ch) || is_del(*str, 9))
			str++;
		if (*str)
			result++;
		while (!is_del(*str, ch) && !is_del(*str, 9) && *str)
			str++;
	}
	return (result);
}

static char		**split_func(char *str, int nb_words, int *i, char ch)
{
	int		i3;
	int		word_size;
	char	**result;

	if (!(result = malloc(sizeof(char*) * (nb_words + 1))))
		return (NULL);
	while (i[0] < nb_words)
	{
		while (is_del(str[i[1]], ch) || is_del(str[i[1]], 9))
			i[1]++;
		word_size = 0;
		while (!is_del(str[i[1] + word_size], ch) &&
				str[i[1] + word_size] && !is_del(str[i[1] + word_size], 9))
			word_size++;
		if (!(result[i[0]] = malloc(sizeof(char) * (word_size + 1))))
			return (NULL);
		i3 = -1;
		while (++i3 < word_size)
			result[i[0]][i3] = str[i[1] + i3];
		result[i[0]][i3] = '\0';
		i[1] += word_size;
		i[0]++;
	}
	result[i[0]] = (NULL);
	return (result);
}

char			**ft_strsplit(char const *s, char c)
{
	int		i[2];
	char	ch[2];
	char	**arr;

	ch[0] = c;
	ch[1] = '\0';
	arr = NULL;
	if (!s || !(*s) || !c)
		return (NULL);
	if (!ft_strstr(s, ch))
	{
		arr = malloc(sizeof(*arr) * 2);
		arr[0] = ft_strdup(s);
		arr[1] = NULL;
		return (arr);
	}
	if (s && c)
	{
		i[0] = 0;
		i[1] = 0;
		return (split_func((char*)s, find_nb_w((char*)s, c), i, c));
	}
	return (NULL);
}
