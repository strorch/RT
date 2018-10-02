/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 10:02:02 by exam              #+#    #+#             */
/*   Updated: 2018/03/02 15:45:55 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		num(const char *str, char c)
{
	int i;
	int count;

	if (!str)
		return (0);
	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		while (str[i] == c && str[i] != '\0')
			i++;
		while (str[i] != c && str[i] != '\0')
		{
			i++;
			if (str[i] == c || str[i] == '\0')
				count++;
		}
	}
	return (count);
}

static int		len(const char *str, int i, char c)
{
	int num;

	num = 0;
	while (str[i] != c && str[i] != 0)
	{
		i++;
		num++;
	}
	return (num);
}

static char		*new_word(const char *str, int i, int len)
{
	int		k;
	char	*word;

	k = 0;
	if (!(word = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (k < len)
		word[k++] = str[i++];
	word[k] = 0;
	return (word);
}

char			**ft_strsplit(const char *str, char c)
{
	char	**arr;
	int		i;
	int		j;

	if (!str || !(arr = (char **)malloc(sizeof(char *) * (num(str, c) + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		while (str[i] == c && str[i] != '\0')
			i++;
		if (str[i] != '\0')
		{
			if (!(arr[j] = new_word(str, i, len(str, i, c))))
				return (ft_del_str(arr));
			i += len(str, i, c);
			j++;
		}
	}
	arr[j] = 0;
	return (arr);
}
