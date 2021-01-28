/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typecast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasanoj <lvasanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 14:39:49 by lvasanoj          #+#    #+#             */
/*   Updated: 2020/09/01 22:29:28 by lvasanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

intmax_t	typecast_uoxx(t_ftprintf *flags, va_list args)
{
	intmax_t num;

	if (flags->short_h == 1)
		num = (unsigned short int)va_arg(args, unsigned int);
	else if (flags->short_h == 2)
		num = (unsigned char)va_arg(args, unsigned int);
	else if (flags->long_l == 1)
		num = (unsigned long int)va_arg(args, unsigned long int);
	else if (flags->long_l == 2)
		num = (unsigned long long int)va_arg(args, unsigned long long int);
	else if (flags->j == 1)
		num = (uintmax_t)va_arg(args, uintmax_t);
	else
		num = (unsigned int)va_arg(args, unsigned int);
	return (num);
}

intmax_t	typecast_num(t_ftprintf *flags, va_list args)
{
	intmax_t		num;

	if (flags->short_h == 1)
		num = (short int)va_arg(args, int);
	else if (flags->short_h == 2)
		num = (signed char)va_arg(args, int);
	else if (flags->long_l == 1)
		num = (long int)va_arg(args, long int);
	else if (flags->long_l == 2)
		num = (long long int)va_arg(args, long long int);
	else if (flags->j == 1)
		num = (intmax_t)va_arg(args, intmax_t);
	else
		num = (int)va_arg(args, int);
	return (num);
}
