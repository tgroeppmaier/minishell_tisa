#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char	*ft_strchr(char *str, int c)
{
	while (*str)
	{
		if (*str == (char)c)
			return (str);
		str++;
	}
	if (c == '\0')
		return (str); // Added handling for '\0'
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	const char	*p;

	p = s;
	while (*p)
		++p;
	return (p - s);
}

void	ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

bool	ft_isalpha(int c)
{
	if ((c > 64 && c < 91) || (c > 96 && c < 123))
		return (true);
	else
		return (false);
}

bool	ft_isdigit(int c)
{
	if ((c >= '0' && c <= '9'))
		return (true);
	else
		return (false);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n && s1[i] && s1[i] == s2[i])
		i++;
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(src);
	if (size != 0)
	{
		while (i < size - 1 && src[i])
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (len);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len1;
	int		len2;
	char	*dst;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	dst = malloc(len1 + len2 + 1);
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, s1, len1 + len2 + 1);
	ft_strlcpy(dst + len1, s2, len2 + 1);
	return (dst);
}

char	*ft_strdup(const char *s1)
{
	unsigned int	len;
	char			*str;

	len = ft_strlen(s1);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, len + 1);
	return (str);
}

char	*ft_strndup(const char *s1, size_t n)
{
	char	*str;

	str = malloc(n + 1);
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, n + 1);
	return (str);
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
	char **array;
	int k;
	int count;

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