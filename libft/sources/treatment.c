/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treatment.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasanoj <lvasanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 14:08:05 by lvasanoj          #+#    #+#             */
/*   Updated: 2021/06/11 18:12:00 by lvasanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

void	treat_perc(t_ftprintf *flags)
{
	if (flags->minus == 1)
		putstrprecision("%", 1, flags);
	treat_width(flags->width, 1, flags->zero, flags);
	if (flags->minus == 0)
		putstrprecision("%", 1, flags);
}

void	treat_width(int width, int minus, int if_zero, t_ftprintf *flags)
{
	while (width - minus > 0)
	{
		if (if_zero)
			ft_putchar('0');
		else
			ft_putchar(' ');
		width--;
		flags->char_count++;
	}
}

void	treatment2(t_ftprintf *flags, va_list args)
{
	if (flags->large_l == 1)
		fltoascii((long double)va_arg(args, long double), flags);
	else
		fltoascii((double)va_arg(args, double), flags);
}

void	treatment(char type, t_ftprintf *flags, va_list args)
{
	if (type == 'c')
		treat_char(va_arg(args, int), flags);
	else if (type == 's')
		treat_string(va_arg(args, char *), flags);
	else if (type == 'p')
		treat_p(va_arg(args, unsigned long long), flags);
	else if (type == 'd' || type == 'i')
		treat_d(typecast_num(flags, args), flags);
	else if (type == 'o')
		treat_o(typecast_uoxx(flags, args), flags);
	else if (type == 'u')
		treat_u(typecast_uoxx(flags, args), flags);
	else if (type == 'x')
		treat_x(typecast_uoxx(flags, args), flags);
	else if (type == 'X')
	{
		flags->x_case = 1;
		treat_x(typecast_uoxx(flags, args), flags);
	}
	else if (type == '%')
		treat_perc(flags);
	else if (type == 'f')
		treatment2(flags, args);
}
