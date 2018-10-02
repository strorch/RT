/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 18:30:11 by mstorcha          #+#    #+#             */
/*   Updated: 2017/11/23 20:04:51 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *cur;
	t_list *next;

	if (!(alst && *alst && del))
		return ;
	cur = *alst;
	while (cur)
	{
		next = cur->next;
		ft_lstdelone(&cur, del);
		cur = next;
	}
	*alst = NULL;
}
