/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_figures2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 11:58:23 by mstorcha          #+#    #+#             */
/*   Updated: 2018/08/01 11:58:26 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_figure	new_twosheet_hyperboloid(t_figure cam)
{
	t_figure f;

	f.type = TWOSHEET_HYPERBOLOID;
	f.radius = 0.5f;
	f.rfl = 0.f;
	f.color = (cl_float3){.x=0.0f, .y=255.0f, .z=0.0f };
	f.p = (cl_float3){.x=cam.p.x +
		rotate_ort((cl_float3){.x=0, .y=0, .z=5}, cam.d).x,
						.y=cam.p.y +
		rotate_ort((cl_float3){.x=0, .y=0, .z=5}, cam.d).y,
						.z=cam.p.z +
		rotate_ort((cl_float3){.x=0, .y=0, .z=5}, cam.d).z };
	f.d = (cl_float3){.x=0, .y=0, .z=0};
	f.min = (cl_float3){.x=0, .y=0, .z=0};
	f.max = (cl_float3){.x=0, .y=0, .z=0};
	return (f);
}

t_figure	new_paraboloid(t_figure cam)
{
	t_figure f;

	f.type = PARABOLOID;
	f.radius = 0.1f;
	f.rfl = 0.f;
	f.cap = 5.f;
	f.color = (cl_float3){.x=0.0f, .y=255.0f, .z=0.0f };
	f.p = (cl_float3){.x=cam.p.x +
		rotate_ort((cl_float3){.x=0, .y=0, .z=20}, cam.d).x,
						.y=cam.p.y +
		rotate_ort((cl_float3){.x=0, .y=0, .z=20}, cam.d).y,
						.z=cam.p.z +
		rotate_ort((cl_float3){.x=0, .y=0, .z=20}, cam.d).z };
	f.d = (cl_float3){.x=
		rotate_ort((cl_float3){.x=0, .y=1, .z=0}, cam.d).x,
						.y=
		rotate_ort((cl_float3){.x=0, .y=1, .z=0}, cam.d).y,
						.z=
		rotate_ort((cl_float3){.x=0, .y=1, .z=0}, cam.d).z };
	f.min = (cl_float3){.x=0, .y=0, .z=0};
	f.max = (cl_float3){.x=0, .y=0, .z=0};
	return (f);
}

t_figure	new_ellipsoid(t_figure cam)
{
	t_figure f;

	f.type = ELLIPSOID;
	f.radius = 0.5f;
	f.rfl = 0.f;
	f.color = (cl_float3){.x=0.0f, .y=255.0f, .z=0.0f };
	f.p = (cl_float3){.x=cam.p.x +
		rotate_ort((cl_float3){.x=0, .y=0, .z=5}, cam.d).x,
						.y=cam.p.y +
		rotate_ort((cl_float3){.x=0, .y=0, .z=5}, cam.d).y,
						.z=cam.p.z +
		rotate_ort((cl_float3){.x=0, .y=0, .z=5}, cam.d).z };
	f.d = (cl_float3){.x=cam.p.x +
		rotate_ort((cl_float3){.x=0, .y=1, .z=5}, cam.d).x,
						.y=cam.p.y +
		rotate_ort((cl_float3){.x=0, .y=1, .z=5}, cam.d).y,
						.z=cam.p.z +
		rotate_ort((cl_float3){.x=0, .y=1, .z=5}, cam.d).z };
	f.min = (cl_float3){.x=0, .y=0, .z=0};
	f.max = (cl_float3){.x=0, .y=0, .z=0};
	return (f);
}

t_figure	new_disk(t_figure cam)
{
	t_figure f;

	f.type = DISK;
	f.radius = 0.5f;
	f.rfl = 0.f;
	f.color = (cl_float3){.x=0.0f, .y=255.0f, .z=0.0f };
	f.p = (cl_float3){.x=cam.p.x +
		rotate_ort((cl_float3){.x=0, .y=0, .z=5}, cam.d).x,
						.y=cam.p.y +
		rotate_ort((cl_float3){.x=0, .y=0, .z=5}, cam.d).y,
						.z=cam.p.z +
		rotate_ort((cl_float3){.x=0, .y=0, .z=5}, cam.d).z };
	f.d = (cl_float3){.x=cam.p.x +
		rotate_ort((cl_float3){.x=0, .y=1, .z=0}, cam.d).x,
						.y=cam.p.y +
		rotate_ort((cl_float3){.x=0, .y=1, .z=0}, cam.d).y,
						.z=cam.p.z +
		rotate_ort((cl_float3){.x=0, .y=1, .z=0}, cam.d).z };
	f.min = (cl_float3){.x=0, .y=0, .z=0};
	f.max = (cl_float3){.x=0, .y=0, .z=0};
	return (f);
}

t_figure	new_cube(t_figure cam)
{
	t_figure f;

	f.type = CUBE;
	f.rfl = 0.f;
	f.color = (cl_float3){.x=0.0f, .y=255.0f, .z=0.0f };
	f.p = (cl_float3){.x=0, .y=0, .z=0};
	f.d = (cl_float3){.x=0, .y=0, .z=0};
	f.min = (cl_float3){.x=cam.p.x +
		rotate_ort((cl_float3){.x=-1, .y=-1, .z=5}, cam.d).x,
						.y=cam.p.y +
		rotate_ort((cl_float3){.x=-1, .y=-1, .z=5}, cam.d).y,
						.z=cam.p.z +
		rotate_ort((cl_float3){.x=-1, .y=-1, .z=5}, cam.d).z };
	f.max = (cl_float3){.x=cam.p.x +
		rotate_ort((cl_float3){.x=1, .y=0, .z=7}, cam.d).x,
						.y=cam.p.y +
		rotate_ort((cl_float3){.x=1, .y=0, .z=7}, cam.d).y,
						.z=cam.p.z +
		rotate_ort((cl_float3){.x=1, .y=0, .z=7}, cam.d).z};
	return (f);
}
