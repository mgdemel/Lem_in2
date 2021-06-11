/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasanoj <lvasanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:59:32 by lvasanoj          #+#    #+#             */
/*   Updated: 2021/06/11 18:12:44 by lvasanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*node;
	t_list	*fresh;
	t_list	*temp;

	if (lst && f)
	{
		temp = f(lst);
		node = ft_lstnew(temp->content, temp->content_size);
		lst = lst->next;
		fresh = node;
		while (lst)
		{
			temp = f(lst);
			node->next = ft_lstnew(temp->content, temp->content_size);
			node = node->next;
			lst = lst->next;
		}
	}
	else
		return (NULL);
	return (fresh);
}
