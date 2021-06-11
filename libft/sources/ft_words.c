/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_words.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasanoj <lvasanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 14:56:01 by lvasanoj          #+#    #+#             */
/*   Updated: 2021/06/11 17:55:11 by lvasanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_words(char const *s, char c)
{
	int	words;
	int	i;

	i = 0;
	words = 0;
	if (s[i] != '\0' && s[i] != c)
	{
		words++;
		i++;
	}
	while (s[i] != '\0')
	{
		while (s[i] == c)
		{
			i++;
			if (s[i] != c && s[i] != '\0')
				words++;
		}
		i++;
	}
	return (words);
}
