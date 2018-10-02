/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 15:29:53 by mstorcha          #+#    #+#             */
/*   Updated: 2017/11/13 16:40:57 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char *arr;

	arr = malloc(size);
	if (arr != NULL)
	{
		ft_bzero(arr, size);
		return (arr);
	}
	return (NULL);
}
