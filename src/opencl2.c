/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 18:17:34 by mstorcha          #+#    #+#             */
/*   Updated: 2018/06/23 18:17:36 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		debugger(int r, cl_program program, cl_device_id device_id)
{
	size_t	log_size;
	char	*log;

	if (r == CL_BUILD_PROGRAM_FAILURE)
	{
		clGetProgramBuildInfo(program,
			device_id, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
		log = (char *)malloc(log_size);
		clGetProgramBuildInfo(program, device_id,
					CL_PROGRAM_BUILD_LOG, log_size, log, NULL);
		ft_putendl(log);
		free(log);
		exit(1);
	}
}

static void		read_kernel(const char *filename,
						char **source_str, size_t *source_size)
{
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		exit_message("Failed to read kernel");
	*source_str = (char *)malloc(MAX_SOURCE_SIZE);
	*source_size = read(fd, *source_str, MAX_SOURCE_SIZE);
}

void			cl_start(t_opencl *cl)
{
	int r;

	if ((r = clGetPlatformIDs(1, &(cl->platform_id), &(cl->ret_num_plat))))
		exit_message("couldn*t load platform");
	if ((r = clGetDeviceIDs(cl->platform_id,
		CL_DEVICE_TYPE_CPU, 1, &(cl->device_id), &(cl->ret_num_devices))))
		exit_message("couldn*t get device id");
	cl->context = clCreateContext(NULL, 1, &(cl->device_id), NULL, NULL, &r);
	if (r)
		exit_message("couldn*t create context");
	cl->command_queue = clCreateCommandQueue(cl->context, cl->device_id, 0, &r);
	if (r)
		exit_message("couldn*t create command queue");
	read_kernel("./opencl/render.cl", &(cl->source_str), &(cl->source_size));
	cl->program = clCreateProgramWithSource(cl->context, 1,
	(const char **)&(cl->source_str), (const size_t *)&(cl->source_size), &r);
	if (r)
		exit_message("couldn*t create binary");
	free(cl->source_str);
	r = clBuildProgram(cl->program, 1, &(cl->device_id),
		"-I ./includes/", NULL, NULL);
	debugger(r, cl->program, cl->device_id);
}

int				count_arr(t_scene sc)
{
	int i;
	int sum;

	i = -1;
	sum = 0;
	while (++i < sc.textures_num)
	{
		sum += sc.textures_info[i].x * sc.textures_info[i].y;
	}
	if (!sum)
		return (1);
	else
		return (sum);
}

void			cl_kernel_buffer_1(t_opencl *cl, t_main *mlx, int memlenth)
{
	int			ret;

	cl->kernel = clCreateKernel(cl->program, "rendering", &ret);
	if (ret)
		exit_message("failed to create kernel");
	cl->memobj_data = clCreateBuffer(cl->context, CL_MEM_READ_WRITE,
				memlenth * sizeof(int), NULL, &ret);
	if (ret)
		exit_message("failed to create buf1");
	cl->memobj_figures = clCreateBuffer(cl->context, CL_MEM_USE_HOST_PTR,
		mlx->scene->o_num * sizeof(t_figure), mlx->scene->objects, &ret);
	if (ret)
		exit_message("failed to create buf2");
	cl->memobj_light = clCreateBuffer(cl->context, CL_MEM_USE_HOST_PTR,
		mlx->scene->l_num * sizeof(t_figure), mlx->scene->lights, &ret);
	if (ret)
		exit_message("failed to create buf3");
	cl->memobj_textures = clCreateBuffer(cl->context, CL_MEM_USE_HOST_PTR,
		count_arr(*mlx->scene) * sizeof(int), mlx->scene->textures, &ret);
	if (ret)
		exit_message("failed to create buf4");
	cl->memobj_textures_sz = clCreateBuffer(cl->context, CL_MEM_USE_HOST_PTR,
mlx->scene->textures_num * sizeof(cl_int3), mlx->scene->textures_info, &ret);
	if (ret)
		exit_message("failed to create buf5");
}
