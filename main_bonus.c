#include "libasm_bonus.h"
#include "libasm.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static t_list	*new_node(char *s)
{
	t_list	*n;

	n = malloc(sizeof(*n));
	if (!n)
		return (NULL);
	n->data = strdup(s);
	if (!n->data)
	{
		free(n);
		return (NULL);
	}
	n->next = NULL;
	return (n);
}

static void	print_list(t_list *lst)
{
	while (lst)
	{
		printf("%s", (char *)lst->data);
		if (lst->next)
			printf(" -> ");
		lst = lst->next;
	}
	printf("\n");
}

static void	free_all(t_list *lst)
{
	t_list	*next;

	while (lst)
	{
		next = lst->next;
		free(lst->data);
		free(lst);
		lst = next;
	}
}

int	main(void)
{
	t_list	*lst;

	printf("ft_atoi_base(\"---1010\", \"01\") = %d\n", ft_atoi_base("---1010", "01"));
	printf("ft_atoi_base(\"7f\", \"0123456789abcdef\") = %d\n",
		ft_atoi_base("7f", "0123456789abcdef"));
	lst = new_node("world");
	ft_list_push_front(&lst, strdup("hello"));
	ft_list_push_front(&lst, strdup("42"));
	ft_list_push_front(&lst, strdup("hello"));
	printf("size = %d\n", ft_list_size(lst));
	print_list(lst);
	ft_list_sort(&lst, (int (*)())ft_strcmp);
	print_list(lst);
	ft_list_remove_if(&lst, "hello", (int (*)())ft_strcmp, free);
	print_list(lst);
	free_all(lst);
	return (0);
}
