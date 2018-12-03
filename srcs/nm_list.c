#include <ft_nm.h>

static void		push_list_next(t_data *tmp, t_data *new)
{
	while (tmp)
	{
		if (!tmp->next)
		{
			tmp->next = new;
			break ;
		}
		if (ft_strcmp(tmp->next->str, new->str) > 0)
		{
			new->next = tmp->next;
			tmp->next = new;
			break ;
		}
		if (ft_strcmp(tmp->next->str, new->str) == 0)
		{
			if (tmp->next->value > new->value)
			{
				new->next = tmp->next;
				tmp->next = new;
				break ;
			}
		}
		tmp = tmp->next;
	}
}

static void		push_list(t_data **lt, t_data *tmp, t_data *new)
{
	if (ft_strcmp(tmp->str, new->str) > 0)
	{
		new->next = tmp;
		*lt = new;
		return ;
	}
	if (ft_strcmp(tmp->str, new->str) == 0)
	{
		if (tmp->value > new->value)
		{
			new->next = tmp;
			*lt = new;
			return ;
		}
	}
	push_list_next(tmp, new);
}

void			add_list_64(t_data **lt, char *str, struct nlist_64 array)
{
	t_data *new;
	t_data *tmp;

	tmp = *lt;
	new = (t_data*)malloc(sizeof(t_data));
	new->value = array.n_value;
	new->type = array.n_type;
	new->sect = array.n_sect;
	new->str = str;
	new->next = NULL;
	if (!*lt)
		*lt = new;
	else
		push_list(lt, tmp, new);
}