/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_makelist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 13:06:25 by mstorcha          #+#    #+#             */
/*   Updated: 2017/12/28 13:07:03 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_slist		*ft_create_elem(void *data)
{
	t_slist *el;

	if (!(el = ft_memalloc(sizeof(t_slist))))
		return (NULL);
	el->data = data;
	el->next = NULL;
	return (el);
}

int			ft_list_count(t_slist *begin_list)
{
	int		i;

	i = 0;
	while (begin_list)
	{
		i++;
		begin_list = begin_list->next;
	}
	return (i);
}

void		*free_lst(t_slist *list)
{
	t_slist *tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp->data);
		free(tmp);
	}
	return (NULL);
}

void		ft_list_push_back(t_slist **begin_list, void *data)
{
	t_slist *lst;
	t_slist *new;

	lst = *begin_list;
	new = ft_create_elem(data);
	if (!lst)
	{
		*begin_list = new;
		return ;
	}
	while (lst->next)
		lst = lst->next;
	lst->next = new;
}
