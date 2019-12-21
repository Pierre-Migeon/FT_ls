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
	DIR 		*dirp;
	struct dirent	*dp;
	//char		*path;

	//name = base_name();
	//path = base_path();
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

void	push_end_node(t_llist **list, char *name, char	*path)
{
	t_llist *next;
	t_llist *current;
	t_stat	*stats;

	if(!(next = (t_llist *)malloc(sizeof(t_llist))))
		exit(1);
	if(!(stats = (t_stat *)malloc(sizeof(t_stat))))
		exit(1);
	next->next = NULL;
	next->name = ft_strdup(name);
	if (stat(make_new_path(path, name), stats) != 0)
		exit(1);
	next->stat = stats;
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
			push_end_node(&list, argv[i], "./");
		++i;
	}
	return (list);
}

t_llist	*make_list(char **argv, t_llist *list, t_flags *flags, char *path)
{
	int 		i;
	DIR 		*dirp;
	struct dirent 	*dp;

	i = 0;
	if (argv && *argv)
		return (from_command_line(argv, list));
	dirp = opendir(path);
        while ((dp = readdir(dirp)))
	{
		if ((ft_strncmp(dp->d_name, ".", 1)) || flags->flags & 2)
			push_end_node(&list, dp->d_name, path);
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

void	print_permissions(t_llist *file)
{
	printf((S_ISDIR(file->stat->st_mode)) ? "d" : "-");
	printf((file->stat->st_mode & S_IRUSR) ? "r" : "-");
	printf((file->stat->st_mode & S_IWUSR) ? "w" : "-");
	printf((file->stat->st_mode & S_IXUSR) ? "x" : "-");
	printf((file->stat->st_mode & S_IRGRP) ? "r" : "-");
	printf((file->stat->st_mode & S_IWGRP) ? "w" : "-");
	printf((file->stat->st_mode & S_IXGRP) ? "x" : "-");
	printf((file->stat->st_mode & S_IROTH) ? "r" : "-");
	printf((file->stat->st_mode & S_IWOTH) ? "w" : "-");
	printf((file->stat->st_mode & S_IXOTH) ? "x" : "-");
	printf(" ");
}

void	print_group_name(t_llist *file)
{
	struct group *g;
	struct passwd *p;

	p = getpwuid(file->stat->st_uid);
	printf (" %s ", p->pw_name);	
	g = getgrgid(file->stat->st_gid);
	printf (" %s ", g->gr_name);
}

void	print_times(t_llist *files)
{
	char *time;
	
	time = ctime(&files->stat->st_mtime);
	printf ("%s", time);
}

void	long_print(t_llist *file)
{
	print_permissions(file);
	printf("%3d", file->stat->st_nlink);
	print_group_name(file);
	printf(" %5lld ", file->stat->st_size);
	print_times(file);
	printf("%s\n", file->name);
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
				long_print(list);
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
		free(head->stat);
		current = head;
		head = head->next;
		free(current);
	}
}

int	is_not_period(char *path)
{
	char *ptr;

	if ((ptr = ft_strrchr(path, '/')) && ++ptr)
		return (!(!(ft_strcmp(".", ptr)) || !(ft_strcmp("..", ptr))));
	return (!(!(ft_strcmp(".", path)) || !(ft_strcmp("..", path))));
}

int	is_directory(char *path) 
{
	struct stat statbuf;

	if (stat(path, &statbuf) != 0)
		return 0;
	return (S_ISDIR(statbuf.st_mode) && is_not_period(path));
}

char	*make_new_path(char *orig_path, char *directory)
{
	int	len;
	int	i;
	char	*out_path;

	i = 0;
	len = 2;
	len += ft_strlen(orig_path);
	len += ft_strlen(directory);
	if (!(out_path = (char *)malloc(sizeof(char) * len)))
		exit(0);
	while (*orig_path)
		*(out_path + i++) = *(orig_path++);
	//Hmmm... won't work on windows computers...
	*(out_path + i++) = '/';
	while (*directory)
		*(out_path + i++) = *(directory++);
	*(out_path + i) = '\0';
	return (out_path);
}

void    go_sub_dir(t_llist *list, t_flags *flags, char *path)
{
	char *new_path;

        while (list)
        {
		new_path = make_new_path(path, list->name);
		if (is_directory(new_path))
			ft_ls(NULL, flags, new_path);
		list = list->next;
		free(new_path);
	}
}

void	ft_ls(char **argv, t_flags *flags, char *path)
{
	t_llist *list = NULL;

	list = make_list(argv, list, flags, path);
        merge_sort(&list, flags);
	if (ft_strcmp(".", path))
		printf("\n%s:\n", path);
        print_list(list, flags);
	if (flags->flags & 8)
		go_sub_dir(list, flags, path);
	free_list(list);
}

int	main(int argc, char **argv)
{
	t_flags	*flags;
	int 	i;

	i = get_flags(argc, argv, &flags);
	ft_ls(argv + i, flags, ".");
	return (0);
}
