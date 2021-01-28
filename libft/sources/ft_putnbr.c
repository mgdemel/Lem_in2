/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasanoj <lvasanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 14:34:42 by lvasanoj          #+#    #+#             */
/*   Updated: 2021/01/28 14:02:19 by lvasanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_putnbr(int n)
{
	if (n >= 0 && n <= 9)
	{
		ft_putchar(n + '0');
	}
	else if (n > 9 && n <= 2147483647)
	{
		ft_putnbr(n / 10);
		ft_putchar(n % 10 + '0');
	}
	else if (n < 0 && n > -2147483648)
	{
		ft_putchar('-');
		ft_putnbr(-n);
	}
	else if (n == -2147483648)
	{
		ft_putnbr(-214748364);
		ft_putchar('8');
	}
}
