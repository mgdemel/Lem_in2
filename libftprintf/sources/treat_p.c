/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasanoj <lvasanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 14:24:47 by lvasanoj          #+#    #+#             */
/*   Updated: 2020/09/01 21:53:41 by lvasanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

static char	*itoa_base_fill(char *str, int b, unsigned long long cpy, int len)
{
	while (cpy != 0)
	{
		if ((cpy % b) < 10)
			str[len - 1] = (cpy % b) + 48;
		else
			str[len - 1] = (cpy % b) + 87;
		cpy /= b;
		len--;
	}
	return (str);
}

static char	*itoa_base_rev(unsigned long long p, int base)
{
	char				*str;
	unsigned long long	copy;
	int					len;

	len = 0;
	copy = p;
	if (p == 0)
		return (ft_strdup("0"));
	while (p != 0)
	{
		p /= base;
		len++;
	}
	str = (char *)malloc(sizeof(char) * (len + 1));
	str[len] = '\0';
	return (itoa_base_fill(str, base, copy, len));
}

static void	treat_p_putchar(char *str, t_ftprintf *flags)
{
	putstrprecision("0x", 2, flags);
	if (flags->dot >= 0)
	{
		treat_width(flags->dot, ft_strlen(str), 1, flags);
		putstrprecision(str, flags->dot, flags);
	}
	else
		putstrprecision(str, ft_strlen(str), flags);
}

int			treat_p(unsigned long long p, t_ftprintf *flags)
{
	char *ptr;

	if (p == 0 && flags->dot == 0)
	{
		flags->width -= 2;
		treat_width(flags->width, 0, 0, flags);
		putstrprecision("0x", 2, flags);
		return (0);
	}
	ptr = itoa_base_rev(p, 16);
	if ((size_t)flags->dot < ft_strlen(ptr))
		flags->dot = ft_strlen(ptr);
	if (flags->minus == 1)
		treat_p_putchar(ptr, flags);
	treat_width(flags->width, ft_strlen(ptr) + 2, 0, flags);
	if (flags->minus == 0)
		treat_p_putchar(ptr, flags);
	free(ptr);
	return (0);
}
