

#include <stdio.h>




int	main(int argc, char **argv)
{
	if (argc == 0)
		return (1);
	
	if (*(argv + argc))
		printf ("Argv is %s\n", argv[argc - 1]);
	return (0);
}	
