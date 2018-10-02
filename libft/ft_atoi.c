/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 13:46:06 by mstorcha          #+#    #+#             */
/*   Updated: 2017/11/27 16:50:20 by mstorcha         ###   ########.fr       */
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

int			ft_atoi(const char *str)
{
	char	*p;
	int		i;
	int		num;

	if (!(p = skip_blank(str)))
		return (0);
	num = 0;
	i = ((*p == '-') || (*p == '+')) ? 0 : -1;
	while (ft_isdigit(p[++i]))
		num = num * 10 + (int)(p[i] - '0');
	return ((*p == '-') ? -num : num);
}
