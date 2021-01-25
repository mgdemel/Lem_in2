/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasanoj <lvasanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 11:24:26 by lvasanoj          #+#    #+#             */
/*   Updated: 2020/09/01 22:28:13 by lvasanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int		flag_short_or_long(t_ftprintf *flags, char first, char second)
{
	if (first == 'h')
	{
		if (second == 'h')
			flags->short_h = 2;
		else
			flags->short_h = 1;
		return (flags->short_h - 1);
	}
	else if (first == 'l')
	{
		if (second == 'l')
			flags->long_l = 2;
		else
			flags->long_l = 1;
		return (flags->long_l - 1);
	}
	else if (first == 'j')
		flags->j = 1;
	else if (first == 'L')
		flags->large_l = 1;
	return (1);
}

/*
**	Here we check the . flag. So we start by going forward to the next
**	character and check if there's a * there, and in that case we know
**	the number for the precision is in the argument, so we save the number
**	in the flags struct.
**
**	In the other case we know that there should be a number after the dot,
**	so we save the number in the struct flags.
*/

int		flag_dot(const char *copy, int i, t_ftprintf *flags, va_list args)
{
	i++;
	if (copy[i] == '*')
	{
		flags->dot = va_arg(args, int);
		i++;
	}
	else
	{
		flags->dot = 0;
		while (ft_isdigit(copy[i]))
			flags->dot = (flags->dot * 10) + (copy[i++] - '0');
	}
	return (i);
}

/*
**	We found a minus, so we save it in flags.
**	0 flag is ignored if - is used so we reset it here.
*/

void	flag_minus(t_ftprintf *flags)
{
	flags->minus = 1;
	flags->zero = 0;
}

/*
**	If we've found a star, we reset the width.
**	Then we set the width to the digit after the % sign.
*/

void	flag_digit(char c, t_ftprintf *flags)
{
	if (flags->star == 1)
		flags->width = 0;
	flags->width = (flags->width * 10) + (c - '0');
}

/*
**	We found a * so we check the width from the args.
**	If the value given is negative, we change the minus
**	flag to be active as - flag is left aligned
**	and change the width to be positive so we can use
**	the number.
*/

void	flag_width(va_list args, t_ftprintf *flags)
{
	flags->star = 1;
	flags->width = va_arg(args, int);
	if (flags->width < 0)
	{
		flags->minus = 1;
		flags->width *= -1;
		flags->zero = 0;
	}
}
