/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 13:17:18 by mstorcha          #+#    #+#             */
/*   Updated: 2017/11/27 15:15:16 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchstr(char const *str, char const *in)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i] != 0)
	{
		j = 0;
		while (in[j] != 0)
		{
			if (str[i] == in[j])
				return (char *)(str + i);
			j++;
		}
		i++;
	}
	return (NULL);
}
