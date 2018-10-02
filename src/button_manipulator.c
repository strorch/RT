/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_manipulator.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminadzh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 19:45:43 by aminadzh          #+#    #+#             */
/*   Updated: 2018/07/30 19:45:45 by aminadzh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			handle_curr_obj(t_main *mlx, int x, int y)
{
	if (x > 10 && x < 25 && y > mlx->sdl->ui.btn_pos_y[0] + HEIGHT / 3 + MEN_H
		&& y < mlx->sdl->ui.btn_pos_y[0] + HEIGHT / 3 + MEN_H + 16)
		change_float_val(&mlx->scene->objects
			[mlx->sdl->ui.curr_figure->index].p.x, '+', 0.2, 0);
	else if (x > 31 && x < 46 && y > mlx->sdl->ui.btn_pos_y[0] + HEIGHT / 3 +
		MEN_H && y < mlx->sdl->ui.btn_pos_y[0] + HEIGHT / 3 + MEN_H + 16)
		change_float_val(&mlx->scene->objects
			[mlx->sdl->ui.curr_figure->index].p.x, '-', 0.2, 0);
	else if (x > 10 && x < 25 && y > mlx->sdl->ui.btn_pos_y[1] + HEIGHT / 3 +
		MEN_H && y < mlx->sdl->ui.btn_pos_y[1] + HEIGHT / 3 + MEN_H + 16)
		change_float_val(&mlx->scene->objects
			[mlx->sdl->ui.curr_figure->index].p.y, '+', 0.2, 0);
	else if (x > 31 && x < 46 && y > mlx->sdl->ui.btn_pos_y[1] + HEIGHT / 3 +
		MEN_H && y < mlx->sdl->ui.btn_pos_y[1] + HEIGHT / 3 + MEN_H + 16)
		change_float_val(&mlx->scene->objects
			[mlx->sdl->ui.curr_figure->index].p.y, '-', 0.2, 0);
	else if (x > 10 && x < 25 && y > mlx->sdl->ui.btn_pos_y[2] + HEIGHT / 3 +
		MEN_H && y < mlx->sdl->ui.btn_pos_y[2] + HEIGHT / 3 + MEN_H + 16)
		change_float_val(&mlx->scene->objects
			[mlx->sdl->ui.curr_figure->index].p.z, '+', 0.2, 0);
	else if (x > 31 && x < 46 && y > mlx->sdl->ui.btn_pos_y[2] + HEIGHT / 3 +
		MEN_H && y < mlx->sdl->ui.btn_pos_y[2] + HEIGHT / 3 + MEN_H + 16)
		change_float_val(&mlx->scene->objects
			[mlx->sdl->ui.curr_figure->index].p.z, '-', 0.2, 0);
	handle_curr_obj2(mlx, x, y);
}

void			handle_curr_obj2(t_main *mlx, int x, int y)
{
	if (x > 10 && x < 25 && y > mlx->sdl->ui.btn_pos_y[3] + HEIGHT / 3 +
		MEN_H && y < mlx->sdl->ui.btn_pos_y[3] + HEIGHT / 3 + MEN_H + 16)
		change_float_val(&mlx->scene->objects
			[mlx->sdl->ui.curr_figure->index].d.x, '+', 0.2, 0);
	else if (x > 31 && x < 46 && y > mlx->sdl->ui.btn_pos_y[3] + HEIGHT / 3 +
		MEN_H && y < mlx->sdl->ui.btn_pos_y[3] + HEIGHT / 3 + MEN_H + 16)
		change_float_val(&mlx->scene->objects
			[mlx->sdl->ui.curr_figure->index].d.x, '-', 0.2, 0);
	else if (x > 10 && x < 25 && y > mlx->sdl->ui.btn_pos_y[4] + HEIGHT / 3 +
		MEN_H && y < mlx->sdl->ui.btn_pos_y[4] + HEIGHT / 3 + MEN_H + 16)
		change_float_val(&mlx->scene->objects
			[mlx->sdl->ui.curr_figure->index].d.y, '+', 0.2, 0);
	else if (x > 31 && x < 46 && y > mlx->sdl->ui.btn_pos_y[4] + HEIGHT / 3 +
		MEN_H && y < mlx->sdl->ui.btn_pos_y[4] + HEIGHT / 3 + MEN_H + 16)
		change_float_val(&mlx->scene->objects
			[mlx->sdl->ui.curr_figure->index].d.y, '-', 0.2, 0);
	else if (x > 10 && x < 25 && y > mlx->sdl->ui.btn_pos_y[5] + HEIGHT / 3 +
		MEN_H && y < mlx->sdl->ui.btn_pos_y[5] + HEIGHT / 3 + MEN_H + 16)
		change_float_val(&mlx->scene->objects
			[mlx->sdl->ui.curr_figure->index].d.z, '+', 0.2, 0);
	else if (x > 31 && x < 46 && y > mlx->sdl->ui.btn_pos_y[5] + HEIGHT / 3 +
		MEN_H && y < mlx->sdl->ui.btn_pos_y[5] + HEIGHT / 3 + MEN_H + 16)
		change_float_val(&mlx->scene->objects
			[mlx->sdl->ui.curr_figure->index].d.z, '-', 0.2, 0);
	handle_curr_obj3(mlx, x, y);
}

void			handle_curr_obj3(t_main *mlx, int x, int y)
{
	if (x > 10 && x < 25 && y > mlx->sdl->ui.btn_pos_y[6] + HEIGHT / 3 +
		MEN_H && y < mlx->sdl->ui.btn_pos_y[6] + HEIGHT / 3 + MEN_H + 16)
		change_float_val(&mlx->scene->objects
			[mlx->sdl->ui.curr_figure->index].min.x, '+', 0.2, 0);
	else if (x > 31 && x < 46 && y > mlx->sdl->ui.btn_pos_y[6] + HEIGHT / 3 +
		MEN_H && y < mlx->sdl->ui.btn_pos_y[6] + HEIGHT / 3 + MEN_H + 16)
		change_float_val(&mlx->scene->objects
			[mlx->sdl->ui.curr_figure->index].min.x, '-', 0.2, 0);
	else if (x > 10 && x < 25 && y > mlx->sdl->ui.btn_pos_y[7] + HEIGHT / 3 +
		MEN_H && y < mlx->sdl->ui.btn_pos_y[7] + HEIGHT / 3 + MEN_H + 16)
		change_float_val(&mlx->scene->objects
			[mlx->sdl->ui.curr_figure->index].min.y, '+', 0.2, 0);
	else if (x > 31 && x < 46 && y > mlx->sdl->ui.btn_pos_y[7] + HEIGHT / 3 +
		MEN_H && y < mlx->sdl->ui.btn_pos_y[7] + HEIGHT / 3 + MEN_H + 16)
		change_float_val(&mlx->scene->objects
			[mlx->sdl->ui.curr_figure->index].min.y, '-', 0.2, 0);
	else if (x > 10 && x < 25 && y > mlx->sdl->ui.btn_pos_y[8] + HEIGHT / 3 +
		MEN_H && y < mlx->sdl->ui.btn_pos_y[8] + HEIGHT / 3 + MEN_H + 16)
		change_float_val(&mlx->scene->objects
			[mlx->sdl->ui.curr_figure->index].min.z, '+', 0.2, 0);
	else if (x > 31 && x < 46 && y > mlx->sdl->ui.btn_pos_y[8] + HEIGHT / 3 +
		MEN_H && y < mlx->sdl->ui.btn_pos_y[8] + HEIGHT / 3 + MEN_H + 16)
		change_float_val(&mlx->scene->objects
			[mlx->sdl->ui.curr_figure->index].min.z, '-', 0.2, 0);
	handle_curr_obj4(mlx, x, y);
}

void			handle_curr_obj4(t_main *mlx, int x, int y)
{
	if (x > 10 && x < 25 && y > mlx->sdl->ui.btn_pos_y[9] + HEIGHT / 3 +
		MEN_H && y < mlx->sdl->ui.btn_pos_y[9] + HEIGHT / 3 + MEN_H + 16)
		change_float_val(&mlx->scene->objects
			[mlx->sdl->ui.curr_figure->index].max.x, '+', 0.1, 0);
	else if (x > 31 && x < 46 && y > mlx->sdl->ui.btn_pos_y[9] + HEIGHT / 3 +
		MEN_H && y < mlx->sdl->ui.btn_pos_y[9] + HEIGHT / 3 + MEN_H + 16)
		change_float_val(&mlx->scene->objects
			[mlx->sdl->ui.curr_figure->index].max.x, '-', 0.1, 0);
	else if (x > 10 && x < 25 && y > mlx->sdl->ui.btn_pos_y[10] + HEIGHT / 3 +
		MEN_H && y < mlx->sdl->ui.btn_pos_y[10] + HEIGHT / 3 + MEN_H + 16)
		change_float_val(&mlx->scene->objects
			[mlx->sdl->ui.curr_figure->index].max.y, '+', 0.1, 0);
	else if (x > 31 && x < 46 && y > mlx->sdl->ui.btn_pos_y[10] + HEIGHT / 3 +
		MEN_H && y < mlx->sdl->ui.btn_pos_y[10] + HEIGHT / 3 + MEN_H + 16)
		change_float_val(&mlx->scene->objects
			[mlx->sdl->ui.curr_figure->index].max.y, '-', 0.1, 0);
	else if (x > 10 && x < 25 && y > mlx->sdl->ui.btn_pos_y[11] + HEIGHT / 3 +
		MEN_H && y < mlx->sdl->ui.btn_pos_y[11] + HEIGHT / 3 + MEN_H + 16)
		change_float_val(&mlx->scene->objects
			[mlx->sdl->ui.curr_figure->index].max.z, '+', 0.1, 0);
	else if (x > 31 && x < 46 && y > mlx->sdl->ui.btn_pos_y[11] + HEIGHT / 3 +
		MEN_H && y < mlx->sdl->ui.btn_pos_y[11] + HEIGHT / 3 + MEN_H + 16)
		change_float_val(&mlx->scene->objects
			[mlx->sdl->ui.curr_figure->index].max.z, '-', 0.1, 0);
	handle_curr_obj5(mlx, x, y);
}

void			handle_curr_obj5(t_main *mlx, int x, int y)
{
	if (x > 10 && x < 25 && y > mlx->sdl->ui.btn_pos_y[12] + HEIGHT / 3 +
		MEN_H && y < mlx->sdl->ui.btn_pos_y[12] + HEIGHT / 3 + MEN_H + 16)
		change_float_val(&mlx->scene->objects
			[mlx->sdl->ui.curr_figure->index].color.x, '+', 1, 250);
	else if (x > 31 && x < 46 && y > mlx->sdl->ui.btn_pos_y[12] + HEIGHT / 3 +
		MEN_H && y < mlx->sdl->ui.btn_pos_y[12] + HEIGHT / 3 + MEN_H + 16)
		change_float_val(&mlx->scene->objects
			[mlx->sdl->ui.curr_figure->index].color.x, '-', 1, 250);
	else if (x > 10 && x < 25 && y > mlx->sdl->ui.btn_pos_y[13] + HEIGHT / 3 +
		MEN_H && y < mlx->sdl->ui.btn_pos_y[13] + HEIGHT / 3 + MEN_H + 16)
		change_float_val(&mlx->scene->objects
			[mlx->sdl->ui.curr_figure->index].color.y, '+', 1, 250);
	else if (x > 31 && x < 46 && y > mlx->sdl->ui.btn_pos_y[13] + HEIGHT / 3 +
		MEN_H && y < mlx->sdl->ui.btn_pos_y[13] + HEIGHT / 3 + MEN_H + 16)
		change_float_val(&mlx->scene->objects
			[mlx->sdl->ui.curr_figure->index].color.y, '-', 1, 250);
	else if (x > 10 && x < 25 && y > mlx->sdl->ui.btn_pos_y[14] + HEIGHT / 3 +
		MEN_H && y < mlx->sdl->ui.btn_pos_y[14] + HEIGHT / 3 + MEN_H + 16)
		change_float_val(&mlx->scene->objects
			[mlx->sdl->ui.curr_figure->index].color.z, '+', 1, 250);
	else if (x > 31 && x < 46 && y > mlx->sdl->ui.btn_pos_y[14] + HEIGHT / 3 +
		MEN_H && y < mlx->sdl->ui.btn_pos_y[14] + HEIGHT / 3 + MEN_H + 16)
		change_float_val(&mlx->scene->objects
			[mlx->sdl->ui.curr_figure->index].color.z, '-', 1, 250);
	handle_curr_obj6(mlx, x, y);
}
