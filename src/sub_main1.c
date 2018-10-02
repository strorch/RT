/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_main1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 12:11:33 by mstorcha          #+#    #+#             */
/*   Updated: 2018/08/01 12:11:37 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#define K_K key.keysym.scancode
#define E_TYPE type

void	init_sdl(t_sdl *sdl)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		exit_message("Error in init sdl");
	if (!(sdl->wind = SDL_CreateWindow("RT",
						SDL_WINDOWPOS_UNDEFINED,
						SDL_WINDOWPOS_UNDEFINED, WIDTH + SIDE_W, HEIGHT + MEN_H,
						SDL_WINDOW_SHOWN)))
		exit_message("Error creating window");
	if (!(sdl->rend = SDL_CreateRenderer(sdl->wind, -1,
							SDL_RENDERER_ACCELERATED)))
		exit_message("Error in creating renderer");
	if (!(sdl->sur = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 32, 0, 0, 0, 0)))
		exit_message("Error in creating surface");
	if (!(sdl->ui.menu_button =
		(SDL_Surface **)malloc(sizeof(SDL_Surface *) * BT_COUNT)))
		exit_message("Error in UI");
	sdl->keyboard_state = SDL_GetKeyboardState(NULL);
}

void	effects(int *a)
{
	(*a)++;
	*a = *a % 7;
}

void	key_events(t_main *mlx, SDL_Event *event)
{
	(event->K_K == SDL_SCANCODE_ESCAPE) ? exit(0) : 0;
	(event->K_K == SDL_SCANCODE_UP) ? (mlx->scene->cam.d.x += 5) : 0;
	(event->K_K == SDL_SCANCODE_DOWN) ? (mlx->scene->cam.d.x -= 5) : 0;
	(event->K_K == SDL_SCANCODE_LEFT) ? (mlx->scene->cam.d.y += 5) : 0;
	(event->K_K == SDL_SCANCODE_RIGHT) ? (mlx->scene->cam.d.y -= 5) : 0;
	(event->K_K == SDL_SCANCODE_A) ? (mlx->scene->cam.p.x -= 0.5f) : 0;
	(event->K_K == SDL_SCANCODE_D) ? (mlx->scene->cam.p.x += 0.5f) : 0;
	(event->K_K == SDL_SCANCODE_W) ? (mlx->scene->cam.p.z += 0.5f) : 0;
	(event->K_K == SDL_SCANCODE_S) ? (mlx->scene->cam.p.z -= 0.5f) : 0;
	(event->K_K == SDL_SCANCODE_E) ? (mlx->scene->cam.p.y += 0.5f) : 0;
	(event->K_K == SDL_SCANCODE_Q) ? (mlx->scene->cam.p.y -= 0.5f) : 0;
}

void	mouse_events1(t_main *mlx)
{
	int		x;
	int		y;

	SDL_GetMouseState(&x, &y);
	if (x > 20 && x < 92 && y > 15 && y < BT_H + 15)
		call_dialog(mlx);
	else if (x > 112 && x < 188 && y > 15 && y < BT_H + 15)
		del_scene(mlx);
	else if (x > 208 && x < 278 && y > 15 && y < BT_H + 15)
		write_in_file(*mlx->scene);
	else if (x > 298 && x < 415 && y > 15 && y < BT_H + 15)
		screen_shoot(*mlx);
	else if (x > 435 && x < 520 && y > 15 && y < BT_H + 15)
		add_figure(mlx, &mlx->scene->objects, mlx->scene->cam, 's');
	else if (x > 540 && x < 617 && y > 15 && y < BT_H + 15)
		add_figure(mlx, &mlx->scene->objects, mlx->scene->cam, 'p');
	else if (x > 637 && x < 709 && y > 15 && y < BT_H + 15)
		add_figure(mlx, &mlx->scene->objects, mlx->scene->cam, 'c');
	else if (x > 729 && x < 826 && y > 15 && y < BT_H + 15)
		add_figure(mlx, &mlx->scene->objects, mlx->scene->cam, 'y');
	handle_curr_obj(mlx, x, y);
}

void	mouse_events2(t_main *mlx)
{
	int		x;
	int		y;

	SDL_GetMouseState(&x, &y);
	if (x > 846 && x < 914 && y > 15 && y < BT_H + 15)
		add_figure(mlx, &mlx->scene->objects, mlx->scene->cam, 'd');
	else if (x > 934 && x < 1005 && y > 15 && y < BT_H + 15)
		add_figure(mlx, &mlx->scene->objects, mlx->scene->cam, 'k');
	else if (x > 1025 && x < 1096 && y > 15 && y < BT_H + 15)
		add_figure(mlx, &mlx->scene->objects, mlx->scene->cam, 'e');
	else if (x > 1116 && x < 1195 && y > 15 && y < BT_H + 15)
		add_figure(mlx, &mlx->scene->objects, mlx->scene->cam, 'a');
	else if (x > 1215 && x < 1299 && y > 15 && y < BT_H + 15)
		add_figure(mlx, &mlx->scene->objects, mlx->scene->cam, 't');
	else if (x > 1319 && x < 1384 && y > 15 && y < BT_H + 15)
		add_figure(mlx, &mlx->scene->objects, mlx->scene->cam, 'h');
	else if (x > 1404 && x < 1484 && y > 15 && y < BT_H + 15)
		effects(&mlx->scene->effect);
	else if (x > SIDE_W && y > MEN_H)
	{
		mlx->sdl->ui.show_info = 1;
		set_curr_fig(&mlx->sdl->ui.curr_figure,
			mlx->scene->objects, figure_actions(mlx, x, y));
	}
	handle_curr_obj(mlx, x, y);
}
