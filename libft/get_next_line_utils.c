/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 11:43:27 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/08/08 11:10:00 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Mistakes:
	did not allocate memory for buffer befre reading into it
	confused several times *buffer and buffer, with having (char **buffer)
	*str[ind], with str of type char **; instead should be (*str)[ind]
	also had an error in place_end_alloc, with indexes
	another mistake was to free(smth) without later assigning smth=NULL
*/

t_size_t	ft_strlen_gnl(char *str)
{
	t_size_t	len;

	if (str == NULL)
		return (0);
	len = 0;
	while (*str++ != '\0')
	{
		++len;
	}
	return (len);
}

int	place_beg_noalloc(char *src, char **dst, t_size_t MAXSIZE)
{
	t_size_t	cnt;

	if (dst == NULL)
		return (-1);
	if (src == NULL)
		return (0);
	if (*dst == NULL)
		return (-2);
	cnt = -1;
	while (++cnt < MAXSIZE && cnt < ft_strlen_gnl(src))
	{
		(*dst)[cnt] = src[cnt];
	}
	(*dst)[cnt] = '\0';
	return (0);
}

int	place_end_alloc(char *src, char **dst, t_size_t MAXSIZE)
{
	char		*tmpptr;
	t_size_t	lensrc;
	t_size_t	lendst;
	t_size_t	cnt;

	if (dst == NULL)
		return (-1);
	lensrc = ft_strlen_gnl(src);
	lendst = ft_strlen_gnl(*dst);
	if (lensrc == 0)
		return (0);
	tmpptr = (char *)malloc(lensrc + lendst + 1);
	if (tmpptr == NULL)
		return (-1);
	cnt = -1;
	while (++cnt < lendst)
		tmpptr[cnt] = (*dst)[cnt];
	while (cnt < lendst + lensrc && cnt++ < lendst + MAXSIZE)
		tmpptr[cnt - 1] = src[cnt - 1 - lendst];
	tmpptr[cnt] = '\0';
	free (*dst);
	*dst = tmpptr;
	return (0);
}

t_size_t	getpos(char smb, char *str)
{
	t_size_t	pos;

	if (str == NULL)
		return (-1);
	pos = 0;
	while (*str != '\0' && *str != smb)
	{
		++pos;
		++str;
	}
	if (*str == smb)
		return (pos);
	return (-1);
}

int	doread(int fd, char **buffer, t_size_t *smbcnt)
{
	*smbcnt = read(fd, *buffer, BUFFER_SIZE);
	if (*smbcnt + 1 == 0)
		return (-1);
	(*buffer)[*smbcnt] = '\0';
	return (0);
}
