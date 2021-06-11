/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_f_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasanoj <lvasanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 18:19:35 by lvasanoj          #+#    #+#             */
/*   Updated: 2021/06/11 18:06:00 by lvasanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

long double	ftoa_helper(char *big)
{
	long double	f;

	f = 0;
	while (*big)
	{
		f *= 10;
		f += (long double)(*big - '0');
		++big;
	}
	return (f);
}

int	count_big_f(long double f)
{
	int	count;

	count = 0;
	while (f > 1)
	{
		count++;
		f /= 10;
	}
	if (count > 1)
		return (count);
	else
		return (1);
}

long double	ten_pow(int pow)
{
	long double	f;

	f = 1;
	while (pow > 0)
	{
		f = f * 10;
		--pow;
	}
	while (pow < 0)
	{
		f = f / 10;
		++pow;
	}
	return (f);
}

char	*big_f(long double f)
{
	char		*s;
	char		*ptr;
	int			count;
	int			i;
	long double	temp;

	count = count_big_f(f);
	s = (char *)ft_memalloc(count + 1);
	ptr = s;
	while (count)
	{
		i = count - 1;
		temp = f;
		while (i--)
			temp /= 10;
		*ptr++ = (int)temp + '0';
		temp = (int)temp;
		while (++i < count - 1)
			temp *= 10;
		f -= temp;
		--count;
	}
	return (s);
}

char	*small_f(long double f, int p, char *big)
{
	char	*s;
	int		i;

	i = 0;
	if (f < 0)
		f *= -f;
	f -= ftoa_helper(big);
	s = (char *)ft_memalloc(p + 1);
	while (i < p)
	{
		f *= 10;
		if (f > 0)
			s[i++] = (int)f + '0';
		else
			s[i++] = '0';
		f -= (int)f;
	}
	return (s);
}
