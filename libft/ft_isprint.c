/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_alpha.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/01 01:42:59 by mstorcha          #+#    #+#             */
/*   Updated: 2017/10/27 14:50:11 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_isprint(int str)
{
	if (str >= ' ' && str <= '~')
		return (1);
	else
		return (0);
}
