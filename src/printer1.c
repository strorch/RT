/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 21:21:08 by mstorcha          #+#    #+#             */
/*   Updated: 2018/07/31 21:21:50 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		get_str_name(t_figure *figure, char **str)
{
	if (figure->type == SPHERE)
		*str = ft_strcpy(*str, "SPHERE ");
	else if (figure->type == PLANE)
		*str = ft_strcpy(*str, "PLANE ");
	else if (figure->type == CONE)
		*str = ft_strcpy(*str, "CONE ");
	else if (figure->type == DISK)
		*str = ft_strcpy(*str, "DISK ");
	else if (figure->type == CUBE)
		*str = ft_strcpy(*str, "CUBE ");
	else if (figure->type == ELLIPSOID)
		*str = ft_strcpy(*str, "ELLIPSOID ");
	else if (figure->type == DISK)
		*str = ft_strcpy(*str, "DISK ");
	else if (figure->type == PARABOLOID)
		*str = ft_strcpy(*str, "PARABOLOID ");
	else if (figure->type == CYLINDER)
		*str = ft_strcpy(*str, "CYLINDER ");
	else if (figure->type == TWOSHEET_HYPERBOLOID)
		*str = ft_strcpy(*str, "TWOSHEET HYPERBOLOID ");
	else if (figure->type == HYPERBOLOID)
		*str = ft_strcpy(*str, "HYPERBOLOID ");
}

void			print_fig_type(t_sdl *sdl, t_figure *figure, int *y)
{
	SDL_Surface	*message;
	SDL_Rect	dst;
	char		*str;

	str = ft_strnew(200);
	dst = (SDL_Rect) {.y = *y, .x = 10};
	get_str_name(figure, &str);
	str = ft_strjoinfree(str, ft_itoa(figure->index));
	TTF_SizeText(sdl->ui.heading, str, &dst.w, &dst.h);
	message = TTF_RenderText_Solid(sdl->ui.heading, str, sdl->ui.grey);
	SDL_BlitSurface(message, NULL, sdl->ui.message, &dst);
	ft_strdel(&str);
	*y = *y + dst.h;
	SDL_FreeSurface(message);
}

void			print_info_message(t_sdl *sdl, const char *str,
	char type, int *y)
{
	SDL_Surface	*message;
	SDL_Rect	dst;

	dst = (SDL_Rect) {.y = *y + 10, .x = 10};
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
	*y = *y + dst.h + 10;
	SDL_BlitSurface(message, NULL, sdl->ui.message, &dst);
	SDL_FreeSurface(message);
}
