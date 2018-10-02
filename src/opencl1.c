/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 21:41:38 by mstorcha          #+#    #+#             */
/*   Updated: 2018/06/19 21:41:40 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#define TEXTURE_SZ 1200

static void		free_mem(t_opencl *cl, int index)
{
	clReleaseKernel(cl->kernel);
	clReleaseMemObject(cl->memobj_figures);
	if (index == 0)
	{
		clReleaseMemObject(cl->memobj_data);
		clReleaseMemObject(cl->memobj_light);
	}
	else if (index == 2)
	{
		clReleaseMemObject(cl->memobj_data);
	}
}

void			cl_init(t_main *mlx)
{
	t_opencl *cl;

	cl = malloc(sizeof(t_opencl));
	mlx->sdl = (t_sdl *)malloc(sizeof(t_sdl));
	cl_start(cl);
	mlx->cl = cl;
}

void			rendering(t_main *mlx)
{
	size_t		global_work_size[3];
	int			ret;
	SDL_Rect	dst_r;

	global_work_size[0] = 1200;
	global_work_size[1] = 1200;
	global_work_size[2] = 0;
	cl_kernel_buffer_1(mlx->cl, mlx, MEM_LENGTH);
	cl_args_1_1(mlx->cl, mlx);
	cl_args_1_2(mlx->cl, mlx);
	if ((ret = clEnqueueNDRangeKernel(mlx->cl->command_queue,
mlx->cl->kernel, 2, NULL, global_work_size, NULL, 0, NULL, NULL)))
		exit_message("failed to execute kernel");
	if ((ret = clEnqueueReadBuffer(mlx->cl->command_queue,
				mlx->cl->memobj_data, CL_TRUE, 0, sizeof(int) * MEM_LENGTH,
				mlx->sdl->sur->pixels, 0, NULL, NULL)))
		exit_message("failed to get buf data");
	mlx->sdl->text =
	SDL_CreateTextureFromSurface(mlx->sdl->rend, mlx->sdl->sur);
	dst_r = (SDL_Rect){.x = SIDE_W, .y = MEN_H, .w = WIDTH, .h = HEIGHT};
	SDL_RenderCopy(mlx->sdl->rend, mlx->sdl->text, NULL, &dst_r);
	user_interface(mlx->sdl, mlx->scene);
	SDL_RenderPresent(mlx->sdl->rend);
	SDL_DestroyTexture(mlx->sdl->text);
	free_mem(mlx->cl, 0);
}

void			get_disruption(t_texture *text,
					t_opencl *cl, cl_float3 color, int type)
{
	size_t		global_work_size[3];
	int			r;
	int			*res;

	if (!(res = (int *)malloc(TEXTURE_SZ * TEXTURE_SZ * sizeof(int))))
		exit_message("mem alloc err");
	global_work_size[0] = TEXTURE_SZ;
	global_work_size[1] = TEXTURE_SZ;
	global_work_size[2] = 0;
	cl_kernel_buffer_3(cl);
	cl_args_3(cl, color, type);
	if ((r = clEnqueueNDRangeKernel(cl->command_queue,
	cl->kernel, 2, NULL, global_work_size, NULL, 0, NULL, NULL)))
		exit_message(ft_strjoin("failed to execute kernel ", ft_itoa(r)));
	if ((r = clEnqueueReadBuffer(cl->command_queue, cl->memobj_data,
CL_TRUE, 0, sizeof(int) * TEXTURE_SZ * TEXTURE_SZ, res, 0, NULL, NULL)))
		exit_message(ft_strjoin("failed to get buf data ", ft_itoa(r)));
	free_mem(cl, 2);
	text->pix = res;
	text->h = TEXTURE_SZ;
	text->w = TEXTURE_SZ;
}

int				find_figure(t_main *mlx, int i, int j)
{
	size_t		global_work_size[3];
	int			ret;
	int			res;

	global_work_size[0] = 1;
	global_work_size[1] = 1;
	global_work_size[2] = 0;
	cl_kernel_buffer_2(mlx->cl, mlx);
	cl_args_2(mlx->cl, mlx, i, j);
	if ((ret = clEnqueueNDRangeKernel(mlx->cl->command_queue,
				mlx->cl->kernel, 2, NULL,
				global_work_size, NULL, 0, NULL, NULL)))
		exit_message(ft_strjoin("failed to execute kernel ", ft_itoa(ret)));
	if ((ret = clEnqueueReadBuffer(mlx->cl->command_queue,
				mlx->cl->memobj_data, CL_TRUE, 0, sizeof(int),
				&res, 0, NULL, NULL)))
		exit_message("failed to get buf data");
	free_mem(mlx->cl, 1);
	return (res);
}
