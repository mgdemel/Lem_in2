/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_f_helper2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasanoj <lvasanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 18:16:52 by lvasanoj          #+#    #+#             */
/*   Updated: 2020/09/01 22:01:10 by lvasanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

char		*increase_last(char *str, t_ftprintf *flags)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	i--;
	if (str[i] < '5')
		return (str);
	while (str[i] == '9' && i > 0)
		i--;
	if (i == 0)
		flags->increase = 1;
	while (str[i] != '\0')
	{
		if (str[i] == '9')
			str[i] = '0';
		else
			str[i] = str[i] + 1;
		i++;
	}
	return (str);
}

char		*ft_addchar(char c, char *str)
{
	size_t	i;
	char	*new;

	if (!(new = (char *)malloc(sizeof(char) * ft_strlen(str) + 1)))
		return (NULL);
	new[ft_strlen(str)] = '\0';
	new[0] = c;
	i = 1;
	while (i < (ft_strlen(str)))
	{
		new[i] = '0';
		i++;
	}
	free(str);
	return (new);
}

char		*increase_last_big(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	i--;
	while (str[i] == '9' && i > 0)
		i--;
	if (i == 0)
		str = ft_addchar(str[0] + 1, str);
	while (str[i] != '\0')
	{
		if (str[i] == '9')
			str[i] = '0';
		else if (str[i] >= '5')
			str[i] = str[i] + 1;
		i++;
	}
	return (str);
}

int			is_not_str(char *str)
{
	return ((str[ft_strlen(str) - 1] - '0') % 2);
}

char		set_sign_f(long double f, t_ftprintf *flags)
{
	char sign;

	if (flags->space == 1)
		sign = ' ';
	else if (flags->plus == 1)
		sign = '+';
	if (f < 0)
	{
		sign = '-';
		flags->isneg = 1;
	}
	return (sign);
}
