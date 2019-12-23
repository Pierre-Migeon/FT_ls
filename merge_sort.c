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

t_llist *merge_lists(t_llist *a, t_llist *b, t_compare_func compare)
{
	t_llist *head;

	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if (compare(a, b) && (head = a))
		a->next = merge_lists(a->next, b, compare);
	else if ((head = b))
		b->next = merge_lists(a, b->next, compare);
	return (head);
}

t_compare_func	get_comp_function(t_flags *flags)
{
	if (flags->flags & 16)
		return ((flags->flags & 4) ? &rev_timesort : &time_sort);
	return ((flags->flags & 4) ? &rev_alphasort : &alpha_sort);
}

void	merge_sort(t_llist **list, t_flags *flags)
{
	int		block_size;
	t_llist 	*a;
	t_llist 	*b;
	t_compare_func	compare;

	if (!*list || !(*list)->next)
		return;
	block_size = (*list)->blocks;
	split_list(*list, &a, &b);
	merge_sort(&a, flags);
	merge_sort(&b, flags);
	compare = get_comp_function(flags);
	*list = merge_lists(a, b, compare);
	(*list)->blocks = block_size;
}
