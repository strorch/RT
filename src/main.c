/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 13:20:54 by mstorcha          #+#    #+#             */
/*   Updated: 2018/05/23 13:21:42 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#define K_K key.keysym.scancode
#define E_TYPE type

void	sdl_events(t_main *mlx, SDL_Event *event)
{
	cl_float3	d;

	d.x = 0;
	d.y = 0;
	d.z = 1;
	mlx->scene->cam.color = rotate_ort(d, mlx->scene->cam.d);
	mlx->scene->cam.color = get_unit_vector(mlx->scene->cam.color);
	while (SDL_PollEvent(event))
	{
		if (event->E_TYPE == SDL_KEYDOWN)
			key_events(mlx, event);
		else if (event->E_TYPE == SDL_MOUSEBUTTONDOWN)
		{
			mouse_events1(mlx);
			mouse_events2(mlx);
		}
		else if (event->E_TYPE == SDL_MOUSEWHEEL)
			mousewheel_events(mlx, event);
		else if (event->E_TYPE == SDL_MOUSEMOTION)
			mousemove_events(mlx);
		else if (event->E_TYPE == SDL_QUIT)
			exit(1);
	}
}

void	exit_rt(void)
{
	TTF_Quit();
	SDL_Quit();
}

int		main(int argc, char **argv)
{
	t_main		mlx;
	SDL_Event	event;

	if (argc != 2)
		return (0);
	cl_init(&mlx);
	mlx.scene = parse_json(argv[1], mlx.cl);
	init_sdl(mlx.sdl);
	init_ui(mlx.sdl);
	while (1)
	{
		sdl_events(&mlx, &event);
		rendering(&mlx);
	}
	exit_rt();
	return (0);
}
