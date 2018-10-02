/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sidebar1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 21:16:51 by mstorcha          #+#    #+#             */
/*   Updated: 2018/07/31 21:17:10 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			print_fig_float(t_sdl *sdl, float nb, int *y, int i)
{
	SDL_Surface	*message;
	SDL_Rect	dst;
	char		*str;

	str = ft_strnew(100);
	str = ft_strjoinfree(str, ft_ftoa(nb));
	dst = (SDL_Rect) {.y = *y, .x = 50};
	message = TTF_RenderText_Solid(sdl->ui.par, str, sdl->ui.grey);
	TTF_SizeText(sdl->ui.par, str, &dst.w, &dst.h);
	SDL_BlitSurface(message, NULL, sdl->ui.message, &dst);
	ft_strdel(&str);
	sdl->ui.btn_pos_y[i] = *y + 5;
	*y = *y + dst.h;
	SDL_FreeSurface(message);
}
