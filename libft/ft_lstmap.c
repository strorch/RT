/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 18:32:49 by mstorcha          #+#    #+#             */
/*   Updated: 2017/11/27 16:51:11 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new_lst;
	t_list	*new_el;
	t_list	*prev_el;

	if (!(f && lst))
		return (NULL);
	new_lst = f(lst);
	prev_el = new_lst;
	lst = lst->next;
	while (lst)
	{
		new_el = f(lst);
		prev_el->next = new_el;
		prev_el = prev_el->next;
		lst = lst->next;
	}
	prev_el->next = NULL;
	return (new_lst);
}
