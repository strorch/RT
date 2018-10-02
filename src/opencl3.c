/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 21:30:01 by mstorcha          #+#    #+#             */
/*   Updated: 2018/07/31 21:30:03 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				*random_array(int size)
{
	int *ret;
	int i;

	ret = malloc(sizeof(int) * size);
	i = -1;
	while (++i < size)
		ret[i] = rand() % 255;
	return (ret);
}

void			cl_kernel_buffer_3(t_opencl *cl)
{
	int	ret;
	int	*rand;

	rand = random_array(512);
	cl->kernel = clCreateKernel(cl->program, "create_disruption", &ret);
	if (ret)
		exit_message("failed to create kernel");
	cl->memobj_data = clCreateBuffer(cl->context, CL_MEM_READ_WRITE,
				sizeof(int) * MEM_LENGTH, NULL, &ret);
	if (ret)
		exit_message("failed to create buf1");
	cl->memobj_figures = clCreateBuffer(cl->context, CL_MEM_USE_HOST_PTR,
				512 * sizeof(int), rand, &ret);
	if (ret)
		exit_message("failed to create buf2");
	free(rand);
}

void			cl_args_3(t_opencl *cl, cl_float3 color, int type)
{
	int ret;

	if ((ret = clSetKernelArg(cl->kernel, 0,
		sizeof(cl_mem), &cl->memobj_data)))
		exit_message("failed to set arg1");
	if ((ret = clSetKernelArg(cl->kernel, 1,
		sizeof(cl_float3), &color)))
		exit_message("failed to set arg2 ");
	if ((ret = clSetKernelArg(cl->kernel, 2,
		sizeof(int), &type)))
		exit_message("failed to set arg3");
	if ((ret = clSetKernelArg(cl->kernel, 3,
		sizeof(cl_mem), &cl->memobj_figures)))
		exit_message("failed to set arg3");
}

void			cl_kernel_buffer_2(t_opencl *cl, t_main *mlx)
{
	int	ret;

	cl->kernel = clCreateKernel(cl->program, "find_figure", &ret);
	if (ret)
		exit_message("failed to create kernel");
	cl->memobj_data = clCreateBuffer(cl->context, CL_MEM_READ_WRITE,
				sizeof(int), NULL, &ret);
	if (ret)
		exit_message("failed to create buf1");
	cl->memobj_figures = clCreateBuffer(cl->context,
		CL_MEM_USE_HOST_PTR,
		mlx->scene->o_num * sizeof(t_figure), mlx->scene->objects, &ret);
	if (ret)
		exit_message("failed to create buf2");
}

void			cl_args_2(t_opencl *cl, t_main *mlx, int i, int j)
{
	int ret;

	if ((ret = clSetKernelArg(cl->kernel, 0,
		sizeof(cl_mem), &cl->memobj_data)))
		exit_message("failed to set arg1");
	if ((ret = clSetKernelArg(cl->kernel, 1,
		sizeof(cl_mem), &cl->memobj_figures)))
		exit_message("failed to set arg2 ");
	if ((ret = clSetKernelArg(cl->kernel, 2,
		sizeof(t_figure), &mlx->scene->cam)))
		exit_message("failed to set arg3");
	if ((ret = clSetKernelArg(cl->kernel, 3,
		sizeof(int), &i)))
		exit_message("failed to set arg4");
	if ((ret = clSetKernelArg(cl->kernel, 4,
		sizeof(int), &j)))
		exit_message("failed to set arg5");
	if ((ret = clSetKernelArg(cl->kernel, 5,
		sizeof(int), &mlx->scene->o_num)))
		exit_message("failed to set arg5");
}
