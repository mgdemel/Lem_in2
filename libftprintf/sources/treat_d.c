/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasanoj <lvasanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 10:10:38 by lvasanoj          #+#    #+#             */
/*   Updated: 2020/09/01 21:52:37 by lvasanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

void			put_part_d(int i, char *num, t_ftprintf *flags)
{
	if ((i < 0 || flags->isneg == 1) && flags->dot >= 0)
	{
		if (i < 0)
			ft_putchar('-');
		else
			putstrprecision("-", 1, flags);
		flags->isneg = 0;
		i *= -1;
	}
	if (flags->dot >= 0)
		treat_width(flags->dot - 1, ft_strlen(num) - 1, 1, flags);
	putstrprecision(num, ft_strlen(num), flags);
}

void			treat_d_putchar(char *num, int i, t_ftprintf *flags)
{
	if (flags->minus == 1)
		put_part_d(i, num, flags);
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
		put_part_d(i, num, flags);
}

static intmax_t	negative(intmax_t arg, t_ftprintf *flags)
{
	if (flags->dot == -1 && flags->zero == 1)
		putstrprecision("-", 1, flags);
	arg *= -1;
	flags->zero = 1;
	flags->isneg = 1;
	flags->width--;
	return (arg);
}

int				treat_d(intmax_t arg, t_ftprintf *flags)
{
	char *num;

	if (flags->space == 1 && arg >= 0 && flags->plus != 1 && (flags->star == 1
	|| (flags->dot == -1 && flags->star == 0)))
	{
		putstrprecision(" ", 1, flags);
		flags->width--;
	}
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
		arg = negative(arg, flags);
	num = ft_itoa_new(arg, flags);
	treat_d_putchar(num, arg, flags);
	free(num);
	return (0);
}
