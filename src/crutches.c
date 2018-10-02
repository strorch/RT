/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crutches.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminadzh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 20:16:35 by aminadzh          #+#    #+#             */
/*   Updated: 2018/07/30 20:16:36 by aminadzh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

char			*ft_ftoa(float num)
{
	int			whole;
	int			fract;
	char		*str;

	str = ft_strnew(1);
	whole = (int)num;
	fract = (num - whole) * 100;
	if (fract < 0 && whole >= 0)
		str = ft_strcpy(str, "-");
	if (fract < 0)
		fract *= -1;
	str = ft_strjoinfree(str, ft_itoa(whole));
	str = ft_strjoinlit(str, ".");
	str = ft_strjoinfree(str, ft_itoa(fract));
	return (str);
}

void			change_float_val(float *val, char operator, float nb, float max)
{
	if (operator == '+')
		*val += nb;
	else if (operator == '-')
		*val -= nb;
	if (max > 0 && operator == '+' && *val > max)
		*val = 0;
	if (max > 0 && operator == '-' && *val < 0)
		*val = max;
}
