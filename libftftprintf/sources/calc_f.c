/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_f.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasanoj <lvasanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 12:00:21 by lvasanoj          #+#    #+#             */
/*   Updated: 2020/09/01 18:31:22 by lvasanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int		block_len_f(char *big_s, t_ftprintf *flags)
{
	int len;

	len = ft_strlen(big_s) + flags->dot2;
	if (flags->dot2 > 0 || flags->hash)
		len += 1;
	if (flags->space || flags->plus)
		len += 1;
	return (len);
}

void	write_padding(int len, char c)
{
	while (len)
	{
		write(1, &c, 1);
		--len;
	}
}

void	pad_block_f(int len, t_ftprintf *flags, int seg)
{
	if (!flags->zero && !flags->minus && flags->width >
		len && seg == 1)
		write_padding(flags->width - len, ' ');
	else if (!flags->zero && flags->minus && flags->width >
		len && seg == 2)
		write_padding(flags->width - len, ' ');
	else if (seg == 0)
	{
		if (flags->zero && flags->width)
			write_padding(flags->width > len ? flags->width - len : 0, '0');
	}
}

void	write_f(t_ftprintf *flags, char sign, char *big, char *small)
{
	int len;

	len = block_len_f(big, flags);
	pad_block_f(len, flags, 1);
	if (flags->space || flags->plus || flags->isneg)
	{
		write(1, &sign, 1);
		flags->char_count++;
	}
	pad_block_f(len, flags, 0);
	putstrprecision(big, ft_strlen(big), flags);
	if (flags->dot2 || flags->hash)
		putstrprecision(".", 1, flags);
	putstrprecision(small, ft_strlen(small), flags);
	pad_block_f(len, flags, 2);
}

void	fltoascii(long double f, t_ftprintf *flags)
{
	char		*big;
	char		*small;
	char		sign;

	sign = set_sign_f(f, flags);
	if (flags->dot == -1)
		flags->dot2 = 6;
	else
		flags->dot2 = flags->dot;
	f = f < 0 ? -f : f;
	big = big_f(f);
	small = small_f(f, flags->dot2, big);
	small = increase_last(small, flags);
	if (flags->increase == 1)
		big = increase_last_big(big);
	write_f(flags, sign, big, small);
	free(big);
	free(small);
}
