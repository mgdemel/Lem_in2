/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_words.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasanoj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 14:56:01 by lvasanoj          #+#    #+#             */
/*   Updated: 2019/11/09 16:41:31 by lvasanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int	ft_words(char const *s, char c)
{
	int words;
	int i;

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
