/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 13:12:54 by mstorcha          #+#    #+#             */
/*   Updated: 2018/03/07 21:41:50 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_get_next_line.h"

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

static char		**my_split(char *str)
{
	char	*kek;
	char	*lol;
	char	**new;

	if (!(kek = ft_strchr(str, '\n')))
		return (NULL);
	kek++;
	lol = ft_strsub(str, 0, kek - str - 1);
	new = (char **)malloc(sizeof(char *) * 3);
	new[0] = lol;
	new[1] = ft_strdup(kek);
	new[2] = 0;
	free(str);
	return (new);
}

static int		arr_init(char *arr[DESCR])
{
	int i;

	i = -1;
	while (++i < DESCR)
	{
		if (!arr[i])
			arr[i] = ft_strnew(BUFF_SIZE);
		if (!arr[i])
			return (0);
	}
	return (1);
}

static char		*return_str(int fd)
{
	char	*tmp1;
	int		i;
	char	*to_arr;

	to_arr = ft_strnew(0);
	while (ft_chinstr('\n', to_arr) != 1)
	{
		tmp1 = ft_strnew(BUFF_SIZE);
		i = read(fd, tmp1, BUFF_SIZE);
		if (i == 0)
		{
			to_arr = free_strjoin(to_arr, tmp1);
			return (to_arr);
		}
		else if (i == -1)
		{
			free(to_arr);
			free(tmp1);
			return (NULL);
		}
		to_arr = free_strjoin(to_arr, tmp1);
	}
	return (to_arr);
}

int				ft_get_next_line(const int fd, char **line)
{
	static char		*arr[DESCR];
	char			*to_arr;
	char			*kek;
	char			**splitted;

	if (!line || BUFF_SIZE <= 0 || !(fd >= 0 && fd < DESCR)
			|| arr_init(arr) == 0 || (*line = NULL)
			|| !(to_arr = return_str(fd)))
		return (-1);
	kek = ft_strjoin(arr[fd], to_arr);
	if (!(splitted = my_split(kek)))
	{
		*line = kek;
		free(arr[fd]);
		arr[fd] = ft_strnew(0);
		free(to_arr);
		return (ft_strlen(*line) == 0 ? 0 : 1);
	}
	free(to_arr);
	free(arr[fd]);
	arr[fd] = splitted[1];
	*line = splitted[0];
	free(splitted);
	return (1);
}
