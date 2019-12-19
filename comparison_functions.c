#include "ft_ls.h"

int	rev_timesort(t_llist *a, t_llist *b)
{
	return (a->stat->st_mtime < b->stat->st_mtime);
}

int	time_sort(t_llist *a, t_llist *b)
{
	return (a->stat->st_mtime > b->stat->st_mtime);	
}

int	rev_alphasort(t_llist *a, t_llist *b)
{
	return (ft_strcmp(a->name, b->name) > 0);
}

int	alpha_sort(t_llist *a, t_llist *b)
{
	return (ft_strcmp(a->name, b->name) < 0);
}
