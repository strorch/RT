/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminadzh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 16:46:08 by aminadzh          #+#    #+#             */
/*   Updated: 2018/07/21 18:57:46 by aminadzh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

cl_float3		json_arr_to_color(char *str,
					char *pattern, char *start, char *end)
{
	cl_float3	color;
	float		arr[3];
	char		**tab;
	int			i;

	start = ft_strstr(str, pattern);
	if (start == NULL)
		return (json_arr_to_color("[0,0,0]", "[", NULL, NULL));
	start = ft_strstr(start, "[");
	end = ft_strstr(start, "]");
	start = ft_get_substr(start, start + 1, end);
	tab = ft_strsplit(start, ',');
	free(start);
	i = 0;
	while (tab[i] != NULL)
	{
		arr[i] = ft_atoi(tab[i]);
		i++;
	}
	color = (cl_float3){.x = arr[0], .y = arr[1], .z = arr[2]};
	color_manage(&color);
	ft_del_str(tab);
	return (color);
}

void			get_fig_type(t_figure *object, char *str)
{
	if (ft_strstr(str, "\"sphere\"") != NULL)
		object->type = 3;
	else if (ft_strstr(str, "\"cone\"") != NULL)
		object->type = 4;
	else if (ft_strstr(str, "\"cylinder\"") != NULL)
		object->type = 5;
	else if (ft_strstr(str, "\"plane\"") != NULL)
		object->type = 6;
	else if (ft_strstr(str, "\"disk\"") != NULL)
		object->type = 7;
	else if (ft_strstr(str, "\"cube\"") != NULL)
		object->type = 8;
	else if (ft_strstr(str, "\"hyperboloid\"") != NULL)
		object->type = HYPERBOLOID;
	else if (ft_strstr(str, "\"2sheet_hyperboloid\"") != NULL)
		object->type = TWOSHEET_HYPERBOLOID;
	else if (ft_strstr(str, "\"paraboloid\"") != NULL)
		object->type = PARABOLOID;
	else if (ft_strstr(str, "\"ellipsoid\"") != NULL)
		object->type = ELLIPSOID;
}

t_figure		*get_object(char *str)
{
	t_figure	*object;

	if (!(object = (t_figure *)malloc(sizeof(t_figure))))
		return (NULL);
	get_fig_type(object, str);
	object->p = json_arr_to_vector(str, "\"origin\"", NULL, NULL);
	object->d = json_arr_to_vector(str, "\"direction\"", NULL, NULL);
	object->radius = json_get_float(str, "\"radius\"");
	(object->radius < 0) ? (object->radius = 0) : 0;
	object->size = json_get_float(str, "\"size\"");
	object->min = json_arr_to_vector(str, "\"min\"", NULL, NULL);
	object->max = json_arr_to_vector(str, "\"max\"", NULL, NULL);
	object->color = json_arr_to_color(str, "\"color\"", NULL, NULL);
	object->cap = json_get_float(str, "\"cap\"");
	object->angle = json_get_float(str, "\"angle\"");
	(object->angle < 0) ? (object->angle = 0) : 0;
	object->matirial = 0;
	object->scale = 1;
	object->rfl = json_get_float(str, "\"reflective\"");
	if (object->rfl > 0)
		object->matirial = 1;
	object->text = 1;
	return (object);
}

t_figure		*get_light(char *str)
{
	t_figure	*light;

	if (!(light = (t_figure *)malloc(sizeof(t_figure))))
		return (NULL);
	if (ft_strstr(str, "\"ambient\"") != NULL)
		light->type = 1;
	else if (ft_strstr(str, "\"point\"") != NULL)
		light->type = 2;
	else if (ft_strstr(str, "\"direct\"") != NULL)
		light->type = 3;
	light->p = json_arr_to_vector(str, "\"position\"", NULL, NULL);
	light->d = json_arr_to_vector(str, "\"direction\"", NULL, NULL);
	light->angle = json_get_float(str, "\"intensity\"");
	if (light->angle > 1 || light->angle < 0)
		light->angle = 1;
	return (light);
}

t_scene			*parse_json(char *file, t_opencl *cl)
{
	t_scene	*scene;
	char	*json_str;
	t_slist	*text_list;
	char	*copy;
	t_slist	*tmp;

	text_list = NULL;
	if (!(scene = (t_scene *)malloc(sizeof(t_scene))))
		exit_message("Memallocation error");
	json_str = ft_fgets(file);
	copy = json_str;
	if (ft_brackets(json_str, ft_strlen(json_str)) != NULL)
		exit_message("No valid");
	parse_camera(&json_str, &scene->cam);
	tmp = parse_objects(&json_str, "\"light\"", cl);
	scene->lights = array_cast(tmp, scene, 1, &text_list);
	tmp = parse_objects(&json_str, "\"objects\"", cl);
	scene->objects = array_cast(tmp, scene, 0, &text_list);
	scene->effect = 0;
	filling_textures(scene, text_list);
	free(copy);
	return (scene);
}
