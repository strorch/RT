/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminadzh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 19:40:13 by aminadzh          #+#    #+#             */
/*   Updated: 2018/07/30 19:40:15 by aminadzh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			print_fig_col(t_sdl *sdl, t_figure *figure, int *y, char *patt)
{
	SDL_Surface	*message;
	SDL_Rect	dst;
	char		*str;
	int			i;

	i = -1;
	while (++i < 3)
	{
		str = ft_strnew(100);
		str = ft_strcpy(str, &patt[i + i]);
		if (i == 0)
			str = ft_strjoinfree(str, ft_itoa((int)figure->color.x));
		else if (i == 1)
			str = ft_strjoinfree(str, ft_itoa((int)figure->color.y));
		else if (i == 2)
			str = ft_strjoinfree(str, ft_itoa((int)figure->color.z));
		dst = (SDL_Rect) {.y = *y, .x = 50};
		message = TTF_RenderText_Solid(sdl->ui.par, str, sdl->ui.grey);
		TTF_SizeText(sdl->ui.par, str, &dst.w, &dst.h);
		SDL_BlitSurface(message, NULL, sdl->ui.message, &dst);
		ft_strdel(&str);
		sdl->ui.btn_pos_y[i + 12] = *y + 5;
		*y = *y + dst.h;
		SDL_FreeSurface(message);
	}
}

void			print_fig_dir(t_sdl *sdl, t_figure *figure, int *y, char *patt)
{
	SDL_Surface	*message;
	SDL_Rect	dst;
	char		*str;
	int			i;

	i = -1;
	while (++i < 3)
	{
		str = ft_strnew(100);
		str = ft_strcpy(str, &patt[i + i]);
		if (i == 0)
			str = ft_strjoinfree(str, ft_ftoa(figure->d.x));
		else if (i == 1)
			str = ft_strjoinfree(str, ft_ftoa(figure->d.y));
		else if (i == 2)
			str = ft_strjoinfree(str, ft_ftoa(figure->d.z));
		dst = (SDL_Rect) {.y = *y, .x = 50};
		message = TTF_RenderText_Solid(sdl->ui.par, str, sdl->ui.grey);
		TTF_SizeText(sdl->ui.par, str, &dst.w, &dst.h);
		SDL_BlitSurface(message, NULL, sdl->ui.message, &dst);
		ft_strdel(&str);
		sdl->ui.btn_pos_y[i + 3] = *y + 5;
		*y = *y + dst.h;
		SDL_FreeSurface(message);
	}
}

void			print_fig_min(t_sdl *sdl, t_figure *figure, int *y, char *patt)
{
	SDL_Surface	*message;
	SDL_Rect	dst;
	char		*str;
	int			i;

	i = -1;
	while (++i < 3)
	{
		str = ft_strnew(100);
		str = ft_strcpy(str, &patt[i + i]);
		if (i == 0)
			str = ft_strjoinfree(str, ft_ftoa(figure->min.x));
		else if (i == 1)
			str = ft_strjoinfree(str, ft_ftoa(figure->min.y));
		else if (i == 2)
			str = ft_strjoinfree(str, ft_ftoa(figure->min.z));
		dst = (SDL_Rect) {.y = *y, .x = 50};
		message = TTF_RenderText_Solid(sdl->ui.par, str, sdl->ui.grey);
		TTF_SizeText(sdl->ui.par, str, &dst.w, &dst.h);
		SDL_BlitSurface(message, NULL, sdl->ui.message, &dst);
		ft_strdel(&str);
		sdl->ui.btn_pos_y[i + 6] = *y + 5;
		*y = *y + dst.h;
		SDL_FreeSurface(message);
	}
}

void			print_fig_max(t_sdl *sdl, t_figure *figure, int *y, char *patt)
{
	SDL_Surface	*message;
	SDL_Rect	dst;
	char		*str;
	int			i;

	i = -1;
	while (++i < 3)
	{
		str = ft_strnew(100);
		str = ft_strcpy(str, &patt[i + i]);
		if (i == 0)
			str = ft_strjoinfree(str, ft_ftoa(figure->max.x));
		else if (i == 1)
			str = ft_strjoinfree(str, ft_ftoa(figure->max.y));
		else if (i == 2)
			str = ft_strjoinfree(str, ft_ftoa(figure->max.z));
		dst = (SDL_Rect) {.y = *y, .x = 50};
		message = TTF_RenderText_Solid(sdl->ui.par, str, sdl->ui.grey);
		TTF_SizeText(sdl->ui.par, str, &dst.w, &dst.h);
		SDL_BlitSurface(message, NULL, sdl->ui.message, &dst);
		ft_strdel(&str);
		sdl->ui.btn_pos_y[i + 9] = *y + 5;
		*y = *y + dst.h;
		SDL_FreeSurface(message);
	}
}

void			print_fig_pos(t_sdl *sdl, t_figure *figure, int *y, char *patt)
{
	SDL_Surface	*message;
	SDL_Rect	dst;
	char		*str;
	int			i;

	i = -1;
	while (++i < 3)
	{
		str = ft_strnew(100);
		str = ft_strcpy(str, &patt[i + i]);
		if (i == 0)
			str = ft_strjoinfree(str, ft_ftoa(figure->p.x));
		else if (i == 1)
			str = ft_strjoinfree(str, ft_ftoa(figure->p.y));
		else if (i == 2)
			str = ft_strjoinfree(str, ft_ftoa(figure->p.z));
		dst = (SDL_Rect) {.y = *y, .x = 50};
		message = TTF_RenderText_Solid(sdl->ui.par, str, sdl->ui.grey);
		TTF_SizeText(sdl->ui.par, str, &dst.w, &dst.h);
		SDL_BlitSurface(message, NULL, sdl->ui.message, &dst);
		ft_strdel(&str);
		sdl->ui.btn_pos_y[i] = *y + 5;
		*y = *y + dst.h;
		SDL_FreeSurface(message);
	}
}
