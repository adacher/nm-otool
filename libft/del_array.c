/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adacher <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 11:40:12 by adacher           #+#    #+#             */
/*   Updated: 2016/02/04 11:40:17 by adacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	del_array(char ***array)
{
	int		i;
	char	**tmp;

	tmp = *array;
	i = 0;
	if (tmp)
	{
		while (tmp && tmp[i])
		{
			ft_strdel(&tmp[i]);
			i++;
		}
		free(tmp);
		tmp = NULL;
	}
}
