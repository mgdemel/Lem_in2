/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasanoj <lvasanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 11:48:32 by lvasanoj          #+#    #+#             */
/*   Updated: 2020/09/01 22:18:02 by lvasanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

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
