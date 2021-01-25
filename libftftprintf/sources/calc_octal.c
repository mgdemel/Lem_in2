/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_octal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasanoj <lvasanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 12:33:27 by lvasanoj          #+#    #+#             */
/*   Updated: 2020/09/01 18:26:37 by lvasanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

static int		get_oct_len(unsigned long long num)
{
	int i;

	i = 0;
	while (num > 0)
	{
		i++;
		num /= 8;
	}
	return (i);
}

static char		*oct_stringrev(char *oct)
{
	int		i;
	int		len;
	char	buf;

	i = 0;
	len = ft_strlen(oct);
	while ((len - 1) > i)
	{
		buf = oct[i];
		oct[i] = oct[len - 1];
		oct[len - 1] = buf;
		len--;
		i++;
	}
	return (oct);
}

char			*calc_octal(unsigned long long decimal)
{
	unsigned long long	octal;
	unsigned long long	multiplier;
	char				*ocnum;
	int					i;

	multiplier = 1;
	octal = 0;
	i = 0;
	ocnum = ft_strnew(get_oct_len(decimal));
	while (decimal != 0)
	{
		octal = 0;
		octal += (decimal % 8) * multiplier;
		decimal /= 8;
		ocnum[i] = octal + 48;
		i++;
	}
	ocnum = oct_stringrev(ocnum);
	return (ocnum);
}
