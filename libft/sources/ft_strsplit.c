/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasanoj <lvasanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 14:15:49 by lvasanoj          #+#    #+#             */
/*   Updated: 2021/01/28 14:01:05 by lvasanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int		cnt(char const *s, char c)
{
	int words;

	words = 0;
	if (*s != c && *s)
	{
		words++;
		s++;
	}
	while (*s)
	{
		while (*s == c)
		{
			s++;
			if (*s != c && *s)
				words++;
		}
		s++;
	}
	return (words);
}

static int		chln(char const *s, char c)
{
	int len;

	len = 0;
	while (*s != c && *s)
	{
		s++;
		len++;
	}
	return (len);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**new;
	int		i;
	int		b;

	b = 0;
	i = 0;
	if (!s || (!(new = (char **)malloc(sizeof(char *) * (cnt(s, c) + 1)))))
		return (NULL);
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
			if (!(new[i] = (char *)malloc(sizeof(char) * (chln(s, c) + 1))))
				return (NULL);
			while (*s && *s != c)
				new[i][b++] = (char)*s++;
			new[i][b] = '\0';
			i++;
			b = 0;
		}
	}
	new[i] = NULL;
	return (new);
}
