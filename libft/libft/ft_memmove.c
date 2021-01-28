/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasanoj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 09:44:14 by lvasanoj          #+#    #+#             */
/*   Updated: 2019/11/01 16:36:47 by lvasanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

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
