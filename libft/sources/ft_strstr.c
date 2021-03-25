/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasanoj <lvasanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 08:47:58 by lvasanoj          #+#    #+#             */
/*   Updated: 2021/03/25 09:54:44 by lvasanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int i;
	int a;

	i = 0;
	a = 0;
	if (needle[0] == '\0')
		return ((char*)haystack);
	while (haystack[i] != '\0')
	{
		if (needle[a] == '\0')
			return (NULL);
		while (haystack[a + i] == needle[a] && haystack[a + i] != '\0')
		{
			if (needle[a + 1] == '\0')
				return ((char*)&haystack[i]);
			a++;
		}
		a = 0;
		i++;
	}
	return (NULL);
}
