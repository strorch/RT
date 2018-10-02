/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 17:19:50 by mstorcha          #+#    #+#             */
/*   Updated: 2017/10/24 17:23:58 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *src)
{
	int		i;
	char	*a;

	a = (char*)malloc((ft_strlen(src) + 1) * sizeof(char));
	if (a != NULL)
	{
		i = 0;
		while (src[i] != '\0')
		{
			a[i] = src[i];
			i++;
		}
		a[i] = 0;
		return (a);
	}
	else
		return (NULL);
	return (NULL);
}
