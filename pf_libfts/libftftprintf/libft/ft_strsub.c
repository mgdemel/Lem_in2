/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasanoj <lvasanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 10:58:31 by lvasanoj          #+#    #+#             */
/*   Updated: 2020/10/22 10:40:50 by lvasanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*new;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (start > ft_strlen(s))
		return (NULL);
	if ((new = (char *)malloc(sizeof(char) * len + 1)) == NULL)
		return (NULL);
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
