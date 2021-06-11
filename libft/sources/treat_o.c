/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_o.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasanoj <lvasanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 10:11:32 by lvasanoj          #+#    #+#             */
/*   Updated: 2021/06/11 18:27:01 by lvasanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"
#include <stdio.h>

static void	put_hash(int o, t_ftprintf *flags)
{
	if (flags->hash == 1 && o != 0)
		putstrprecision("0", 1, flags);
}

static void	minus_on(char *octal, t_ftprintf *flags, int o)
{
	if (flags->minus == 1)
	{
		if (flags->dot >= 0)
			treat_width(flags->dot - 1, ft_strlen(octal) - 1, 1, flags);
		put_hash(o, flags);
		putstrprecision(octal, ft_strlen(octal), flags);
	}
}

static void	minus_off(char *octal, t_ftprintf *flags, int o)
{
	if (flags->minus == 0)
	{
		if (flags->dot >= 0)
			treat_width(flags->dot - 1, ft_strlen(octal) - 1, 1, flags);
		if (flags->zero == 0)
			put_hash(o, flags);
		putstrprecision(octal, ft_strlen(octal), flags);
	}
}

static void	treat_o_putchar(char *octal, t_ftprintf *flags, int o)
{
	minus_on(octal, flags, o);
	if (flags->dot >= 0 && (size_t)flags->dot < ft_strlen(octal))
		flags->dot = ft_strlen(octal);
	if (flags->dot >= 0)
	{
		flags->width -= flags->dot;
		treat_width(flags->width, 0, 0, flags);
	}
	else
	{
		if (flags->zero == 1)
			put_hash(o, flags);
		treat_width(flags->width, ft_strlen(octal), flags->zero, flags);
	}
	minus_off(octal, flags, o);
}

int	treat_o(unsigned long long o, t_ftprintf *flags)
{
	char	*octal;

	if (o == 0 && flags->dot == -1)
	{
		treat_o_putchar("0", flags, o);
		return (0);
	}
	if (flags->hash == 1 && o != 0 && flags->width != 0)
		flags->width -= 1;
	else if (flags->hash == 1 && o != 0 && flags->dot > -1)
		flags->dot -= 1;
	if (flags->dot == 0 && o == 0)
	{
		treat_width(flags->width, 0, 0, flags);
		if (flags->hash == 1)
			putstrprecision("0", 1, flags);
		return (0);
	}
	octal = calc_octal(o);
	treat_o_putchar(octal, flags, o);
	free(octal);
	return (0);
}
