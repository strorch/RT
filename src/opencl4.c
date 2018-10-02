/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 21:30:07 by mstorcha          #+#    #+#             */
/*   Updated: 2018/07/31 21:30:09 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			exit_message(const char *str)
{
	ft_putendl(str);
	exit(1);
}

void			cl_args_1_1(t_opencl *cl, t_main *mlx)
{
	int ret;

	if ((ret = clSetKernelArg(cl->kernel, 0,
		sizeof(cl_mem), &cl->memobj_data)))
		exit_message("failed to set arg1");
	if ((ret = clSetKernelArg(cl->kernel, 1,
		sizeof(cl_mem), &cl->memobj_figures)))
		exit_message("failed to set arg2 ");
	if ((ret = clSetKernelArg(cl->kernel, 2,
		sizeof(cl_mem), &cl->memobj_light)))
		exit_message("failed to set arg3");
	if ((ret = clSetKernelArg(cl->kernel, 3,
		sizeof(t_figure), &mlx->scene->cam)))
		exit_message("failed to set arg4");
	if ((ret = clSetKernelArg(cl->kernel, 4,
		sizeof(int), &mlx->scene->l_num)))
		exit_message("failed to set arg5");
}

void			cl_args_1_2(t_opencl *cl, t_main *mlx)
{
	int ret;

	if ((ret = clSetKernelArg(cl->kernel, 5,
		sizeof(int), &mlx->scene->o_num)))
		exit_message("failed to set arg6");
	if ((ret = clSetKernelArg(cl->kernel, 6,
		sizeof(cl_mem), &cl->memobj_textures)))
		exit_message("failed to set arg7");
	if ((ret = clSetKernelArg(cl->kernel, 7,
		sizeof(cl_mem), &cl->memobj_textures_sz)))
		exit_message("failed to set arg8");
	if ((ret = clSetKernelArg(cl->kernel, 8,
		sizeof(int), &mlx->scene->effect)))
		exit_message("failed to set arg8");
}
