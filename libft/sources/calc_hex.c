/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_hex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasanoj <lvasanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 12:20:21 by lvasanoj          #+#    #+#             */
/*   Updated: 2020/08/20 13:06:51 by lvasanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

static char	*hex_stringrev(char *hex)
{
	int		i;
	int		len;
	char	buf;

	i = 0;
	len = ft_strlen(hex);
	while ((len - 1) > i)
	{
		buf = hex[i];
		hex[i] = hex[len - 1];
		hex[len - 1] = buf;
		len--;
		i++;
	}
	return (hex);
}

static int	get_hex_length(intmax_t n)
{
	int length;

	length = 0;
	while (n > 0)
	{
		length++;
		n /= 16;
	}
	return (length);
}

static char	get_char(int num)
{
	if (num < 10)
		return (num + 48);
	else
		return (num + 55);
}

static char	*calc_hex(uintmax_t n, t_ftprintf *flags)
{
	int		temp;
	int		i;
	char	*hex;

	i = 0;
	if (n == 0 && flags->dot != 0)
	{
		hex = ft_strnew(1);
		hex[0] = '0';
		return (hex);
	}
	hex = ft_strnew(get_hex_length(n));
	while (n != 0)
	{
		temp = n % 16;
		hex[i++] = get_char(temp);
		n /= 16;
	}
	return (hex);
}

char		*decimal_to_hexa(uintmax_t n, t_ftprintf *flags)
{
	char	*hexdecnum;

	hexdecnum = calc_hex(n, flags);
	return (hex_stringrev(hexdecnum));
}
