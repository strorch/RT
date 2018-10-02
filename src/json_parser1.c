/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_parser1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 11:19:35 by mstorcha          #+#    #+#             */
/*   Updated: 2018/08/01 11:19:36 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int		size_texture(t_slist *lst)
{
	int			i;
	t_texture	*tmp;

	i = 0;
	while (lst)
	{
		tmp = lst->data;
		i += tmp->h * tmp->w;
		lst = lst->next;
	}
	return (i);
}

int				*ft_intcat(int *dest, int *src, int *sz1, int sz2)
{
	int i;

	i = -1;
	while (++i < sz2)
	{
		dest[i + *sz1] = src[i];
	}
	*sz1 += sz2;
	return (dest);
}

int				*get_texture_array(t_slist *lst)
{
	int			*res;
	t_texture	*tmp_text;
	int			*tmp_int;
	int			size;
	int			count;

	count = 0;
	size = size_texture(lst);
	if (!(res = (int *)malloc(sizeof(int) * size)))
		return (NULL);
	while (lst)
	{
		tmp_text = lst->data;
		tmp_int = tmp_text->pix;
		res = ft_intcat(res, tmp_int, &count, tmp_text->h * tmp_text->w);
		lst = lst->next;
	}
	return (res);
}

void			*free_lst1(t_slist *list)
{
	t_slist *tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free(((t_texture *)tmp->data)->pix);
		free(tmp->data);
		free(tmp);
	}
	return (NULL);
}

void			filling_textures(t_scene *scene, t_slist *text_list)
{
	if (!text_list)
	{
		scene->textures_num = 1;
		scene->textures = malloc(sizeof(int));
		scene->textures[0] = 0;
		scene->textures_info = malloc(sizeof(cl_int3));
		scene->textures_info[0] = (cl_int3){.x=0, .y=0, .z=0};
	}
	else
	{
		scene->textures = get_texture_array(text_list);
		scene->textures_num = ft_list_count(text_list);
		scene->textures_info = get_texture_info(text_list);
		free_lst1(text_list);
	}
}
