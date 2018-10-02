/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_manipulator1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 21:54:45 by mstorcha          #+#    #+#             */
/*   Updated: 2018/07/31 21:54:46 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			handle_curr_obj6(t_main *mlx, int x, int y)
{
	if (x > 10 && x < 25 && y > mlx->sdl->ui.btn_pos_y[15] + HEIGHT / 3 +
		MEN_H && y < mlx->sdl->ui.btn_pos_y[15] + HEIGHT / 3 + MEN_H + 16)
		change_float_val(&mlx->scene->objects
			[mlx->sdl->ui.curr_figure->index].radius, '+', 0.2, 250);
	else if (x > 31 && x < 46 && y > mlx->sdl->ui.btn_pos_y[15] + HEIGHT / 3 +
		MEN_H && y < mlx->sdl->ui.btn_pos_y[15] + HEIGHT / 3 + MEN_H + 16)
		change_float_val(&mlx->scene->objects
			[mlx->sdl->ui.curr_figure->index].radius, '-', 0.2, 0);
	else if (x > 10 && x < 25 && y > mlx->sdl->ui.btn_pos_y[16] + HEIGHT / 3 +
		MEN_H && y < mlx->sdl->ui.btn_pos_y[16] + HEIGHT / 3 + MEN_H + 16)
		change_float_val(&mlx->scene->objects
			[mlx->sdl->ui.curr_figure->index].angle, '+', 1, 250);
	else if (x > 31 && x < 46 && y > mlx->sdl->ui.btn_pos_y[16] + HEIGHT / 3 +
		MEN_H && y < mlx->sdl->ui.btn_pos_y[16] + HEIGHT / 3 + MEN_H + 16)
		change_float_val(&mlx->scene->objects
			[mlx->sdl->ui.curr_figure->index].angle, '-', 1, 0);
	handle_curr_obj7(mlx, x, y);
}

void			handle_curr_obj7(t_main *mlx, int x, int y)
{
	if (x > 10 && x < 25 && y > mlx->sdl->ui.btn_pos_y[17] + HEIGHT / 3 +
		MEN_H && y < mlx->sdl->ui.btn_pos_y[17] + HEIGHT / 3 + MEN_H + 16)
	{
		change_float_val(&mlx->scene->objects
			[mlx->sdl->ui.curr_figure->index].rfl, '+', 0.05, 1);
		if (mlx->scene->objects[mlx->sdl->ui.curr_figure->index].rfl > 0)
			mlx->scene->objects[mlx->sdl->ui.curr_figure->index].matirial = 1;
		else
			mlx->scene->objects[mlx->sdl->ui.curr_figure->index].matirial = 0;
	}
	else if (x > 31 && x < 46 && y > mlx->sdl->ui.btn_pos_y[17] + HEIGHT / 3 +
		MEN_H && y < mlx->sdl->ui.btn_pos_y[17] + HEIGHT / 3 + MEN_H + 16)
	{
		change_float_val(&mlx->scene->objects
			[mlx->sdl->ui.curr_figure->index].rfl, '-', 0.05, 1);
		if (mlx->scene->objects[mlx->sdl->ui.curr_figure->index].rfl > 0)
			mlx->scene->objects[mlx->sdl->ui.curr_figure->index].matirial = 1;
		else
			mlx->scene->objects[mlx->sdl->ui.curr_figure->index].matirial = 0;
	}
	handle_curr_obj8(mlx, x, y);
}

void			handle_curr_obj8(t_main *mlx, int x, int y)
{
	if (x > 10 && x < 25 && y > mlx->sdl->ui.btn_pos_y[18] + HEIGHT / 3 +
		MEN_H && y < mlx->sdl->ui.btn_pos_y[18] + HEIGHT / 3 + MEN_H + 16)
		change_float_val(&mlx->scene->objects
			[mlx->sdl->ui.curr_figure->index].scale, '+', 0.05, 4);
	else if (x > 31 && x < 46 && y > mlx->sdl->ui.btn_pos_y[18] + HEIGHT / 3 +
		MEN_H && y < mlx->sdl->ui.btn_pos_y[18] + HEIGHT / 3 + MEN_H + 16)
		change_float_val(&mlx->scene->objects
			[mlx->sdl->ui.curr_figure->index].scale, '-', 0.05, 4);
}
