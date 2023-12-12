/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exit_code.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgroeppm <tgroeppm@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 21:48:15 by tgroeppm          #+#    #+#             */
/*   Updated: 2023/12/12 08:44:06 by tgroeppm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	calculate_new_len(const char *str, int i, char *exit_code_str)
{
	if (!str[i])
		return (0);
	if (str[i] == '$' && str[i + 1] == '?' && !in_single_quotes(str, i))
	{
		return (strlen(exit_code_str) + calculate_new_len(str, i + 2,
				exit_code_str));
	}
	else
		return (1 + calculate_new_len(str, i + 1, exit_code_str));
}

void	create_new_str(const char *str, char *new_str, int i, int *j,
		char *exit_code_str)
{
	if (!str[i])
	{
		new_str[*j] = '\0';
		return ;
	}
	if (str[i] == '$' && str[i + 1] == '?' && !in_single_quotes(str, i))
	{
		strcpy(&new_str[*j], exit_code_str);
		*j += strlen(exit_code_str);
		create_new_str(str, new_str, i + 2, j, exit_code_str);
	}
	else
	{
		new_str[(*j)++] = str[i];
		create_new_str(str, new_str, i + 1, j, exit_code_str);
	}
}

char	*expand_exit_code(const char *str, int exit_code)
{
    int		new_len;
    char	*new_str;
    int		j;
    char	exit_code_str[12];
    char    *exit_code_itoa;

    if (!str)
        return (NULL);
    exit_code_str[0] = '\0';
    exit_code_itoa = ft_itoa(exit_code);
    if (!exit_code_itoa)
        return (NULL);
    ft_strlcat(exit_code_str, exit_code_itoa, 12);
    new_len = calculate_new_len(str, 0, exit_code_str);
    new_str = malloc(new_len + 1);
    if (!new_str)
    {
        free(exit_code_itoa);
        return (NULL);
    }
    j = 0;
    create_new_str(str, new_str, 0, &j, exit_code_str);
    free(exit_code_itoa);
    return (new_str);
}

void	expand_exit(t_tree *tree, int exit_code)
{
	t_list	*current;
	char	*expanded;

	if (!tree)
		return ;
	current = tree->list;
	while (current)
	{
		expanded = expand_exit_code(current->word, exit_code);
		if (!expanded)
		{
			ft_printf_fd(2, "error exit code expansion\n");
			return ;
		}
		free(current->word);
		current->word = expanded;
		current = current->next;
	}
}
