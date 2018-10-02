/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_parser3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 11:01:13 by mstorcha          #+#    #+#             */
/*   Updated: 2018/08/01 11:01:15 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void			get_counters(t_scene *sc, int sz, int num)
{
	if (!num)
		sc->o_num = sz;
	else
		sc->l_num = sz;
}

static void			free_tmp(t_slist **tmp)
{
	free(((t_fig_text *)(*tmp)->data)->fig);
	free((*tmp)->data);
	free((*tmp));
}

t_figure			*array_cast(t_slist *lst,
						t_scene *sc, int num, t_slist **text)
{
	int			sz;
	int			i;
	t_figure	*ret;
	t_slist		*tmp;

	sz = ft_list_count(lst);
	get_counters(sc, sz, num);
	if (!(ret = malloc(sizeof(t_figure) * sz)))
		exit_message("memory allocation err");
	i = -1;
	while (++i < sz)
	{
		tmp = lst;
		ret[i] = *(((t_fig_text *)tmp->data)->fig);
		ret[i].index = i;
		if (((t_fig_text *)tmp->data)->text && !num)
		{
			((t_fig_text *)tmp->data)->text->index = i;
			ft_list_push_back(text, ((t_fig_text *)(tmp->data))->text);
		}
		lst = lst->next;
		free_tmp(&tmp);
	}
	return (ret);
}

static t_fig_text	*fill_t_fig_text(char *obj_str, t_opencl *cl, char *type)
{
	t_fig_text	*obj;

	if (!(obj = ft_memalloc(sizeof(t_fig_text))))
		exit_message("mem alloc err");
	if (!ft_strcmp(type, "\"objects\""))
	{
		obj->fig = get_object(obj_str);
		obj->text = get_texture(obj_str, cl, obj->fig->color);
		if (!obj->text)
			obj->fig->text = 0;
	}
	else if (!ft_strcmp(type, "\"light\""))
		obj->fig = get_light(obj_str);
	return (obj);
}

t_slist				*parse_objects(char **str, char *type, t_opencl *cl)
{
	char		*substr;
	char		*obj_str;
	t_slist		*list;
	t_fig_text	*obj;
	char		*copy;

	list = NULL;
	substr = json_get_array(*str, type, NULL, 0);
	copy = substr;
	while (*substr)
	{
		obj_str = json_get_object(substr, "{");
		if (obj_str)
		{
			obj = fill_t_fig_text(obj_str, cl, type);
			ft_list_push_back(&list, obj);
		}
		free(obj_str);
		substr++;
	}
	free(copy);
	return (list);
}
