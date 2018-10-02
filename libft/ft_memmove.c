/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 14:49:18 by mstorcha          #+#    #+#             */
/*   Updated: 2017/11/27 16:09:15 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t num)
{
	size_t		i;

	if (src == dst)
		return (dst);
	else if (src < dst)
	{
		i = num + 1;
		while (--i)
		{
			*((char *)(dst + i - 1)) = *(char *)(src + i - 1);
		}
	}
	else
	{
		i = -1;
		while (++i < num)
		{
			*((char *)(dst + i)) = *((char *)(src + i));
		}
	}
	return (dst);
}
