#include <ft_nm.h>

static int check_list_one(t_data *tmp, t_data *init, t_data **info)
{
	if (ft_strcmp(tmp->str, init->str) > 0)
	{
		init->next = tmp;
		*info = init;
		return (0);
	}
	return (-1);
}

static int check_list_two(t_data *tmp, t_data *init, t_data **info)
{
	if (!(ft_strcmp(tmp->str, init->str)))
	{
		if (tmp->value > init->value)
		{
			init->next = tmp;
			*info = init;
			return (0);
		}
	}
	return (-1);
}

static int		fill_list(t_data **info, t_data *tmp, t_data *init)
{
	if (!(check_list_one(tmp, init, info)))
		return (0);
	else if (!(check_list_two(tmp, init, info)))
		return (0);
	else if (!(further_fill(tmp, init)))
		return (0);
	else
		return (-1);
}

void			create_64(t_data **info, char *str, struct nlist_64 array) //str bug cant access memory
{
	t_data *init;
	t_data *tmp;

	tmp = *info;
	init = (t_data*)malloc(sizeof(t_data));
	init->value = array.n_value;
	init->type = array.n_type;
	init->sect = array.n_sect;
	init->str = str;
	init->next = NULL;
	if (!*info)
		*info = init;
	else
	{
		if (fill_list(info, tmp, init) != 0)
			return ;
	}
}