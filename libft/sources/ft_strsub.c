/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasanoj <lvasanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 10:58:31 by lvasanoj          #+#    #+#             */
/*   Updated: 2021/06/11 17:51:16 by lvasanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*new;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (start > ft_strlen(s))
		return (NULL);
	new = (char *)malloc(sizeof(char) * len + 1);
	while (s[start] != '\0' && len > 0)
	{
		new[i] = s[start];
		start++;
		len--;
		i++;
	}
	new[i] = '\0';
	return (new);
}
