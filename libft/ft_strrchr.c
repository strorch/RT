/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 14:34:32 by mstorcha          #+#    #+#             */
/*   Updated: 2017/11/13 15:59:24 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int i;

	if (0 == c)
		return ((char *)(s + ft_strlen(s)));
	i = ft_strlen(s) - 1;
	while (s[i] != c && i != -1)
		i--;
	if (i == -1)
		return (NULL);
	return (char *)(s + i);
}
