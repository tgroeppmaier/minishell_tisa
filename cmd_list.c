#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

t_command	*ft_lstlast(t_command *lst)
{
	t_command	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	ft_lstadd_back(t_command **lst, t_command *new)
{
	t_command	*tmp;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = ft_lstlast(*lst);
	tmp->next = new;
}

t_command	*ft_lstnew(void *content)
{
	t_command	*s1;

	s1 = malloc(sizeof(t_command));
	if (!s1)
		return (NULL);
	s1->cmd = content;
	s1->next = NULL;
	return (s1);
}

void print_list(t_command *node)
{
	int i = 1;

	while(node)
	{
		printf("Node %d: %s\n", i, node->cmd);
		node = node->next;
		i++;
	}
}

void free_cmd_list(t_command *head)
{
    t_command *tmp;
	t_command *save = head;

    while (head != NULL)
	{
        tmp = head;
        head = head->next;
        free(tmp->cmd);  // Assuming cmd was dynamically allocated
        free(tmp);
    }
	// free(save);
}

void new_cmdl_node(t_command **node, char *cmdl)
{
    t_command *new;

    if (node == NULL) {
        return;
    }

    new = ft_lstnew(cmdl);
    ft_lstadd_back(node, new);
}

