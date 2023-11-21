#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

t_token	*ft_word_lstlast(t_token *lst)
{
	t_token	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	ft_word_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*tmp;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = ft_word_lstlast(*lst);
	tmp->next = new;
}

t_token	*ft_word_lstnew(void *content)
{
	t_token	*s1;

	s1 = malloc(sizeof(t_token));
	if (!s1)
		return (NULL);
	s1->word = content;
	s1->next = NULL;
	return (s1);
}

void print_word_list(t_token *node)
{
	int i = 1;

	while(node)
	{
		printf("word: %d: %s\n", i, node->word);
		node = node->next;
		i++;
	}
}

void free_word_list(t_token *head)
{
    t_token *tmp;
	t_token *save = head;

    while (head != NULL)
	{
        tmp = head;
        head = head->next;
        free(tmp->word);  // Assuming cmd was dynamically allocated
        free(tmp);
    }
	// free(save);
}

void new_word_node(t_token **node, char *word)
{
    t_token *new;

    if (node == NULL) {
        return;
    }

    new = ft_word_lstnew(word);
    ft_word_lstadd_back(node, new);
}

