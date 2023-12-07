#include "minishell.h"
#include "string.h"

/* returns true, if given index is in single quotes*/

bool	in_single_quotes(const char *str, int index)
{
	int		i;
	bool	in_single_quote;
	bool	in_double_quote;

	i = 0;
	in_single_quote = false;
	in_double_quote = false;
	if (str == NULL || index < 0)
		return (false);
	while (str[i] && i <= index)
	{
		if (str[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (str[i] == '\"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		i++;
	}
	return (in_single_quote);
}

int	get_varname_len(char *str)
{
	int	i;

	i = 0;
	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
	{
		return (0);
	}
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
	{
		i++;
	}
	return (i);
}
char	*get_var_name(char *str)
{
	int		len;
	char	*var_name;

	len = get_varname_len(str);
	if (len == 0)
		return (NULL);
	var_name = ft_strndup(str, len);
	return (var_name);
}

/* if first character after $ is not valid (A-Z,
	a-z or '_') it removes $ and that character
it takes the name as variable name,
	as long as the following characters are valid (A-Z, a-z, 0-9, '_' )
it takes out these characters and replaces it with the variable value. if the variable does not exist,
these characters will be deleted*/

int	get_expand_len(t_tree *tree, char *str)
{
	char	*var_name;
	char	*var_value;
	int		i;
	int		len;

	i = 0;
	len = 1;
	if(!str || !str[0])
		return(0);
	while (str[i])
	{
		if (str[i] != '$' || in_single_quotes(str, i))
		{
			i++;
			len++;
			continue ;
		}
		// i++;
		if (!str[++i])
			return (len);
		var_name = get_var_name(str + i);
		if(var_name == NULL) // means invalid char after $, we skip $ and that char
			i++;
		else
		{
			// ft_printf("var name: %s\n", var_name);
			var_value = ft_getenv(var_name, tree->data);
			if(var_value != NULL)
			{
				// ft_printf("var value: %s\n", var_value);
				len += ft_strlen(var_value);
			}
			i += ft_strlen(var_name);
			free(var_name);
		}
	}
	// ft_printf("total len = %d\n", len);
	return (len);
}


char	*get_expand_str(t_tree *tree, char *str)
{
	int		i;
	int		k;
	int		len;
	char	*var_name;
	char	*var_value;
	char	*expand;

	i = 0;
	k = 0;
	len = get_expand_len(tree, str);
	ft_printf("total len = %d\n", len);
	ft_printf("strlen: %d\n", ft_strlen(str));
	expand = (char *)malloc(sizeof(char) * (len + 1));
	expand[0] = '\0';
	while (k <= len && str[i])
	{
		ft_printf("begin loop str[i] = %c\n", str[i]);
		if (str[i] != '$' || in_single_quotes(str, i))
		{
			expand[k] = str[i];
			i++;
			k++;
			expand[k] = '\0';
			continue ;
		}
		i++;  // we move past $
		printf("k: %d, i: %d\n", k, i);
		var_name = get_var_name(str + i);
		ft_printf("var name: %s\n", var_name);
		if(var_name == NULL)
		{
			// i++;
			if(str[i] == '"' || str[i] == '\'')
			{
				ft_printf("are we getting here?\n");
				expand[k] = str[i];
				k++;
				i++;
				expand[k] = '\0';
			}
		} // means invalid char after $, we skip $ and that char
		else
		{
			var_value = ft_getenv(var_name, tree->data);
			if(var_value != NULL)
			{
				ft_printf("var value: %s\n", var_value);
				k = ft_strlcat(expand, var_value, len);
				ft_printf("k = %d\n", k);
				ft_printf("char = %c\n", expand[k]);
			}
			i += ft_strlen(var_name);
			ft_printf("i = %d\n", i);
			ft_printf("str[i] = %c\n", str[i]);
			free(var_name);
			// i++;
		}
	}
	expand[k] = '\0';
	return (expand);
}


void	expand_variables(t_tree *tree)
{
	t_list	*current;
	char	*tmp;

	current = tree->list;
	while (current)
	{
		tmp = get_expand_str(tree, current->word);
		if (tmp == NULL)
		{
			ft_printf_fd(2, "error expanding variables\n");
				// what to do in this case?
			current = current->next;
			continue ;
		}
		free(current->word);
		current->word = tmp;
		// ft_printf("current word: %s\n", current->word);
		current = current->next;
		// ft_printf("%s\n", current->word);    // for testing
	}
}



// void add_to_list(t_tree *tree, char *str, int beg, int end)
// {
// 	t_list *list;

// 	list = ft_lstnew(str, beg, end);
// 	ft_lstadd_back(&(tree->expand), list);
// }

// void test_list(t_tree *tree) {
//     char *str[] = {"one", "two", "three", NULL};  // Static array of strings
//     int i = 0;

//     while (str[i] != NULL) {
//         add_to_list(tree, str[i], 1, strlen(str[i])); 
	// Use strlen to get the length of each string
//         i++;
//     }
// }

// char *get_expand_variables(t_tree *tree, char *str)
// {
// 	char *buffer;
// 	char *var_name;
// 	char *var_value;
//     int i = 0;
// 	int k = 0;
// 	int len;

// 	if(str == NULL)
// 		return(NULL);
// 	if(strchr(str, '$') == NULL)
// 		return(ft_strdup(str));
// 	buffer = (char *)malloc(sizeof(char) * 1000);
// 	buffer[0] = '\0';
// 	while(str[i])
// 	{
// 		if(str[i] == '$' && not_in_single_quotes(str, i))
// 		{
// 			i++;
// 			// printf("str: %s\n", str);
// 			len = get_varname_len(str + i);
// 			// ft_printf("len: %d\n", len);
// 			var_name = ft_strndup(str + i, len);
// 			// ft_printf("var name: %s\n", var_name);
// 			var_value = ft_strdup(ft_getenv(var_name, tree->data));
// 			// ft_printf("var value: %s\n", var_value);
// 			k = ft_strlcat(buffer, var_value, 1000);
// 			i += len;
// 			free(var_name);
// 			free(var_value);
// 		}
// 		else
// 		{
// 			buffer[k] = str[i];
// 			k++;
// 			i++;
// 		}
// 	}
// 	buffer[k] = '\0';
// 	// printf("buffer: %s\n", buffer);
// 	return(buffer);
// }


// void expand_variables(t_tree *tree, char *str)
// {
// 	int pos_open, pos_close;
//     char quote;
//     t_sgm sgm;
//     int i = 0;

//     sgm.e = (int)ft_strlen(str);
// 	sgm.b = 0;

// 	if(strchr(str, '$') == NULL)
// 	{
// 		add_to_list(tree, str, sgm.b, sgm.e);
// 		return ;
// 	}
// 	while(str[i])
// 	{
// 		sgm.b = i;
// 		pos_open = get_quote_pos(str, sgm);
// 		quote = str[pos_open];
// 		pos_close = find_symb(str, quote, cr_sgm(pos_open + 1, sgm.e));
// 		if(quote == '\'')
// 		{
// 			add_to_list(tree, str, sgm.b, pos_close + 1);
// 			i = pos_close + 1;
// 			continue ;
// 		}
// 		if(quote == '"')
// 		{
// 			add_to_list(tree, str, sgm.b, pos_close + 1);
// 			i = pos_close + 1;
// 			continue ;
// 		}
// 		i++;
// 		// if(str[i] == '$')
// 		// {
// 		// 	len = get_varname_len(str + i + 1);
// 		// }

// 	}
// }
