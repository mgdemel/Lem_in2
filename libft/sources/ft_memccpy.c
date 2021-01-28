/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasanoj <lvasanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 16:33:15 by lvasanoj          #+#    #+#             */
/*   Updated: 2021/01/28 14:03:05 by lvasanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*cpy;
	unsigned char	*srccpy;

	cpy = (unsigned char *)dst;
	srccpy = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		cpy[i] = srccpy[i];
		if (srccpy[i] == (unsigned char)c)
			return ((void*)dst + i + 1);
		++i;
	}
	return (NULL);
}
