/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasanoj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 13:50:39 by lvasanoj          #+#    #+#             */
/*   Updated: 2019/11/01 17:19:47 by lvasanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t i;

	i = 0;
	while (n--)
	{
		if (((unsigned char *)s)[i] == (unsigned char)c)
			return (&((void*)s)[i]);
		i++;
	}
	return (NULL);
}
