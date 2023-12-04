

#include "minishell.h"
#include "string.h"

void add_to_list(t_tree *tree, char *str, int beg, int end)
{
	t_list *list;
		
	list = ft_lstnew(str, beg, end);
	ft_lstadd_back(&(tree->expand), list);
	
}

int get_var_len(char *str) 
{
    int i;
	
	i = 0;
    while (str[i] && (ft_isalpha(str[i]) || str[i] == '_')) 
	{
        i++;
    }
    return i;
}


int get_var_len(char *str)
{
	int i;

	i = 0;
	if(!ft_isalpha(str[i] && str[i] != '_'))
		return(i);
	while(str[i])
	{
		if(!ft_isalpha(str[i] && str[i] != '_'))
			return(i);
		i++;
	}
	return(i);
}

/* returns true, if given index is not in single quotes*/

bool not_in_single_quotes(const char *str, int index) 
{
    int i;
    bool in_single_quote;
    bool in_double_quote;

	i = 0;
    in_single_quote = false;
	in_double_quote = false;
	if (str == NULL || index < 0) 
        return false;
    while (str[i] != '\0' && i <= index) 
	{
        if (str[i] == '\'' && !in_double_quote) 
            in_single_quote = !in_single_quote;
		else if (str[i] == '\"' && !in_single_quote) 
            in_double_quote = !in_double_quote;
        i++;
    }
    return (!in_single_quote);
}

char *expand_variables(t_tree *tree, char *str)
{
	char buffer[1000];
	char *var_name;
	char *var_value;
    int i = 0;
	int k = 0;
	int len;

	if(strchr(str, '$') == NULL)
	{
		ft_strlcpy(buffer, str, 1000);
		return(buffer);
	}
	while(str[i])
	{
		if(str[i] == '$' && not_in_single_quotes(str, i))
		{
			i++;
			len = get_var_len(str + i);
			var_name = ft_strndup(str + i, len);
			var_value = ft_strdup(ft_getenv(var_name, tree->data));
			k = ft_strlcat(buffer, var_value, 1000);
			i += len;
			free(var_name);
			free(var_value);
		}
		else
		{
			buffer[k] = str[i];
			k++;
			i++;
		}
	}
	return(buffer);
}

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
// 		return;
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
// 			continue;
// 		}
// 		if(quote == '"')
// 		{
// 			add_to_list(tree, str, sgm.b, pos_close + 1);
// 			i = pos_close + 1;
// 			continue;
// 		}
// 		i++;
// 		// if(str[i] == '$')
// 		// {
// 		// 	len = get_var_len(str + i + 1);
// 		// }
		
// 	}
// }

void expand_var_list(t_tree *tree)
{
	t_list *current;
	
	current = tree->list;
	while(current)
	{
		// tmp = remove_outer_quotes(current->word);
		// if(tmp == NULL) 
		// {
		// 	ft_printf_fd(2, "error removing outer quotes\n"); // what to do in this case?
		// 	current = current->next;
		// 	continue;
		// }
		expand_variables(tree, current->word);
		// free(current->word);
		// current->word = tmp;
		current = current->next;
		// ft_printf("%s\n", current->word);    // for testing
	}
}
