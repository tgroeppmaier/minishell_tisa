#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

char *ft_strchr(char *str, int c)
{
    while(*str) 
    {
        if(*str == (char)c)
            return (str);
        str++;
    }
    if (c == '\0')
        return (str); // Added handling for '\0'
    return (NULL);
}

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while(str[i])
		i++;
	return(i);
}

void ft_putstr(char *str)
{
	while(*str)
		write(2, str++, 1);
}

int ft_strcmp(const char *s1, const char *s2)
{
	int i;

	i = 0;
	while(s1[i] && s2[i])
	{
		if(s1[i] != s2[i])
			return((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char *ft_strncpy(char *dest, const char *src, int n)
{
	int i = 0;

	while(src[i] && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return(dest);
}

char *ft_strndup(const char *str, int n)
{
	char *new_str;
	
	if(!str)
	{
		perror("ft_strndup error\n");
		exit(1);
	}
	new_str = malloc(sizeof(char) * n + 1);
	if(!new_str)
	{
		perror("malloc\n");
		exit(1);
	}
	new_str = ft_strncpy(new_str, str, n);
	return(new_str);

}

int	ft_wcount(const char *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (*s != c)
		{
			++count;
			while (*s && *s != c)
				++s;
		}
		else
			++s;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		k;
	int		count;

	k = 0;
	if (!s)
		return (NULL);
	array = malloc(sizeof(char *) * (ft_wcount(s, c) + 1));
	if (!array)
		return (NULL);
	while (*s)
	{
		count = 0;
		while (*s != c && *s)
		{
			count++;
			s++;
		}
		if (count > 0)
			array[k++] = ft_strndup(s - count, count);
		if (*s)
			s++;
	}
	array[k] = NULL;
	return (array);
}