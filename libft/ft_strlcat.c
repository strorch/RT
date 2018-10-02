/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/31 23:54:08 by mstorcha          #+#    #+#             */
/*   Updated: 2017/11/27 16:45:29 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t nb)
{
	char			*dd;
	char			*ss;
	size_t			n;
	size_t			dstlen;

	dd = dst;
	ss = (char *)src;
	n = nb;
	while (*dd != '\0' && n-- != 0)
		dd++;
	dstlen = dd - dst;
	n = nb - dstlen;
	if (!n)
		return (dstlen + ft_strlen(ss));
	while (*ss)
	{
		if (n != 1)
		{
			*dd++ = *ss;
			n--;
		}
		ss++;
	}
	*dd = '\0';
	return (dstlen + (ss - src));
}
