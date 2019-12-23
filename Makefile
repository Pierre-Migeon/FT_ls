

make:
	gcc -g -Wall -Wextra -Werror main.c merge_sort.c ./comparison_functions.c ./libft.a -o ft_ls
clean:
	rm ./ft_ls 
	rm -rf ./*.dSYM
