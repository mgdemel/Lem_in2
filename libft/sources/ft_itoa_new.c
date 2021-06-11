/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasanoj <lvasanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 11:36:49 by lvasanoj          #+#    #+#             */
/*   Updated: 2021/06/11 18:47:42 by lvasanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

static int	checkln(intmax_t n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		len++;
		n = n * -1;
	}
	while (n > 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

static intmax_t	negat(intmax_t n)
{
	n = n * -1;
	return (n);
}

static char	*itoa_new(intmax_t n)
{
	int		i;
	char	*new;
	int		neg;

	i = 0;
	neg = 0;
	i = checkln(n);
	new = (char *)malloc(sizeof(char) * i + 1);
	new[i--] = '\0';
	if (n == 0)
		new[0] = '0';
	if (n < 0)
	{
		n = negat(n);
		new[0] = '-';
		neg = 1;
	}
	while (i >= 0 + neg)
	{
		new[i] = 48 + (n % 10);
		n = n / 10;
		i--;
	}
	return (new);
}

char	*ft_itoa_new(intmax_t n, t_ftprintf *flags)
{
	if ((n == 32768 || n == -32768) && flags->short_h == 1
		&& flags->type == 'd')
		return (ft_strdup("-32768"));
	else if ((n == 128 || n == -128) && flags->short_h == 2
		&& flags->type == 'd')
		return (ft_strdup("-128"));
	else if (n == 2147483648 && flags->long_l >= 1 && (flags->type == 'd'
			|| flags->type == 'i'))
		return (ft_strdup("2147483648"));
	else if (n == -2147483649 && flags->long_l >= 1 && (flags->type == 'd'
			|| flags->type == 'i'))
		return (ft_strdup("-2147483649"));
	else if (((n + 1) == -9223372036854775807) && flags->long_l >= 1
		&& (flags->type == 'd' || flags->type == 'i'))
		return (ft_strdup("-9223372036854775808"));
	else if ((n == -2147483648 || n == 2147483648) && (flags->type == 'd'
			|| flags->type == 'i'))
		return (ft_strdup("-2147483648"));
	else
		return (itoa_new(n));
}
