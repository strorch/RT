/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rmchar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/25 14:58:46 by mstorcha          #+#    #+#             */
/*   Updated: 2017/12/25 14:59:16 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	numch(char *str, char c)
{
	size_t i;
	size_t count;

	i = 0;
	count = 0;
	while (str[i] != 0)
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

char			*ft_rmchar(char *str, char c)
{
	int		i;
	size_t	j;
	char	*new;

	i = 0;
	j = 0;
	if (!(new = ft_strnew(ft_strlen(str) - numch(str, c))))
		return (NULL);
	while (j < ft_strlen(str) - numch(str, c))
	{
		if (str[i] != c)
		{
			new[j] = str[i];
			j++;
		}
		i++;
	}
	new[j] = 0;
	return (new);
}
