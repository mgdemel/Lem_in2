/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasanoj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 16:33:15 by lvasanoj          #+#    #+#             */
/*   Updated: 2019/11/02 20:01:18 by lvasanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

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
