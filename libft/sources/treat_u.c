/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_u.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasanoj <lvasanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 10:43:24 by lvasanoj          #+#    #+#             */
/*   Updated: 2021/06/11 17:43:28 by lvasanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

static char	*utoa(unsigned long long u)
{
	char				*num;
	unsigned long long	copy;
	int					len;

	len = 0;
	copy = u;
	while (u > 0)
	{
		len++;
		u /= 10;
	}
	if (copy != 0)
		num = (char *)malloc(sizeof(char) * len);
	else
		return (num = ft_strdup("0"));
	num[len] = '\0';
	while (len)
	{
		len--;
		num[len] = (copy % 10) + '0';
		copy /= 10;
	}
	return (num);
}

static void	treat_u_putchar(char *u, t_ftprintf *flags)
{
	if (flags->minus == 1)
	{
		if (flags->dot >= 0)
			treat_width(flags->dot - 1, ft_strlen(u) - 1, 1, flags);
		putstrprecision(u, ft_strlen(u), flags);
	}
	if (flags->dot >= 0 && (size_t)flags->dot < ft_strlen(u))
		flags->dot = ft_strlen(u);
	if (flags->dot >= 0)
	{
		flags->width -= flags->dot;
		treat_width(flags->width, 0, 0, flags);
	}
	else
		treat_width(flags->width, ft_strlen(u), flags->zero, flags);
	if (flags->minus == 0)
	{
		if (flags->dot >= 0)
			treat_width(flags->dot - 1, ft_strlen(u) - 1, 1, flags);
		putstrprecision(u, ft_strlen(u), flags);
	}
}

int	treat_u(unsigned long long u, t_ftprintf *flags)
{
	char	*unlong;

	if (flags->dot == 0 && u == 0)
	{
		treat_width(flags->width, 0, 0, flags);
		return (0);
	}
	unlong = utoa(u);
	treat_u_putchar(unlong, flags);
	free(unlong);
	return (0);
}
