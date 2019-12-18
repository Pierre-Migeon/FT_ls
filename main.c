#include "ft_ls.h"

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

int	get_flags(int argc, char **argv, t_flags **flags)
{
	int i;
	int j;

	if (!(*flags = (t_flags *)malloc(sizeof(t_flags))))
        	exit(1);
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
				flip_flags(argv[i][j], *flags);
				++j;
			}
		}
		else
			return (i);
		++i;
	}
	return (i);
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

void	push_end_node(t_llist **list, char *name)
{
	t_llist *next;
	t_llist *current;

	if(!(next = (t_llist *)malloc(sizeof(t_llist))))
		exit(1);
	next->next = NULL;
	next->name = ft_strdup(name);
	current = *list;
	while (current && current->next)
		current = current->next;
	if (current == NULL)
		*list = next;
	else
		current->next = next;
}

t_llist	*from_command_line(char **argv, t_llist *list)
{
	int i;

	i = 0;
	while (argv[i])
	{
		if(does_it_exist(argv[i]))
			no_such_file(argv[i]);
		else
			push_end_node(&list, argv[i]);
		++i;
	}
	return (list);
}

t_llist	*make_list(char **argv, t_llist *list, t_flags *flags)
{
	int 		i;
	DIR 		*dirp;
	struct dirent 	*dp;

	i = 0;
	if (*argv)
		return (from_command_line(argv, list));
	dirp = opendir(".");
        while ((dp = readdir(dirp)))
	{
		if ((ft_strncmp(dp->d_name, ".", 1)) || flags->flags & 2)
			push_end_node(&list, dp->d_name);
	}
	closedir(dirp);
	return (list);
}

void	swap_list(t_llist *head)
{
	char *tmp;

	tmp = head->name;
	head->name = head->next->name;
	head->next->name = tmp;
}

void	print_list(t_llist *list, t_flags *flags)
{
	int i;
	int j;
	t_llist *head;

	i = 0;
	head = list;
	if (flags->flags & 1)
		printf ("total \n");
	while (i < 2)
	{
		j = 0;
		while(list)
		{
			if (j % 2 == i && ((flags->flags & 1) ^ 1))
				printf("%-16s", list->name);
			if (flags->flags & 1)
				printf("         %s\n", list->name);
			list = list->next;
			++j;
		}
		i += (flags->flags & 1) ? 2 : 1;
		list = head;
		if (!(flags->flags & 1))
			printf("\n");
	}
}

void	free_list(t_llist *head)
{
	t_llist *current;

	while (head)
	{
		free(head->name);
		current = head;
		head = head->next;
		free(current);
	}
}

void	ft_ls(char **argv, t_flags *flags)
{
	t_llist *list;

	list = NULL;
	list = make_list(argv, list, flags);
        merge_sort(&list, flags);
        print_list(list, flags);
        free_list(list);
}

int	main(int argc, char **argv)
{
	t_flags	*flags;
	int 	i;

	i = get_flags(argc, argv, &flags);
	ft_ls(argv + i, flags);
	return (0);
}
