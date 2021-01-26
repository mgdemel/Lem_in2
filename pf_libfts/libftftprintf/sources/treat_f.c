/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_f.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasanoj <lvasanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 16:53:15 by lvasanoj          #+#    #+#             */
/*   Updated: 2020/08/03 12:37:05 by lvasanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"
#include <stdio.h>

static void			put_part_f(int i, char *num, t_ftprintf *flags)
{
	if (i < 0 && flags->dot >= 0)
		ft_putchar('-');
	if (flags->dot >= 0)
		treat_width(flags->dot - 1, ft_strlen(num) - 1, 1, flags);
	putstrprecision(num, ft_strlen(num), flags);
}

static void			treat_f_putchar(char *num, int i, t_ftprintf *flags)
{
	if (flags->minus == 1)
		put_part_f(i, num, flags);
	if (flags->dot >= 0 && (size_t)flags->dot < ft_strlen(num))
		flags->dot = ft_strlen(num);
	if (flags->dot >= 0)
	{
		flags->width -= flags->dot;
		if (flags->plus == 1 && num[0] != '-')
			flags->width -= 1;
		treat_width(flags->width, 0, 0, flags);
		if (flags->plus == 1 && num[0] != '-' && flags->minus != 1)
		{
			putstrprecision("+", 1, flags);
			flags->width -= 1;
		}
	}
	else
		treat_width(flags->width, ft_strlen(num), flags->zero, flags);
	if (flags->minus == 0)
		put_part_f(i, num, flags);
	free(num);
}

int					treat_f(char *arg, t_ftprintf *flags, double n)
{
	if (flags->space == 1 && arg >= 0 && flags->plus != 1 && flags->dot < 0)
		putstrprecision(" ", 1, flags);
	if (flags->plus == 1 && arg >= 0 && (flags->dot < 0 || flags->minus == 1))
	{
		putstrprecision("+", 1, flags);
		if (flags->minus != 1)
			flags->width -= 1;
	}
	if (flags->dot == 0 && arg == 0)
	{
		treat_width(flags->width, 0, 0, flags);
		return (0);
	}
	else if (arg < 0 && (flags->dot >= 0 || flags->zero == 1))
	{
		putstrprecision("-", 1, flags);
		flags->zero = 1;
		flags->width--;
	}
	treat_f_putchar(arg, n, flags);
	return (0);
}
