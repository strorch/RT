/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 17:26:53 by mstorcha          #+#    #+#             */
/*   Updated: 2017/11/21 17:27:52 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	long int nb1;

	nb1 = nb;
	if (nb1 < 0)
	{
		ft_putchar_fd('-', fd);
		nb1 = -nb1;
	}
	if (nb1 >= 10)
	{
		ft_putnbr_fd(nb1 / 10, fd);
		ft_putnbr_fd(nb1 % 10, fd);
	}
	else
		ft_putchar_fd(nb1 + '0', fd);
}
