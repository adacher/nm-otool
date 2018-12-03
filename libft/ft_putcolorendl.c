/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putcolorendl.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adacher <adacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/02 15:18:14 by adacher           #+#    #+#             */
/*   Updated: 2016/02/04 11:45:10 by adacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putcolorendl(char *color, char *s)
{
	ft_putstr(color);
	ft_putstr(s);
	ft_putstr(NORMAL);
	ft_putchar('\n');
}
