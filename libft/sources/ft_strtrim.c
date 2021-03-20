/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasanoj <lvasanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 13:19:35 by lvasanoj          #+#    #+#             */
/*   Updated: 2021/03/20 12:41:18 by lvasanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int		counters(char const *s)
{
	int i;

	i = 0;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	return (i);
}

static int		fn(char const *s)
{
	int i;
	int j;
	int x;

	x = 0;
	j = 0;
	i = ft_strlen(s);
	while (s[j] == ' ' || s[j] == '\n' || s[j] == '\t')
	{
		j++;
		x++;
	}
	if (s[j] == '\0')
		return (x);
	while (s[i - 1] == ' ' || s[i - 1] == '\n' || s[i - 1] == '\t')
	{
		x++;
		i--;
	}
	return (x);
}

static int		countere(char const *s)
{
	int i;

	i = ft_strlen(s);
	while (s[i - 1] == ' ' || s[i - 1] == '\n' || s[i - 1] == '\t')
		i--;
	return (i);
}

char			*ft_strtrim(char const *s)
{
	char	*new;
	int		c;
	int		i;
	int		j;
	int		n;

	n = fn(s);
	i = counters(s);
	j = 0;
	c = countere(s);
	if (!(new = (char *)malloc(sizeof(char) * (ft_strlen(s) - n) + 1)))
		return (NULL);
	while (s[i] != '\0' && i < c)
	{
		new[j] = s[i];
		j++;
		i++;
	}
	new[j] = '\0';
	return (new);
}
