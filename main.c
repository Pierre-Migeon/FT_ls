#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>

int		ft_strncmp(const char *s1, const char *s2, size_t n);
void		ft_putstr(char *str);
int		ft_strcmp(const char *s1, const char *s2);
char		*ft_strdup(const char *s1);

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

int	valid_flag(char c)
{
	return (c == 'l' || c == 'a' || c == 'r' || c == 'R' || c == 't');
}

void	no_such_file(char *file)
{
	write(1, "ft_ls: ", 7);
	ft_putstr(file);
	write(1, ": No such file or directory\n", 28); 
	return ;
}

void	usage(char c)
{
	write(1, "ft_ls: illegal option -- ", 25);
	write(1, &c, 1);
	write(1, "\nusage: ft_ls [-larRt] [file ...]\n", 34);
	exit (0);
}

void	flip_flags(char c, t_flags *flags)
{
	if (c == 'l')
		flags->flags |= 1;
	else if (c == 'a')
		flags->flags |= 2;
	else if (c == 'r')
		flags->flags |= 4;
	else if (c == 'R')
		flags->flags |= 8;
	else if (c == 't')
		flags->flags |= 16;
}

int	get_flags(int argc, char **argv, t_flags *flags)
{
	int i;
	int j;

	i = 1;
	while(i < argc)
	{
		j = 1;
		if (!(ft_strncmp("-", argv[i], 1)))
		{
			while (argv[i][j])
			{
				if(valid_flag(argv[i][j]) == 0)
					usage(argv[i][j]);
				flip_flags(argv[i][j], flags);
				++j;
			}
		}
		else
			return (i);
		++i;
	}
	return (i);
}

void	malloc_structs(t_flags **flags, t_llist **list)
{
	if (!(*flags = (t_flags *)malloc(sizeof(t_flags))))
		exit(1);
        if (!(*list = (t_llist *)malloc(sizeof(t_llist))))
		exit(1);
}

int	does_it_exist(char *name)
{
	DIR *dirp;
	struct dirent *dp;

	dirp = opendir(".");
	while ((dp = readdir(dirp))) 
	{
        	if (ft_strcmp(dp->d_name, name) == 0) 
		{
			closedir(dirp);
			return (0);
		}
	}
	closedir(dirp);
	return (1);
}

t_llist *new_node(void)
{
	t_llist *next;

	if(!(next = (t_llist *)malloc(sizeof(t_llist))))
		exit(1);
	next->next = NULL;
	return (next);
}

t_llist	*from_command_line(char **argv, t_llist *list)
{
	int i;
	t_llist *head;

	i = 0;
	head = list;
	while (argv[i])
	{
		if(does_it_exist(argv[i]))
			no_such_file(argv[i]);
		else
		{
			list->name = ft_strdup(argv[i]);
			list->next = new_node();
			list = list->next;
		}
		++i;
	}
	return (head);
}

t_llist	*make_list(char **argv, t_llist *list, t_flags *flags)
{
	int 		i;
	DIR 		*dirp;
	struct dirent 	*dp;
	t_llist 	*head;

	i = 0;
	if (*argv)
		return (from_command_line(argv, list));
	head = list;
	dirp = opendir(".");
        while ((dp = readdir(dirp)))
	{
		if ((ft_strncmp(dp->d_name, ".", 1)) || flags->flags & 2)
		{
			list->name = ft_strdup(dp->d_name);
			list->next = new_node();
			list = list->next;
		}
	}
	closedir(dirp);
	return (head);
}

void	swap(t_llist **last, t_llist **current)
{
	if (last)
	{
		(*last)->next = (*current)->next;
		(*current)->next = (*current)->next->next;
	}
}

void	sort_list(t_llist **list, t_flags *flags)
{
	t_llist *head;
	t_llist *last;
	int	go_ahead;

	head = *list;
	last = NULL;
	go_ahead = 1;
	while(go_ahead)
	{
		head = *list;
		go_ahead = 0;
		while (head->next)
		{
			if (ft_strcmp(list->name, list->next->name) > 0)
			{
				swap(&last, &list);
				go_ahead++;
			}
			last = list;
		:wq
	list = list->next;
		}
	}
}

int	main(int argc, char **argv)
{
	t_flags	*flags;
	t_llist *list;
	int 	i;

	malloc_structs(&flags, &list);
	i = get_flags(argc, argv, flags);
	//get info + make linked list
	list = make_list(argv + i, list, flags);
	while(list->next != NULL)
	{	
		printf ("%s\n", list->name);
		list = list->next;
	}	
	//sort linked list
	sort_list(&list, flags);
	//print linked list:
	//print_list();
	//free linked list
	//free_list(list);
	return (0);
}
