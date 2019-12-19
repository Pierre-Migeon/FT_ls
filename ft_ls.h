#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>

typedef struct  stat    t_stat;

typedef struct 		s_flags
{
	unsigned int flags : 5;
}			t_flags;

typedef struct		s_llist
{
	char 		*name;
	t_stat		*stat;
	struct s_llist 	*next;
} 			t_llist;

typedef int     (*t_compare_func)(t_llist *a, t_llist *b);

int	ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_putstr(char *str);
int	ft_strcmp(const char *s1, const char *s2);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
void	merge_sort(t_llist **list,  t_flags *flags);
void	ft_ls(char **argv, t_flags *flags, char *path);
char	*ft_strrchr(const char *s, int c);
int	rev_timesort(t_llist *a, t_llist *b);
int	time_sort(t_llist *a, t_llist *b);
int	rev_alphasort(t_llist *a, t_llist *b);
int	alpha_sort(t_llist *a, t_llist *b);
char    *make_new_path(char *orig_path, char *directory);
