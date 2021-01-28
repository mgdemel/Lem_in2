/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasanoj <lvasanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 11:36:49 by lvasanoj          #+#    #+#             */
/*   Updated: 2020/06/26 11:14:55 by lvasanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static int		checkln(int n)
{
	int len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		len++;
		n = n * -1;
	}
	while (n > 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

static int		negat(int n)
{
	n = n * -1;
	return (n);
}

char			*ft_itoa(int n)
{
	char	*new;
	int		i;

	i = 0;
	i = checkln(n);
	if (n == -2147483648)
		return (new = ft_strdup("-2147483648"));
	if (!(new = (char *)malloc(sizeof(char) * i + 1)))
		return (NULL);
	new[i--] = '\0';
	if (n == 0)
		new[0] = '0';
	if (n < 0)
	{
		n = negat(n);
		new[0] = '-';
	}
	while (n > 0)
	{
		new[i] = 48 + (n % 10);
		n = n / 10;
		i--;
	}
	return (new);
}
