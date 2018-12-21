#include <ft_nm.h>

static int check_list_three(t_data *tmp, t_data *init)
{
	if (!tmp->next)
	{
		tmp->next = init;
		return (0);
	}
	return (-1);
}

static int check_list_four(t_data *tmp, t_data *init)
{
	if (ft_strcmp(tmp->next->str, init->str) > 0)
	{
		init->next = tmp->next;
		tmp->next = init;
		return (0);
	}
	return (-1);
}

static int check_list_five(t_data *tmp, t_data *init)
{
	if (ft_strcmp(tmp->next->str, init->str) == 0)
	{
		if (tmp->next->value > init->value)
		{
			init->next = tmp->next;
			tmp->next = init;
			return (0);
		}
	}
	return (-1);
}

int		further_fill(t_data *tmp, t_data *init)
{
	int i;

	i = -1;
	while (tmp)
	{
		if (!(check_list_three(tmp, init)))
		{
			i = 0;
			break ;
		}
		if (!(check_list_four(tmp, init)))
		{
			i = 0;
			break ;
		}
		if (!(check_list_five(tmp, init)))
		{
			i = 0;
			break ;
		}
		tmp = tmp->next;
	}
	return (i);
}