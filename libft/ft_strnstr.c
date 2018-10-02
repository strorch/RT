/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 14:49:18 by mstorcha          #+#    #+#             */
/*   Updated: 2017/11/22 20:27:24 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t len;

	if (!*needle)
		return ((char *)haystack);
	len = ft_strlen(needle);
	while (*haystack && n-- >= len)
		if (!ft_strncmp(haystack++, needle, len))
			return ((char *)haystack - 1);
	return (NULL);
}
