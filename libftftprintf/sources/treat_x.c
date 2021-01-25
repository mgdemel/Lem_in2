/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_x.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasanoj <lvasanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 11:58:44 by lvasanoj          #+#    #+#             */
/*   Updated: 2020/09/01 21:55:36 by lvasanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"
#include <stdio.h>

static void	put_hash(intmax_t x, t_ftprintf *flags)
{
	if (flags->hash == 1 && flags->x_case == 1 && x != 0)
		putstrprecision("0X", 2, flags);
	else if (flags->hash == 1 && flags->x_case == 0 && x != 0)
		putstrprecision("0x", 2, flags);
}

static void	minus_on(char *hexa, t_ftprintf *flags, intmax_t x)
{
	if (flags->minus == 1)
	{
		if (flags->dot >= 0)
			put_hash(x, flags);
		if (flags->dot >= 0)
			treat_width(flags->dot - 1, ft_strlen(hexa) - 1, 1, flags);
		if (flags->dot == -1)
			put_hash(x, flags);
		putstrprecision(hexa, ft_strlen(hexa), flags);
	}
}

static void	minus_off(char *hexa, t_ftprintf *flags, intmax_t x, int hashed)
{
	if (flags->minus == 0)
	{
		if (flags->dot >= 0)
			put_hash(x, flags);
		if (flags->dot >= 0)
			treat_width(flags->dot - 1, ft_strlen(hexa) - 1, 1, flags);
		if (flags->dot == -1 && hashed == 0)
			put_hash(x, flags);
		putstrprecision(hexa, ft_strlen(hexa), flags);
	}
}

static void	treat_x_putchar(char *hexa, t_ftprintf *flags, uintmax_t x)
{
	int hashed;

	hashed = 0;
	minus_on(hexa, flags, x);
	if (flags->dot >= 0 && (size_t)flags->dot < ft_strlen(hexa))
		flags->dot = ft_strlen(hexa);
	if (flags->dot >= 0)
	{
		flags->width -= flags->dot;
		treat_width(flags->width, 0, 0, flags);
	}
	else
	{
		if (flags->zero == 1)
		{
			put_hash(x, flags);
			hashed = 1;
		}
		treat_width(flags->width, ft_strlen(hexa), flags->zero, flags);
	}
	minus_off(hexa, flags, x, hashed);
}

int			treat_x(uintmax_t x, t_ftprintf *flags)
{
	char	*hexa;
	int		i;

	i = 0;
	if (flags->hash == 1 && x != 0)
		flags->width -= 2;
	if (flags->dot == 0 && x == 0)
	{
		treat_width(flags->width, 0, 0, flags);
		return (0);
	}
	hexa = decimal_to_hexa(x, flags);
	if (flags->x_case == 0)
	{
		while (hexa[i] != '\0')
		{
			hexa[i] = ft_tolower(hexa[i]);
			i++;
		}
	}
	treat_x_putchar(hexa, flags, x);
	free(hexa);
	return (0);
}
