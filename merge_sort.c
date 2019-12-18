#include "ft_ls.h"

void	split_list(t_llist *list, t_llist **slow, t_llist **fast)
{
	*slow = list;
	*fast = list->next;

	while((*fast)->next)
	{
		*slow = (*slow)->next;
		*fast = (*fast)->next;
		if ((*fast)->next)
			*fast = (*fast)->next;
	}
	*fast = (*slow)->next;
	(*slow)->next = NULL;
	*slow = list;
}

t_llist *merge_lists(t_llist *a, t_llist *b, t_flags *flags)
{
	t_llist *head;

	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if (((flags->flags & 4) >> 2) ^ (ft_strcmp(a->name, b->name) < 0))
	{
		a->next = merge_lists(a->next, b, flags);
		head = a;
	}
	else
	{
		b->next = merge_lists(a, b->next, flags);
		head = b;
	}
	return (head);
}

void	merge_sort(t_llist **list, t_flags *flags)
{
	t_llist *a;
	t_llist *b;

	if (!*list || !(*list)->next)
		return;
	split_list(*list, &a, &b);
	merge_sort(&a, flags);
	merge_sort(&b, flags);
	*list = merge_lists(a, b, flags);
}
