/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_f_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasanoj <lvasanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 18:19:35 by lvasanoj          #+#    #+#             */
/*   Updated: 2020/09/01 22:07:17 by lvasanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

long double	ftoa_helper(char *big)
{
	long double f;

	f = 0;
	while (*big)
	{
		f *= 10;
		f += (long double)(*big - '0');
		++big;
	}
	return (f);
}

int			count_big_f(long double f)
{
	int count;

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
	long double f;

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

char		*big_f(long double f)
{
	char		*s;
	char		*ptr;
	int			count;
	int			i;
	long double	temp;

	count = count_big_f(f);
	if (!(s = (char *)ft_memalloc(count + 1)))
		return (NULL);
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

char		*small_f(long double f, int p, char *big)
{
	char	*s;
	int		i;

	i = 0;
	f = f < 0 ? -f : f;
	f -= ftoa_helper(big);
	if (!(s = (char *)ft_memalloc(p + 1)))
		return (NULL);
	while (i < p)
	{
		f *= 10;
		s[i++] = (f > 0) ? (int)f + '0' : '0';
		f -= (int)f;
	}
	return (s);
}
