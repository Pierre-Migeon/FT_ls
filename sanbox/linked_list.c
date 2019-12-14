#include <stdlib.h>
#include <stdio.h>

typedef struct s_llist
{
	int data;
	struct s_llist *next;
}	t_llist;

void	push(t_llist **list, int data)
{
	t_llist *new;
	t_llist *current;

	new = (t_llist *)malloc(sizeof(t_llist));
	new->data = data;
	new->next = NULL;

	current = *list;
	while(current && current->next)
		current = current->next;
	if (current == NULL)
		*list = new;
	else
		current->next = new;
}

void	print_list(t_llist *head)
{
	while (head)
	{
		printf("Value is %i\n", head->data);
		head = head->next;	
	}
}

int	main()
{
	t_llist *list;

	list = NULL;
	push(&list, 5);
	push(&list, 10);
	push(&list, 15);
	push(&list, 20);
	push(&list, 5);
	push(&list, 10);
	
	print_list(list);


	return (0);
}
