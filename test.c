#include <stdio.h>
#include <stdbool.h>

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

int main() {
    const char *test_str = "1\'\"4\"\'5\'8\'789";
    int index = 8;  

    if (not_in_single_quotes(test_str, index)) {
        printf("Index %d is either not in quotes or in double quotes.\n", index);
    } else {
        printf("Index %d is in single quotes.\n", index);
    }

    return 0;
}
