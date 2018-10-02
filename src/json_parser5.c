/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_parser5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 11:01:35 by mstorcha          #+#    #+#             */
/*   Updated: 2018/08/01 11:01:36 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

char			*json_get_array(char *str, char *pattern, char *stack, int top)
{
	char	*start;
	char	*ret;
	char	*s_ptr;
	char	*copy;

	copy = str;
	if (!(start = ft_strstr(copy, pattern)))
		exit_message(ft_strjoin("Unable to find \n", pattern));
	s_ptr = start;
	stack = ft_strnew(ft_strlen(start));
	while (*s_ptr)
	{
		if (*s_ptr == '[')
			stack[top++] = *s_ptr;
		if (*s_ptr == ']')
			if (--top == 0)
				break ;
		s_ptr++;
	}
	free(stack);
	ret = ft_get_substr(start, start, s_ptr);
	ft_memmove(start, s_ptr + 1, ft_strlen(s_ptr));
	return (ret);
}

cl_float3		json_arr_to_vector(char *str,
			char *pattern, char *start, char *end)
{
	cl_float3	vector;
	char		**tab;
	float		arr[3];
	int			i;

	if (!(start = ft_strstr(str, pattern)))
		return (json_arr_to_vector("[0,0,0]", "[", NULL, NULL));
	start = ft_strstr(start, "[");
	end = ft_strstr(start, "]");
	start = ft_get_substr(start, start + 1, end);
	tab = ft_strsplit(start, ',');
	free(start);
	i = -1;
	while (tab[++i])
		arr[i] = ft_atof(tab[i]);
	ft_del_str(tab);
	vector = (cl_float3){.x = arr[0], .y = arr[1], .z = arr[2]};
	return (vector);
}

cl_float3		get_unit_vector(cl_float3 vec)
{
	cl_float3	new;
	float		mag;

	mag = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	new.x = vec.x / mag;
	new.y = vec.y / mag;
	new.z = vec.z / mag;
	return (new);
}

char			*json_get_object(char *str, char *pattern)
{
	char	*start;
	char	*end;
	char	*ret;

	if (!(start = ft_strstr(str, pattern)))
		return (NULL);
	end = ft_strstr(start, "}");
	ret = ft_get_substr(str, start, end + 1);
	ft_memmove(str, end + 1, ft_strlen(end) + 1);
	return (ret);
}

float			json_get_float(char *str, char *pattern)
{
	float		ret;
	char		*substr;

	substr = ft_strstr(str, pattern);
	if (substr == NULL)
		return (0);
	while (!ft_isdigit(*substr))
		substr++;
	ret = ft_atof(substr);
	return (ret);
}
