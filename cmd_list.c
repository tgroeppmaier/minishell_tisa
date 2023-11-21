#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

t_cmd_line	*ft_lstlast(t_cmd_line *lst)
{
	t_cmd_line	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	ft_lstadd_back(t_cmd_line **lst, t_cmd_line *new)
{
	t_cmd_line	*tmp;

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

t_cmd_line	*ft_lstnew(void *content)
{
	t_cmd_line	*s1;

	s1 = malloc(sizeof(t_cmd_line));
	if (!s1)
		return (NULL);
	s1->cmd = content;
	s1->next = NULL;
	return (s1);
}

void print_list(t_cmd_line *node)
{
	int i = 1;

	while(node)
	{
		printf("Node %d: %s\n", i, node->cmd);
		node = node->next;
		i++;
	}
}

void free_cmd_list(t_cmd_line *head)
{
    t_cmd_line *tmp;
	t_cmd_line *save = head;

    while (head != NULL)
	{
        tmp = head;
        head = head->next;
        free(tmp->cmd);  // Assuming cmd was dynamically allocated
        free(tmp);
    }
	// free(save);
}

void new_cmdl_node(t_cmd_line **node, char *cmdl)
{
    t_cmd_line *new;

    if (node == NULL) {
        return;
    }

    new = ft_lstnew(cmdl);
    ft_lstadd_back(node, new);
}

