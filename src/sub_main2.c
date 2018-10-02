/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_main2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 12:11:41 by mstorcha          #+#    #+#             */
/*   Updated: 2018/08/01 12:11:45 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#define K_K key.keysym.scancode
#define E_TYPE type

cl_float3	vector_add(cl_float3 vec1, cl_float3 vec2)
{
	cl_float3	new;

	new.x = vec1.x + vec2.x;
	new.y = vec1.y + vec2.y;
	new.z = vec1.z + vec2.z;
	return (new);
}

cl_float3	vector_subtract(cl_float3 vec1, cl_float3 vec2)
{
	cl_float3	new;

	new.x = vec1.x - vec2.x;
	new.y = vec1.y - vec2.y;
	new.z = vec1.z - vec2.z;
	return (new);
}

void		mousewheel_events(t_main *mlx, SDL_Event *event)
{
	int		x;
	int		y;

	SDL_GetMouseState(&x, &y);
	if (mlx->sdl->keyboard_state[SDL_SCANCODE_LSHIFT]
		&& x > SIDE_W && y > MEN_H)
	{
		if (event->wheel.y > 0)
			mlx->scene->cam.p =
		vector_add(mlx->scene->cam.p, mlx->scene->cam.color);
		else if (event->wheel.y < 0)
			mlx->scene->cam.p =
		vector_subtract(mlx->scene->cam.p, mlx->scene->cam.color);
	}
}

void		mousemove_events(t_main *mlx)
{
	int		x;
	int		y;

	SDL_GetMouseState(&x, &y);
	if (mlx->sdl->keyboard_state[SDL_SCANCODE_LSHIFT]
		&& x > SIDE_W && y > MEN_H)
	{
		if (x > mlx->prev.mouse_x)
			mlx->scene->cam.d.y -= 0.5;
		else if (x < mlx->prev.mouse_x)
			mlx->scene->cam.d.y += 0.5;
		if (y > mlx->prev.mouse_y)
			mlx->scene->cam.d.x -= 0.5;
		else if (y < mlx->prev.mouse_y)
			mlx->scene->cam.d.x += 0.5;
	}
	mlx->prev.mouse_x = x;
	mlx->prev.mouse_y = y;
}
