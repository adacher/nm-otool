#include <ft_nm.h>

static void	sorted_insert(t_symdata **slist, t_symdata *new)
{
	t_symdata	*ptr;

	if (*slist == NULL || ft_strcmp((*slist)->str, new->str) >= 0)
	{
		new->next = *slist;
		*slist = new;
	}
	else
	{
		ptr = *slist;
		while (ptr->next && ft_strcmp(ptr->next->str, new->str) < 0)
			ptr = ptr->next;
		new->next = ptr->next;
		ptr->next = new;
	}
}

void		insertion_sort(t_symdata **slist)
{
	t_symdata	*sorted;
	t_symdata	*ptr;
	t_symdata	*tmp;

	sorted = NULL;
	ptr = *slist;
	while (ptr)
	{
		tmp = ptr->next;
		sorted_insert(&sorted, ptr);
		ptr = tmp;
	}
	*slist = sorted;
}