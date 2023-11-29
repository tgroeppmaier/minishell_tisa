/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 10:56:57 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/08/08 11:09:48 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*res;

	res = gnl_eou(fd, &buffer);
	return (res);
}

char	*gnl_eou(int fd, char **buffer)
{
	char		*curr_line;
	int			iter;
	t_size_t	smbcnt;
	t_size_t	pos;

	iter = -1;
	curr_line = NULL;
	while (++iter >= 0 && BUFFER_SIZE + 1 > 1)
	{
		if (iter != 0)
		{
			if (-1 == doalloc(buffer, curr_line, iter))
				return (NULL);
			if (1 + doread(fd, buffer, &smbcnt) == 0)
				return (doiferrornl(buffer, curr_line, 1, 0));
		}
		if (1 + place_end_alloc(*buffer, &curr_line, BUFFER_SIZE) == 0)
			return (doiferrornl(buffer, curr_line, 1, 0));
		pos = getpos('\n', *buffer);
		if (pos + 1 != 0)
			return (doiferrornl(buffer, curr_line, 2, pos));
		if (iter != 0 && smbcnt + 1 < BUFFER_SIZE + 1)
			return (doifeof(buffer, curr_line, smbcnt));
	}
	return (NULL);
}

int	doalloc(char **buffer, char *curr_line, int iter)
{
	if (iter == 1)
	{
		free(*buffer);
		*buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (*buffer == NULL)
		{
			free(curr_line);
			return (-1);
		}
		*buffer[0] = '\0';
	}
	return (0);
}

char	*doiferrornl(char **buffer, char *curr_line, int opt, t_size_t pos)
{
	if (opt == 1)
	{
		free(*buffer);
		*buffer = NULL;
		free(curr_line);
		return (NULL);
	}
	if (opt == 2)
	{
		place_beg_noalloc(*buffer + pos + 1, buffer, BUFFER_SIZE);
		pos = getpos('\n', curr_line);
		curr_line[pos + 1] = '\0';
		if (ft_strlen_gnl(*buffer) == 0)
		{
			free(*buffer);
			*buffer = NULL;
		}
		return (curr_line);
	}
	return (NULL);
}

char	*doifeof(char **buffer, char *curr_line, t_size_t smbcnt)
{
	if (ft_strlen_gnl(curr_line) == 0 && smbcnt == 0)
	{
		free(*buffer);
		*buffer = NULL;
		free(curr_line);
		return (NULL);
	}
	free(*buffer);
	*buffer = NULL;
	return (curr_line);
}
