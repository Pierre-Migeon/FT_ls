#include <dirent.h>
#include <stdio.h>



int	main()
{
	DIR *directory;
	struct dirent *files;

	directory = opendir(".");
	
	while((files = readdir(directory)))
	{
		printf("The first file is %s\n", files->d_name);
	}
	closedir(directory);

	return (0);
}
