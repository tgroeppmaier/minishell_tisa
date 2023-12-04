#include "minishell.h"
#include "string.h"

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
//         add_to_list(tree, str[i], 1, strlen(str[i]));  // Use strlen to get the length of each string
//         i++;
//     }
// }

int get_var_len(char *str) 
{
    int i;
	
	i = 0;
	if(ft_isalpha(str[0] && str[0] != '_'))
		return(0);
    while (str[i] && (ft_isalnum(str[i]) || str[i] == '_')) 
        i++;
    return i;
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

char *get_expand_variables(t_tree *tree, char *str)
{
	char *buffer;
	char *var_name;
	char *var_value;
    int i = 0;
	int k = 0;
	int len;

	if(str == NULL)
		return(NULL);
	if(strchr(str, '$') == NULL)
		return(ft_strdup(str));
	buffer = (char *)malloc(sizeof(char) * 1000);
	buffer[0] = '\0';
	while(str[i])
	{
		if(str[i] == '$' && not_in_single_quotes(str, i))
		{
			i++;
			// printf("str: %s\n", str);
			len = get_var_len(str + i);
			// ft_printf("len: %d\n", len);
			var_name = ft_strndup(str + i, len);
			// ft_printf("var name: %s\n", var_name);
			var_value = ft_strdup(ft_getenv(var_name, tree->data));
			// ft_printf("var value: %s\n", var_value);
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
	buffer[k] = '\0';
	// printf("buffer: %s\n", buffer);
	return(buffer);
}

void expand_variables(t_tree *tree)
{
	t_list	*current;
	char	*tmp;
	
	current = tree->list;
	while(current)
	{
		tmp = get_expand_variables(tree, current->word);
		if(tmp == NULL) 
		{
			ft_printf_fd(2, "error expanding variables\n"); // what to do in this case?
			current = current->next;
			continue;
		}
		free(current->word);
		current->word = tmp;
		ft_printf("current word: %s\n", current->word);
		current = current->next;
		// ft_printf("%s\n", current->word);    // for testing
	}
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
