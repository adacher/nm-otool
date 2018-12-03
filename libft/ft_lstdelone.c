/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adacher <adrien_1109@hotmail.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/18 08:59:32 by adacher           #+#    #+#             */
/*   Updated: 2015/02/18 08:59:34 by adacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		default_deleter(void *data, size_t size)
{
	(void)size;
	ft_memdel(&data);
}

void			ft_lstdelone(t_list **alst, void (*del)(void *, size_t))
{
	if (del == NULL)
		del = default_deleter;
	if (alst && *alst)
	{
		del((*alst)->content, (*alst)->content_size);
		ft_memdel((void **)alst);
	}
}
