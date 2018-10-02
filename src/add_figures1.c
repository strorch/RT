/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_figures1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 11:58:16 by mstorcha          #+#    #+#             */
/*   Updated: 2018/08/01 11:58:18 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_figure	new_sphere(t_figure cam, float radius)
{
	t_figure f;

	f.type = SPHERE;
	f.radius = 0.5f;
	f.radius = radius;
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

t_figure	new_cylinder(t_figure cam)
{
	t_figure f;

	f.type = CYLINDER;
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

t_figure	new_cone(t_figure cam)
{
	t_figure f;

	f.type = CONE;
	f.angle = 10;
	f.rfl = 0.f;
	f.radius = 0.f;
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

t_figure	new_plane(t_figure cam)
{
	t_figure f;

	f.type = PLANE;
	f.rfl = 0.f;
	f.radius = 0.f;
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

t_figure	new_hyperboloid(t_figure cam)
{
	t_figure f;

	f.type = HYPERBOLOID;
	f.radius = 0.5f;
	f.rfl = 0.f;
	f.color = (cl_float3){.x=0.0f, .y=255.0f, .z=0.0f };
	f.p = (cl_float3){.x=cam.p.x +
		rotate_ort((cl_float3){.x=0, .y=0, .z=5}, cam.d).x,
						.y=cam.p.y +
		rotate_ort((cl_float3){.x=0, .y=0, .z=5}, cam.d).y,
						.z=cam.p.z +
		rotate_ort((cl_float3){.x=0, .y=0, .z=5}, cam.d).z };
	f.min = (cl_float3){.x=0, .y=0, .z=0};
	f.max = (cl_float3){.x=0, .y=0, .z=0};
	f.d = (cl_float3){.x=0, .y=0, .z=0};
	return (f);
}
