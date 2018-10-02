/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/01 18:37:05 by mstorcha          #+#    #+#             */
/*   Updated: 2017/11/25 14:50:48 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t len)
{
	char *s;

	s = dest;
	while (*src && len)
	{
		*s = *src;
		src++;
		s++;
		len--;
	}
	while (len)
	{
		*s = 0;
		s++;
		len--;
	}
	return (dest);
}
