#include "ft_ls.h"

int     time_sort(t_llist *a, t_llist *b)
{
	if (a->stat->st_mtimespec.tv_sec == b->stat->st_mtimespec.tv_sec)
		return (a->stat->st_mtimespec.tv_nsec > b->stat->st_mtimespec.tv_nsec);
	return (a->stat->st_mtimespec.tv_sec > b->stat->st_mtimespec.tv_sec);
}

int	rev_timesort(t_llist *a, t_llist *b)
{
	return (1^(time_sort(a, b)));
}

int	rev_alphasort(t_llist *a, t_llist *b)
{
	return (ft_strcmp(a->name, b->name) > 0);
}

int	alpha_sort(t_llist *a, t_llist *b)
{
	return (ft_strcmp(a->name, b->name) < 0);
}

int	dir_vs_nondir_sort(t_llist *a, t_llist *b)
{
	return (!S_ISDIR(a->stat->st_mode) && S_ISDIR(b->stat->st_mode));
}
