/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasanoj <lvasanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 15:41:14 by lvasanoj          #+#    #+#             */
/*   Updated: 2021/01/28 14:01:39 by lvasanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t sized;
	size_t sizes;

	sized = ft_strlen(dst);
	sizes = ft_strlen(src);
	if (sized > dstsize)
		sized = dstsize;
	else if (sized == dstsize || dstsize == 0)
		return (sized + sizes);
	else if (sizes < dstsize - sized)
		ft_memcpy(dst + sized, src, sizes + 1);
	else
	{
		ft_memcpy(dst + sized, src, dstsize - sized - 1);
		dst[dstsize - 1] = '\0';
	}
	return (sized + sizes);
}
