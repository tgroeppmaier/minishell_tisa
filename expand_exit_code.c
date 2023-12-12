/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exit_code.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgroeppm <tgroeppm@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 21:48:15 by tgroeppm          #+#    #+#             */
/*   Updated: 2023/12/12 12:39:18 by tgroeppm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	calculate_new_len(const char *str, int i, char *exit_code_str)
{
    if (!str[i])
        return (0);
    if (str[i] == '$' && str[i + 1] == '?' && !in_single_quotes(str, i))
        return (ft_strlen(exit_code_str) + calculate_new_len(str, i + 2, exit_code_str));
    return (1 + calculate_new_len(str, i + 1, exit_code_str));
}

void	create_new_str(CreateNewStrArgs args, int i)
{
    if (!args.str[i])
    {
        args.new_str[*args.j] = '\0';
        return ;
    }
    if (args.str[i] == '$' && args.str[i + 1] == '?' && !in_single_quotes(args.str, i))
    {
        ft_strlcpy(&args.new_str[*args.j], args.exit_code_str, ft_strlen(args.exit_code_str) + 1);
        *args.j += ft_strlen(args.exit_code_str);
        create_new_str(args, i + 2);
        return ;
    }
    args.new_str[(*args.j)++] = args.str[i];
    create_new_str(args, i + 1);
}

char* expand_exit_code(const char *str, char *exit_code_str, int i)
{
    if (!str[i])
        return ft_strdup("");
    
    if (str[i] == '$' && str[i + 1] == '?' && !in_single_quotes(str, i))
    {
        char *rest = expand_exit_code(str, exit_code_str, i + 2);
        size_t exit_code_str_len = ft_strlen(exit_code_str);
        size_t rest_len = ft_strlen(rest);
        char *result = malloc(exit_code_str_len + rest_len + 1);
        ft_strlcpy(result, exit_code_str, exit_code_str_len + 1);
        ft_strlcat(result, rest, exit_code_str_len + rest_len + 1);
        free(rest);
        return result;
    }
    else
    {
        char *rest = expand_exit_code(str, exit_code_str, i + 1);
        size_t rest_len = ft_strlen(rest);
        char *result = malloc(rest_len + 2);
        result[0] = str[i];
        ft_strlcpy(result + 1, rest, rest_len + 1);
        free(rest);
        return result;
    }
}

void	expand_exit(t_tree *tree, int exit_code)
{
    t_list	*current;
    char	exit_code_str[12];

    if (!tree)
        return ;
    sprintf(exit_code_str, "%d", exit_code);
    current = tree->list;
    while (current)
    {
        char *expanded = expand_exit_code(current->word, exit_code_str, 0);
        free(current->word);
        current->word = expanded;
        current = current->next;
    }
}

// int	calculate_new_len(const char *str, int i, char *exit_code_str)
// {
// 	if (!str[i])
// 		return (0);
// 	if (str[i] == '$' && str[i + 1] == '?' && !in_single_quotes(str, i))
// 	{
// 		return (ft_strlen(exit_code_str) + calculate_new_len(str, i + 2,
// 				exit_code_str));
// 	}
// 	else
// 		return (1 + calculate_new_len(str, i + 1, exit_code_str));
// }

// void	create_new_str(const char *str, char *new_str, int i, int *j,
// 		char *exit_code_str)
// {
// 	if (!str[i])
// 	{
// 		new_str[*j] = '\0';
// 		return ;
// 	}
// 	if (str[i] == '$' && str[i + 1] == '?' && !in_single_quotes(str, i))
// 	{
// 		ft_strcpy(&new_str[*j], exit_code_str);
// 		*j += ft_strlen(exit_code_str);
// 		create_new_str(str, new_str, i + 2, j, exit_code_str);
// 	}
// 	else
// 	{
// 		new_str[(*j)++] = str[i];
// 		create_new_str(str, new_str, i + 1, j, exit_code_str);
// 	}
// }

// char* expand_exit_code_rest(const char *str, char *exit_code_str, int i)
// {
//     char *rest = expand_exit_code(str, exit_code_str, i + 1);
//     size_t rest_len = ft_strlen(rest);
//     char *result = malloc(rest_len + 2);
//     result[0] = str[i];
//     ft_strlcpy(result + 1, rest, rest_len + 1);
//     free(rest);
//     return result;
// }




// void	expand_exit(t_tree *tree, int exit_code)
// {
// 	t_list	*current;
// 	char	*expanded;

// 	if (!tree)
// 		return ;
// 	current = tree->list;
// 	while (current)
// 	{
// 		expanded = expand_exit_code(current->word, exit_code, 0);
// 		if (!expanded)
// 		{
// 			ft_printf_fd(2, "error exit code expansion\n");
// 			return ;
// 		}
// 		free(current->word);
// 		current->word = expanded;
// 		current = current->next;
// 	}
// }


// char	*expand_exit_code(const char *str, int exit_code)
// {
//     int		new_len;
//     char	*new_str;
//     int		j;
//     char	exit_code_str[12];
//     char    *exit_code_itoa;

//     if (!str)
//         return (NULL);
//     exit_code_str[0] = '\0';
//     exit_code_itoa = ft_itoa(exit_code);
//     if (!exit_code_itoa)
//         return (NULL);
//     ft_strlcat(exit_code_str, exit_code_itoa, 12);
//     new_len = calculate_new_len(str, 0, exit_code_str);
//     new_str = malloc(new_len + 1);
//     if (!new_str)
//     {
//         free(exit_code_itoa);
//         return (NULL);
//     }
//     j = 0;
//     create_new_str(str, new_str, 0, &j, exit_code_str);
//     free(exit_code_itoa);
//     return (new_str);
// }

// char* expand_exit_code(const char *str, char *exit_code_str, int i)
// {
//     if (!str[i])
//         return strdup("");
    
//     if (str[i] == '$' && str[i + 1] == '?' && !in_single_quotes(str, i))
//     {
//         char *rest = expand_exit_code(str, exit_code_str, i + 2);
//         char *result = malloc(strlen(exit_code_str) + strlen(rest) + 1);
//         strcpy(result, exit_code_str);
//         strcat(result, rest);
//         free(rest);
//         return result;
//     }
//     else
//     {
//         char *rest = expand_exit_code(str, exit_code_str, i + 1);
//         char *result = malloc(strlen(rest) + 2);
//         result[0] = str[i];
//         strcpy(result + 1, rest);
//         free(rest);
//         return result;
//     }
// }
