/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:09:04 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/06/20 21:03:28 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_size_t	ft_int_len(int n)
{
	t_size_t	sign;

	sign = 0;
	if (n < 0 && n == -n)
	{
		return (ft_int_len(n / 10) + 1);
	}
	if (n < 0)
	{
		++sign;
		n = -n;
	}
	if (0 <= n && n <= 9)
	{
		return (1 + sign);
	}
	return (ft_int_len(n / 10) + 1 + sign);
}

t_uint	ft_unsigned_int_len_base(t_uint num, t_uint base)
{
	if (base <= 1)
	{
		write(1, "Warning in ft_unsigned_int_len_base\n\
			base was raised to minimal value of 2\n", 78);
		base = 2;
	}
	if (num <= base - 1)
		return (1);
	return (1 + ft_unsigned_int_len_base(num / base, base));
}

static char	*ft_allocate_itoa(int n, t_size_t *len_addr)
{
	char		*res;
	t_size_t	index;

	index = ft_int_len(n);
	res = (char *)malloc(sizeof(char) * (index + 1));
	if (res == NULL)
	{
		return (NULL);
	}
	res[index] = '\0';
	*len_addr = index;
	return (res);
}

char	*ft_itoa(int n)
{
	char		*res;
	t_size_t	index;
	t_size_t	negative;

	res = ft_allocate_itoa(n, &index);
	if (res == NULL)
		return (NULL);
	negative = 0;
	if (n < 0)
	{
		res[0] = '-';
		negative = 1;
		if (n == -n)
		{
			res[index-- - 1] = '0' + (- (n % 10));
			n /= 10;
		}
		n = -n;
	}
	while (index > negative)
	{
		res[index-- - 1] = '0' + (n % 10);
		n /= 10;
	}
	return (res);
}
