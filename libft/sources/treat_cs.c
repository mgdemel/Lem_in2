/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_cs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasanoj <lvasanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 11:40:48 by lvasanoj          #+#    #+#             */
/*   Updated: 2021/06/11 18:26:41 by lvasanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

void	treat_char(char c, t_ftprintf *flags)
{
	if (flags->minus == 1)
		ft_putchar(c);
	treat_width(flags->width, 1, 0, flags);
	if (flags->minus == 0)
		ft_putchar(c);
	flags->char_count++;
}

static void	putstr_part(char *str, t_ftprintf *flags)
{
	if (flags->dot >= 0)
	{
		treat_width(flags->dot, ft_strlen(str), 0, flags);
		putstrprecision(str, flags->dot, flags);
	}
	else
		putstrprecision(str, ft_strlen(str), flags);
}

void	treat_string(char *str, t_ftprintf *flags)
{
	if (!str)
		str = "(null)";
	if (flags->dot >= 0 && (size_t)flags->dot > ft_strlen(str))
		flags->dot = ft_strlen(str);
	if (flags->minus == 1)
		putstr_part(str, flags);
	if (flags->dot >= 0)
		treat_width(flags->width, flags->dot, flags->zero, flags);
	else
		treat_width(flags->width, ft_strlen(str), flags->zero, flags);
	if (flags->minus == 0)
		putstr_part(str, flags);
}
