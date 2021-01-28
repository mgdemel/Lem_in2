/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasanoj <lvasanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 10:16:39 by lvasanoj          #+#    #+#             */
/*   Updated: 2021/01/28 14:01:09 by lvasanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*string;
	size_t	count;

	count = 0;
	if (*s)
	{
		while (*s)
		{
			if (*s == c)
			{
				string = (char *)s;
				count++;
			}
			s++;
		}
		if (count > 0)
			return (string);
	}
	if (*s == c)
	{
		string = (char *)s;
		return (string);
	}
	return (NULL);
}
