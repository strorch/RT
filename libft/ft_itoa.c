/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/31 15:54:12 by mstorcha          #+#    #+#             */
/*   Updated: 2017/11/27 16:50:44 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	num_len(int n)
{
	int i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		i++;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char		*ft_itoa(int n)
{
	char			*p;
	int				len;
	unsigned int	nn;
	char			*num;

	len = num_len(n);
	if (!(num = ft_strnew(len)))
		return (NULL);
	p = num + len;
	if (n < 0)
	{
		*num = '-';
		nn = -n;
		len--;
	}
	else
		nn = n;
	while (len--)
	{
		*--p = '0' + (nn % 10);
		nn /= 10;
	}
	return (num);
}
