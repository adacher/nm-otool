/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tablen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adacher <adrien_1109@hotmail.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/13 02:14:14 by adacher           #+#    #+#             */
/*   Updated: 2015/03/13 02:16:47 by adacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tablen(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
