/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 13:11:32 by mstorcha          #+#    #+#             */
/*   Updated: 2018/07/31 21:04:05 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				figure_actions(t_main *mlx, int x, int y)
{
	int index;

	index = find_figure(mlx, x - SIDE_W, y - MEN_H);
	if (index == -1)
		mlx->sdl->ui.show_info = 0;
	return (index);
}

void			call_dialog(t_main *mlx)
{
	const char	*open;
	const char	*format[1] = { "*.j" };

	open = tinyfd_openFileDialog("", "./scenes/", 1, format, NULL, 0);
	if (open == NULL)
		return ;
	free(mlx->scene->textures);
	free(mlx->scene->textures_info);
	free(mlx->scene->objects);
	free(mlx->scene->lights);
	free(mlx->scene);
	mlx->sdl->ui.show_info = 0;
	mlx->scene = parse_json((char *)open, mlx->cl);
}

t_figure		new_ambient(float intensity)
{
	t_figure	light;

	light.type = 3;
	light.angle = intensity;
	light.p = (cl_float3){.x=0, .y=-1, .z=-2};
	return (light);
}

t_scene			*empty_scene(void)
{
	t_scene		*scene;

	if (!(scene = (t_scene *)malloc(sizeof(t_scene))))
		exit_message("Memallocation error");
	scene->l_num = 1;
	scene->o_num = 1;
	scene->cam.p = (cl_float3){.x = 0, .y = 0, .z = 0};
	scene->cam.d = (cl_float3){.x = 0, .y = 0, .z = 0};
	scene->lights = (t_figure *)malloc(sizeof(t_figure));
	scene->lights[0].type = 3;
	scene->lights[0].angle = 0.5;
	scene->lights[0].p = (cl_float3){.x=0, .y=-1, .z=-2};
	scene->objects = (t_figure *)malloc(sizeof(t_figure));
	scene->objects[0].type = 1;
	scene->objects[0].radius = 0.01;
	scene->objects[0].p = (cl_float3){.x = 100, .y = 100, .z = 100};
	scene->objects[0].color = (cl_float3){.x = 0, .y = 0, .z = 0};
	filling_textures(scene, NULL);
	scene->effect = 0;
	return (scene);
}

void			del_scene(t_main *mlx)
{
	free(mlx->scene->textures_info);
	free(mlx->scene->textures);
	free(mlx->scene->objects);
	free(mlx->scene->lights);
	free(mlx->scene);
	mlx->scene = empty_scene();
	mlx->sdl->ui.show_info = 0;
}
