/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adacher <adrien_1109@hotmail.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/18 21:39:50 by adacher           #+#    #+#             */
/*   Updated: 2015/05/26 08:34:13 by adacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

static int		gnl_check_stock(char **stock, char **line)
{
	char			*tmp;

	if ((tmp = ft_strchr(*stock, '\n')))
	{
		*tmp = '\0';
		*line = ft_strdup(*stock);
		free(*stock);
		*stock = ft_strdup(tmp + 1);
		tmp = NULL;
		return (1);
	}
	return (0);
}

static int		gnl_check_read(char *buffer, char **stock, char **line)
{
	char			*tmp;

	if ((tmp = ft_strchr(buffer, '\n')))
	{
		*tmp = '\0';
		*line = ft_strjoin(*stock, buffer);
		free(*stock);
		*stock = ft_strdup(tmp + 1);
		tmp = NULL;
		free(buffer);
		return (1);
	}
	return (0);
}

int				get_next_line(int const fd, char **line)
{
	static char		*stock[256];
	char			*buffer;
	int				ret;

	if (!line || !(buffer = ft_strnew(BUFF_SIZE)))
		return (-1);
	if (stock[fd])
		if (gnl_check_stock(&stock[fd], line))
			return (1);
	while ((ret = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[ret] = '\0';
		if (gnl_check_read(buffer, &stock[fd], line))
			return (1);
		stock[fd] = ft_strjoin(stock[fd], buffer);
	}
	free(buffer);
	if (ret == -1 || line == NULL)
		return (-1);
	if (stock[fd] == NULL)
		return (0);
	*line = ft_strdup(stock[fd]);
	free(stock[fd]);
	stock[fd] = NULL;
	return (0);
}
