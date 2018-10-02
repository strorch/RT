/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 17:19:50 by mstorcha          #+#    #+#             */
/*   Updated: 2017/11/21 18:56:28 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	lenwsp(char const *s, char c)
{
	size_t i;
	size_t count;

	count = 0;
	i = ft_strlen(s) - 1;
	while (s[i] == c)
	{
		count++;
		i--;
	}
	return (count);
}

char			*ft_strtrimch(char const *s, char c)
{
	size_t	len;
	char	*new;

	if (!s)
		return (NULL);
	while (*s == c)
		s++;
	len = ft_strlen(s);
	if (len == 0)
	{
		new = ft_strnew(1);
		*new = '\0';
		return (new);
	}
	if (!(new = ft_strnew(len - lenwsp(s, c))))
		return (NULL);
	new = ft_strncpy(new, s, len - lenwsp(s, c));
	return (new);
}
