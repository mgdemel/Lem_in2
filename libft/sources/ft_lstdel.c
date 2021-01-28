/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasanoj <lvasanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 11:48:32 by lvasanoj          #+#    #+#             */
/*   Updated: 2021/01/28 14:03:26 by lvasanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*templist;
	t_list	*pointer;

	templist = *alst;
	while (templist)
	{
		pointer = templist;
		ft_lstdelone(&templist, del);
		templist = pointer->next;
	}
	*alst = NULL;
}
