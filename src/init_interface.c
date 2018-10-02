/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_interface.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminadzh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 19:15:05 by aminadzh          #+#    #+#             */
/*   Updated: 2018/07/30 19:15:07 by aminadzh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			init_ui(t_sdl *sdl)
{
	if (TTF_Init() == -1)
		exit_message("Error in initialising TTF");
	if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == -1)
		exit_message("Error in initialising IMG");
	if (!(sdl->ui.menu = SDL_CreateRGBSurface(0, WIDTH + SIDE_W, MEN_H, 32,
					0, 0, 0, 0)))
		exit_message("Error in creating UI");
	if (!(sdl->ui.sb = SDL_CreateRGBSurface(0, SIDE_W, HEIGHT, 32,
					0, 0, 0, 0)))
		exit_message("Error in creating UI");
	if (!(sdl->ui.message = SDL_CreateRGBSurface(0, SIDE_W, HEIGHT, 32,
					0, 0, 0, 0)))
		exit_message("Error in creating UI");
	if (!(sdl->ui.heading = TTF_OpenFont("./fonts/LiberationBold.ttf", 20))
		|| !(sdl->ui.par = TTF_OpenFont("./fonts/Liberation.ttf", 18)))
		exit_message("Error in creating font");
	SDL_FillRect(sdl->ui.menu, NULL, SDL_MapRGB(sdl->ui.menu->format,
		108, 109, 105));
	init_buttons(sdl->ui.menu_button);
	sdl->ui.grey = (SDL_Color) {.r = 128, .g = 128, .b = 128, .a = 255};
	sdl->ui.black = (SDL_Color) {.r = 39, .g = 40, .b = 34, .a = 255};
	sdl->ui.show_info = 0;
}

void			init_buttons(SDL_Surface **menu_button)
{
	menu_button[0] = create_button("./images/button_load_1.png");
	menu_button[1] = create_button("./images/button_reset_1.png");
	menu_button[2] = create_button("./images/button_save_1.png");
	menu_button[3] = create_button("./images/button_screenshot_1.png");
	menu_button[4] = create_button("./images/button_sphere_1.png");
	menu_button[5] = create_button("./images/button_plane_1.png");
	menu_button[6] = create_button("./images/button_cone_1.png");
	menu_button[7] = create_button("./images/button_cylinder_1.png");
	menu_button[8] = create_button("./images/button_disk.png");
	menu_button[9] = create_button("./images/button_cube.png");
	menu_button[10] = create_button("./images/button_effect.png");
	menu_button[11] = create_button("./images/button_elips.png");
	menu_button[12] = create_button("./images/button_parab.png");
	menu_button[13] = create_button("./images/button_tw-hy.png");
	menu_button[14] = create_button("./images/button_hyp.png");
	menu_button[15] = create_button("./images/button_plus.png");
	menu_button[16] = create_button("./images/button_minus.png");
}

SDL_Surface		*create_button(char *src)
{
	SDL_Surface	*surface;

	surface = IMG_Load(src);
	if (!surface)
		printf("IMG_Load: %s\n", IMG_GetError());
	return (surface);
}

char			*ft_strjoinfree(char *s1, char *s2)
{
	char		*new;
	size_t		len1;
	size_t		len2;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!(new = ft_strnew(len1 + len2)))
		return (NULL);
	ft_strcat(new, s1);
	ft_strcat(new, s2);
	ft_strdel(&s1);
	ft_strdel(&s2);
	return (new);
}

char			*ft_strjoinlit(char *s1, const char *s2)
{
	char		*new;
	size_t		len1;
	size_t		len2;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!(new = ft_strnew(len1 + len2)))
		return (NULL);
	ft_strcat(new, s1);
	ft_strcat(new, s2);
	ft_strdel(&s1);
	return (new);
}
