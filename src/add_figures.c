/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_figures.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 15:29:39 by mstorcha          #+#    #+#             */
/*   Updated: 2018/07/16 15:29:41 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_figure	return_fig(char type, t_figure cam)
{
	if (type == 's')
		return (new_sphere(cam, 0.3f));
	else if (type == 'p')
		return (new_plane(cam));
	else if (type == 'c')
		return (new_cone(cam));
	else if (type == 'y')
		return (new_cylinder(cam));
	else if (type == 'd')
		return (new_disk(cam));
	else if (type == 'k')
		return (new_cube(cam));
	else if (type == 'e')
		return (new_ellipsoid(cam));
	else if (type == 'a')
		return (new_paraboloid(cam));
	else if (type == 't')
		return (new_twosheet_hyperboloid(cam));
	else
		return (new_hyperboloid(cam));
}

void			add_figure(t_main *mlx, t_figure **figures,
						t_figure cam, char type)
{
	t_figure	*new;
	int			i;
	int			index;
	int			o_num;

	o_num = mlx->scene->o_num;
	if (!(new = (t_figure *)malloc(sizeof(t_figure) * (o_num + 1))))
		exit_message("failed");
	i = -1;
	mlx->sdl->ui.show_info = 0;
	while (++i < o_num)
		new[i] = (*figures)[i];
	index = (*figures)[i - 1].index;
	new[i] = return_fig(type, cam);
	new[i].index = index + 1;
	new[i].matirial = 0;
	new[i].text = 0;
	new[i].scale = 1;
	if (o_num >= 1)
		free(*figures);
	*figures = new;
	mlx->scene->o_num = i + 1;
}
