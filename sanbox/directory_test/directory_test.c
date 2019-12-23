#include <stdio.h>
#include "../../ft_ls.h"

char	*get_base_path(char *str)
{
        char *ptr_1;
        char *out;

        if(!(ptr_1 = ft_strrchr(str, '/')))
		return (ft_strdup("."));
        if (*(ptr_1 + 1) == '\0')
		return(ft_strdup(str));
	out = (char *)malloc(sizeof(char) * (size_t)(ptr_1 - str));
	out = ft_strncpy(out, str, ptr_1 - str);
	return (out);
}

char	*get_base_name(char *str)
{
        char *ptr_1;
	char *ptr_2;
	char *out;

        if (!(ptr_1 = ft_strrchr(str, '/')))
		return (ft_strdup(str));
        if (*(ptr_1 + 1) != '\0')
                return (ft_strdup(ptr_1 + 1));
	*ptr_1 = '\0';
	ptr_2 = ft_strrchr(str, '/');
	out = ft_strdup(ptr_2 + 1);
	*ptr_1 = '/';
	return (out);
}

int     does_it_exist(char *name)
{       
        DIR             *dirp;
        struct dirent   *dp;
        char            *path;
	char		*base_name;

        path = get_base_path(name);
        base_name = get_base_name(name);
	printf ("path is %s and name is %s\n", path, base_name);

        if (!(dirp = opendir(path)))
		printf("ft_ls: %s: Not a directory\n", path);
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


int	main(int argc, char **argv)
{
	if (argc > 1)
	{
		if (does_it_exist(argv[1]))
			printf("doesn't exist");
		else
			printf ("it does exist");
	}
	return (0);
}
