/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 14:28:34 by mstorcha          #+#    #+#             */
/*   Updated: 2018/06/02 14:28:36 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_instr(char ch, char *str)
{
	while (str && *str && *str != ch)
		++str;
	return (*str == ch);
}

static char	*skip_blank(const char *str)
{
	int i;

	i = 0;
	while (ft_instr(str[i], " \t\n\v\r\f"))
		i++;
	if (ft_instr(str[i], "+-") || ft_isdigit(str[i]))
		return ((char *)&str[i]);
	else
		return (0);
}

float		ft_atof(const char *str)
{
	char	*p;
	int		i;
	float	num;
	float	tmp;

	if (!(p = skip_blank(str)))
		return (0);
	num = 0;
	i = ((*p == '-') || (*p == '+')) ? 0 : -1;
	while (p[++i] != '.' && p[i] != 0 && ft_isdigit(p[i]))
		num = num * 10 + (int)(p[i] - '0');
	tmp = 1;
	while (ft_isdigit(p[++i]))
	{
		tmp *= 10;
		num += (float)(p[i] - '0') / (float)tmp;
	}
	return ((*p == '-') ? -num : num);
}
