/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasanoj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 10:15:16 by lvasanoj          #+#    #+#             */
/*   Updated: 2019/11/03 23:19:50 by lvasanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t i;
	size_t a;

	i = 0;
	if (needle[0] == '\0')
		return ((char*)haystack);
	while (haystack[i] != '\0' && i < len)
	{
		if (haystack[i] == needle[0])
		{
			a = 1;
			while (needle[a] != '\0' && haystack[i + a] == needle[a]
					&& (a + i) < len)
				a++;
			if (needle[a] == '\0')
				return ((char*)&haystack[i]);
		}
		i++;
	}
	return (NULL);
}
