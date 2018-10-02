/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_interface.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminadzh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 17:02:41 by aminadzh          #+#    #+#             */
/*   Updated: 2018/07/22 15:27:14 by aminadzh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			draw_button(t_sdl *sdl, int i, int x, int width)
{
	SDL_Rect	dst;

	dst = (SDL_Rect){.x = x, .y = 15, .h = BT_H, .w = width};
	if (i < BT_COUNT)
		SDL_BlitSurface(sdl->ui.menu_button[i], NULL, sdl->ui.menu, &dst);
}

void			draw_menu(t_sdl *sdl)
{
	draw_button(sdl, 0, 20, 72);
	draw_button(sdl, 1, 112, 76);
	draw_button(sdl, 2, 208, 70);
	draw_button(sdl, 3, 298, 117);
	draw_button(sdl, 4, 435, 85);
	draw_button(sdl, 5, 540, 77);
	draw_button(sdl, 6, 637, 72);
	draw_button(sdl, 7, 729, 97);
	draw_button(sdl, 8, 846, 68);
	draw_button(sdl, 9, 934, 71);
	draw_button(sdl, 11, 1025, 71);
	draw_button(sdl, 12, 1116, 79);
	draw_button(sdl, 13, 1215, 84);
	draw_button(sdl, 14, 1319, 64);
	draw_button(sdl, 10, 1404, 80);
}

void			print_message(t_sdl *sdl, const char *str, char type, int *y)
{
	SDL_Surface	*message;
	SDL_Rect	dst;

	dst = (SDL_Rect) {.y = *y, .x = 10};
	if (type == 'h')
	{
		TTF_SizeText(sdl->ui.heading, str, &dst.w, &dst.h);
		message = TTF_RenderText_Solid(sdl->ui.heading, str, sdl->ui.grey);
	}
	else
	{
		TTF_SizeText(sdl->ui.par, str, &dst.w, &dst.h);
		message = TTF_RenderText_Solid(sdl->ui.par, str, sdl->ui.black);
	}
	*y = *y + dst.h;
	SDL_BlitSurface(message, NULL, sdl->ui.sb, &dst);
	SDL_FreeSurface(message);
}

void			user_interface(t_sdl *sdl, t_scene *scene)
{
	SDL_Rect	menu_dst;
	SDL_Rect	sb_dst;

	menu_dst = (SDL_Rect){.x = 0, .y = 0, .h = MEN_H, .w = WIDTH + SIDE_W};
	sb_dst = (SDL_Rect){.x = 0, .y = MEN_H, .h = HEIGHT, .w = SIDE_W};
	draw_menu(sdl);
	draw_sidebar(sdl, scene);
	sdl->ui.menu_text = SDL_CreateTextureFromSurface(sdl->rend, sdl->ui.menu);
	sdl->ui.sb_text = SDL_CreateTextureFromSurface(sdl->rend, sdl->ui.sb);
	SDL_RenderCopy(sdl->rend, sdl->ui.menu_text, NULL, &menu_dst);
	SDL_RenderCopy(sdl->rend, sdl->ui.sb_text, NULL, &sb_dst);
	SDL_DestroyTexture(sdl->ui.sb_text);
}

void			set_curr_fig(t_figure **curr, t_figure *fig, int i)
{
	if (!fig || (i < 0 && i != -1))
		exit_message("index error");
	*curr = &fig[i];
	(*curr)->index = i;
}
