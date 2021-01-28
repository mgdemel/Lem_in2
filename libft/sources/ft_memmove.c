/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasanoj <lvasanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 09:44:14 by lvasanoj          #+#    #+#             */
/*   Updated: 2021/01/28 14:02:43 by lvasanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t				i;
	unsigned char		*ptrd;
	const unsigned char	*ptrs;

	ptrd = (unsigned char *)dst;
	ptrs = (unsigned char *)src;
	i = 0;
	if (ptrs < ptrd)
		while (++i <= len)
		{
			ptrd[len - i] = ptrs[len - i];
		}
	else if (ptrd < ptrs)
	{
		while (len > 0)
		{
			ptrd[i] = ptrs[i];
			len--;
			i++;
		}
	}
	return (dst);
}
