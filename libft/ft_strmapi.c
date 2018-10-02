/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 13:54:17 by mstorcha          #+#    #+#             */
/*   Updated: 2017/11/14 13:55:49 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *tab, char (*f)(unsigned int, char))
{
	char			*new;
	unsigned int	i;

	if (!tab || !f || !(new = ft_strnew(ft_strlen(tab))))
		return (NULL);
	i = 0;
	while (*tab)
	{
		*new = f(i, *tab);
		new++;
		tab++;
		i++;
	}
	return (new - i);
}
