/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sidebar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminadzh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 19:27:30 by aminadzh          #+#    #+#             */
/*   Updated: 2018/07/30 19:27:32 by aminadzh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			draw_sidebar(t_sdl *sdl, t_scene *scene)
{
	int			pos;
	char		*message;
	int			i;

	SDL_FillRect(sdl->ui.sb, NULL, SDL_MapRGB(sdl->ui.sb->format,
		235, 237, 239));
	pos = 10;
	print_message(sdl, "CAMERA", 'h', &pos);
	message = cam_pos_message(scene->cam, 'p');
	print_message(sdl, message, 'p', &pos);
	free(message);
	message = cam_pos_message(scene->cam, 'd');
	print_message(sdl, message, 'p', &pos);
	free(message);
	print_message(sdl, "LIGHT", 'h', &pos);
	i = -1;
	while (++i < scene->l_num)
	{
		message = light_message(scene->lights, i);
		print_message(sdl, message, 'p', &pos);
		ft_strdel(&message);
	}
	if (sdl->ui.show_info == 1)
		show_fig_info(sdl, sdl->ui.curr_figure);
}

char			*cam_pos_message(t_figure cam, char type)
{
	char		*message;

	message = ft_strnew(1);
	if (type == 'p')
	{
		message = ft_strjoinlit(message, "Origin: x ");
		message = ft_strjoinfree(message, ft_ftoa(cam.p.x));
		message = ft_strjoinlit(message, " y ");
		message = ft_strjoinfree(message, ft_ftoa(cam.p.y));
		message = ft_strjoinlit(message, " z ");
		message = ft_strjoinfree(message, ft_ftoa(cam.p.z));
		message = ft_strjoinlit(message, "");
	}
	else
	{
		message = ft_strjoinlit(message, "Direction: x ");
		message = ft_strjoinfree(message, ft_ftoa(cam.d.x));
		message = ft_strjoinlit(message, " y ");
		message = ft_strjoinfree(message, ft_ftoa(cam.d.y));
		message = ft_strjoinlit(message, " z ");
		message = ft_strjoinfree(message, ft_ftoa(cam.d.z));
		message = ft_strjoinlit(message, "");
	}
	return (message);
}

char			*light_message(t_figure *light, int i)
{
	char		*mes;

	mes = ft_strnew(1);
	if (light[i].type == 1)
	{
		mes = ft_strjoinlit(mes, "Ambient: i ");
		mes = ft_strjoinfree(mes, ft_ftoa(light[i].angle));
		return (mes);
	}
	else if (light[i].type == 2)
		mes = ft_strjoinlit(mes, "Point: i ");
	else
		mes = ft_strjoinlit(mes, "Direct: i ");
	mes = ft_strjoinfree(mes, ft_ftoa(light[i].angle));
	mes = ft_strjoinlit(mes, " x ");
	mes = ft_strjoinfree(mes, ft_ftoa(light[i].p.x));
	mes = ft_strjoinlit(mes, " y ");
	mes = ft_strjoinfree(mes, ft_ftoa(light[i].p.y));
	mes = ft_strjoinlit(mes, " z ");
	mes = ft_strjoinfree(mes, ft_ftoa(light[i].p.z));
	return (mes);
}

void			show_fig_info1(t_sdl *sdl, t_figure *curr, int *pos)
{
	print_fig_type(sdl, curr, pos);
	print_info_message(sdl, "Position:", 'p', pos);
	print_fig_pos(sdl, curr, pos, "x\0y\0z\0");
	print_info_message(sdl, "Direction:", 'p', pos);
	print_fig_dir(sdl, curr, pos, "x\0y\0z\0");
	print_info_message(sdl, "Min:", 'p', pos);
	print_fig_min(sdl, curr, pos, "x\0y\0z\0");
	print_info_message(sdl, "Max:", 'p', pos);
	print_fig_max(sdl, curr, pos, "x\0y\0z\0");
	print_info_message(sdl, "Color:", 'p', pos);
	print_fig_col(sdl, curr, pos, "r\0g\0b\0");
	print_info_message(sdl, "Radius:", 'p', pos);
	print_fig_float(sdl, curr->radius, pos, 15);
	print_info_message(sdl, "Angle:", 'p', pos);
	print_fig_float(sdl, curr->angle, pos, 16);
	print_info_message(sdl, "Reflectiveness:", 'p', pos);
	print_fig_float(sdl, curr->rfl, pos, 17);
	print_info_message(sdl, "Scale:", 'p', pos);
	print_fig_float(sdl, curr->scale, pos, 18);
}

void			show_fig_info(t_sdl *sdl, t_figure *curr)
{
	SDL_Rect	dst;
	int			pos;

	pos = 10;
	dst = (SDL_Rect){.x = 0, .y = HEIGHT / 3, .h = HEIGHT / 3 * 2, .w = SIDE_W};
	SDL_FillRect(sdl->ui.message, NULL, SDL_MapRGB(sdl->ui.message->format,
		235, 237, 239));
	show_fig_info1(sdl, curr, &pos);
	draw_info_btns(sdl);
	SDL_BlitSurface(sdl->ui.message, NULL, sdl->ui.sb, &dst);
}
