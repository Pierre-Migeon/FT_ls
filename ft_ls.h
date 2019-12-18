
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>

typedef struct s_flags
{
	unsigned int flags : 5;
}	t_flags;

typedef struct		s_llist
{
	char 		*name;
	int		val;
	struct s_llist 	*next;
	struct s_llist	*last;
} 			t_llist;

int             ft_strncmp(const char *s1, const char *s2, size_t n);
void            ft_putstr(char *str);
int             ft_strcmp(const char *s1, const char *s2);
size_t		ft_strlen(const char *s);
char            *ft_strdup(const char *s1);
void		merge_sort(t_llist **list,  t_flags *flags);
void    	ft_ls(char **argv, t_flags *flags, char *path);
