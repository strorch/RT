/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_parser2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 11:01:01 by mstorcha          #+#    #+#             */
/*   Updated: 2018/08/01 11:01:03 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

cl_int4				*get_texture_info(t_slist *lst)
{
	cl_int3		*info;
	t_texture	*tmp;
	int			i;

	if (!(info = (cl_int3 *)malloc(sizeof(cl_int3) * ft_list_count(lst))))
		return (NULL);
	i = 0;
	while (lst)
	{
		tmp = lst->data;
		info[i] = (cl_int3) {.x = tmp->h,
								.y = tmp->w,
								.z = tmp->index};
		lst = lst->next;
		i++;
	}
	return (info);
}

static char			*json_get_name(char *str, char *pattern)
{
	char		*ret;
	char		*substr;
	char		**splitted;

	substr = ft_strstr(str, pattern);
	if (!substr)
	{
		return (NULL);
	}
	splitted = ft_strsplit(substr, '\"');
	ret = ft_strdup(splitted[2]);
	ft_del_str(splitted);
	return (ret);
}

static int			read_texture(char *file, t_texture *text)
{
	SDL_Surface	*surface;

	if (!(surface = IMG_Load(file)))
		return (0);
	text->pix = malloc(sizeof(int) * surface->w * surface->h);
	ft_memcpy(text->pix, surface->pixels,
		sizeof(int) * surface->w * surface->h);
	text->h = surface->h;
	text->w = surface->w;
	SDL_FreeSurface(surface);
	return (1);
}

t_texture			*get_texture(char *str, t_opencl *cl, cl_float3 color)
{
	t_texture	*text;
	char		*name;
	int			res;

	if (!(name = json_get_name(str, "\"texture\""))
		|| !(text = malloc(sizeof(t_texture))))
		return (NULL);
	if (!(res = read_texture(name, text)))
	{
		if (!ft_strcmp(name, "perlin"))
			get_disruption(text, cl, color, 1);
		else if (!ft_strcmp(name, "chessboard"))
			get_disruption(text, cl, color, 2);
		else
		{
			free(name);
			free(text);
			return (NULL);
		}
	}
	free(name);
	return (text);
}

void				parse_camera(char **str, t_figure *camera)
{
	char	*substr;
	char	*copy;

	copy = ft_strdup(*str);
	substr = json_get_array(copy, "\"camera\"", NULL, 0);
	free(copy);
	camera->p = json_arr_to_vector(substr, "\"origin\"", NULL, NULL);
	camera->d = json_arr_to_vector(substr, "\"direction\"", NULL, NULL);
	free(substr);
}
