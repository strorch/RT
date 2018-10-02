/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/31 15:54:12 by mstorcha          #+#    #+#             */
/*   Updated: 2017/11/13 16:41:55 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int nb)
{
	long int nb1;

	nb1 = nb;
	if (nb < 0)
	{
		ft_putchar('-');
		nb1 = -nb1;
	}
	if (nb1 >= 10)
	{
		ft_putnbr(nb1 / 10);
		ft_putnbr(nb1 % 10);
	}
	else
		ft_putchar(nb1 + '0');
}
