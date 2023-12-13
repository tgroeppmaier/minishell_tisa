/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exit_code.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgroeppm <tgroeppm@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 21:48:15 by tgroeppm          #+#    #+#             */
/*   Updated: 2023/12/13 14:19:32 by aminakov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/*static int	calculate_new_len(const char *str, int i, char *exit_code_str)
{
	if (!str[i])
		return (0);
	if (str[i] == '$' && str[i + 1] == '?' && !in_single_quotes(str, i))
		return (ft_strlen(exit_code_str) + calculate_new_len(str, i + 2,
				exit_code_str));
	return (1 + calculate_new_len(str, i + 1, exit_code_str));
}*/

/*static void	create_new_str(t_CreateNewStrArgs args, int i)
{
	if (!args.str[i])
	{
		args.new_str[*args.j] = '\0';
		return ;
	}
	if (args.str[i] == '$' && args.str[i + 1] == '?'
		&& !in_single_quotes(args.str, i))
	{
		ft_strlcpy(&args.new_str[*args.j], args.exit_code_str,
			ft_strlen(args.exit_code_str) + 1);
		*args.j += ft_strlen(args.exit_code_str);
		create_new_str(args, i + 2);
		return ;
	}
	args.new_str[(*args.j)++] = args.str[i];
	create_new_str(args, i + 1);
}*/

// char	*expand_exit_code(const char *str, char *exit_code_str, int i)
// {
// 	char	*rest;
// 	size_t	exit_code_str_len;
// 	size_t	rest_len;
// 	char	*result;

// 	if (!str[i])
// 		return (ft_strdup(""));
// 	if (str[i] == '$' && str[i + 1] == '?' && !in_single_quotes(str, i))
// 	{
// 		rest = expand_exit_code(str, exit_code_str, i + 2);
// 		exit_code_str_len = ft_strlen(exit_code_str);
// 		rest_len = ft_strlen(rest);
// 		result = malloc(exit_code_str_len + rest_len + 1);
// 		ft_strlcpy(result, exit_code_str, exit_code_str_len + 1);
// 		ft_strlcat(result, rest, exit_code_str_len + rest_len + 1);
// 		free(rest);
// 		return (result);
// 	}
// 	else
// 	{
// 		rest = expand_exit_code(str, exit_code_str, i + 1);
// 		rest_len = ft_strlen(rest);
// 		result = malloc(rest_len + 2);
// 		result[0] = str[i];
// 		ft_strlcpy(result + 1, rest, rest_len + 1);
// 		free(rest);
// 		return (result);
// 	}
// }

static char	*expand_exit_code_rest(const char *str, char *exit_code_str, int i)
{
	char	*rest;
	size_t	rest_len;
	char	*result;

	rest = expand_exit_code(str, exit_code_str, i + 1);
	rest_len = ft_strlen(rest);
	result = malloc(rest_len + 2);
	result[0] = str[i];
	ft_strlcpy(result + 1, rest, rest_len + 1);
	free(rest);
	return (result);
}

char	*expand_exit_code(const char *str, char *exit_code_str, int i)
{
	char	*rest;
	size_t	exit_code_str_len;
	size_t	rest_len;
	char	*result;

	if (!str[i])
		return (ft_strdup(""));
	if (str[i] == '$' && str[i + 1] == '?' && !in_single_quotes(str, i))
	{
		rest = expand_exit_code(str, exit_code_str, i + 2);
		exit_code_str_len = ft_strlen(exit_code_str);
		rest_len = ft_strlen(rest);
		result = malloc(exit_code_str_len + rest_len + 1);
		ft_strlcpy(result, exit_code_str, exit_code_str_len + 1);
		ft_strlcat(result, rest, exit_code_str_len + rest_len + 1);
		free(rest);
		return (result);
	}
	else
		return (expand_exit_code_rest(str, exit_code_str, i));
}

void	expand_exit(t_tree *tree, int exit_code)
{
	t_list	*current;
	char	exit_code_str[12];
	char	*str_ptr;
	char	*expanded;

	if (!tree)
		return ;
	sprintf(exit_code_str, "%d", exit_code);
	str_ptr = ft_itoa(exit_code);
	if (NULL == str_ptr)
	{
		print_error(1, "failed ft_itoa in exit_code expansion");
		return ;
	}
	ft_strlcpy(exit_code_str, str_ptr, ft_strlen(str_ptr) + 1);
	do_free_str(&str_ptr);
	current = tree->list;
	while (current)
	{
		expanded = expand_exit_code(current->word, exit_code_str, 0);
		free(current->word);
		current->word = expanded;
		current = current->next;
	}
}
