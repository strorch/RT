/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_parser4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 11:01:21 by mstorcha          #+#    #+#             */
/*   Updated: 2018/08/01 11:01:22 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static char		*free_strjoin(char *s1, char *s2)
{
	char	*new;
	size_t	len1;
	size_t	len2;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!(new = ft_strnew(len1 + len2)))
		return (NULL);
	ft_strcat(new, s1);
	ft_strcat(new, s2);
	free(s1);
	free(s2);
	return (new);
}

char			*ft_fgets(char *file)
{
	int		fd;
	char	*str;
	char	*tmp;

	if ((fd = open(file, O_RDONLY)) < 0)
	{
		exit_message("Can not open file");
	}
	str = ft_strnew(0);
	while (ft_get_next_line(fd, &tmp) > 0)
	{
		str = free_strjoin(str, tmp);
	}
	free(tmp);
	return (str);
}

static int		match_brack(char open, char close)
{
	if ((open == '[' && close == ']') || (open == '{' && close == '}'))
		return (1);
	return (0);
}

char			*ft_brackets(char *str, int len)
{
	int		top;
	char	*stack;

	top = 0;
	stack = ft_strnew(len);
	while (*str)
	{
		if (*str == '[' || *str == '{')
			stack[top++] = *str;
		if (*str == ']' || *str == '}')
		{
			if (!match_brack(stack[--top], *str))
			{
				free(stack);
				return (str);
			}
		}
		str++;
	}
	free(stack);
	return (NULL);
}

char			*ft_get_substr(const char *str, char *start, char *end)
{
	size_t		len;
	char		*new;

	len = 0;
	while (str != start)
		str++;
	while (start != end)
	{
		len++;
		start++;
	}
	new = ft_strsub(str, 0, len + 1);
	return (new);
}
