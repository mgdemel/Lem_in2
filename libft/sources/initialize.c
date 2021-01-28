/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasanoj <lvasanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 14:51:03 by lvasanoj          #+#    #+#             */
/*   Updated: 2020/09/01 22:08:00 by lvasanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

/*
**	These functions are made to initialize a struct to what we need.
**	All these values will change if they are being used in the char string.
*/

void	init_flags(t_ftprintf *flags)
{
	flags->dot = -1;
	flags->minus = 0;
	flags->star = 0;
	flags->type = 0;
	flags->width = 0;
	flags->zero = 0;
	flags->short_h = 0;
	flags->x_case = 0;
	flags->long_l = 0;
	flags->hash = 0;
	flags->space = 0;
	flags->float_comp = 0;
	flags->dot2 = 0;
	flags->intcopy = 0;
	flags->save = 0;
	flags->isneg = 0;
	flags->j = 0;
	flags->large_l = 0;
	flags->percentages = 0;
	flags->increase = 0;
}

void	initialize(t_ftprintf *p)
{
	p->percentages = 0;
	p->char_count = 0;
}
