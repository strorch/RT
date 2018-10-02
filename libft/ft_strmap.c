/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/07 16:30:01 by mstorcha          #+#    #+#             */
/*   Updated: 2017/11/27 16:54:43 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *tab, char (*f)(char))
{
	char	*new;
	size_t	len;

	if (!tab || !f)
		return (NULL);
	len = ft_strlen(tab);
	if (!(new = ft_strnew(len)))
		return (NULL);
	while (*tab)
	{
		*new = f(*tab);
		new++;
		tab++;
	}
	return (new - len);
}
