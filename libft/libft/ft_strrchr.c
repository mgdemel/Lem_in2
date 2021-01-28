/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasanoj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 10:16:39 by lvasanoj          #+#    #+#             */
/*   Updated: 2019/11/01 16:44:39 by lvasanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

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
