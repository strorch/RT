/* **************************************************************************** */
/*                                                                              */
/*                                                         :::      ::::::::    */
/*    1.h.cl                                             :+:      :+:    :+:    */
/*                                                     +:+ +:+         +:+      */
/*    By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+         */
/*                                                 +#+#+#+#+#+   +#+            */
/*    Created: 2018/06/19 13:41:34 by mstorcha          #+#    #+#              */
/*    Updated: 2018/06/19 13:41:45 by mstorcha         ###   ########.fr        */
/*                                                                              */
/* **************************************************************************** */

#ifndef RENDERING_H_CL

# define RENDERING_H_CL
# define HEIGHT 1200
# define WIDTH 1200

/*
** 1 - cam
** 2 - light
** 3 - sphere
** 4 - cone
** 5 - cylinder
** 6 - plane
*/

# define PLANE 6
# define CYLINDER 5
# define CONE 4
# define SPHERE 3
# define DISK 7
# define CUBE 8
# define ELLIPSOID 9
# define PARABOLOID 10
# define TWOSHEET_HYPERBOLOID 11
# define HYPERBOLOID 12

# define NUM_REFL 4

typedef struct	s_figure
{
	int			text;
	int			matirial;
	int			index;
	int			type;
	float		radius;
	float		angle;
	float		rfl;
	float		cap;
	float3		color;
	float3		p;
	float3		d;
	float3		min;
	float3		max;
	float		size;
	float		scale;
}				t_figure;

typedef struct	s_closest
{
	float		closest;
	t_figure	figure;
	int			index;
}				t_closest;

/*
**	EFFECTS
*/


float3		e_grades_gray(float3 a);
float3		e_sepia(float3 a);
float3		e_negative(float3 a);
float3		e_black_white(float3 a);

float3			return_point_color(int c);

/*
**
*/
float noise(float x, float y, float z);

void 			fresnel(float3 R, float3 N, float n1, float n2, float *kr);
float3			RefractRay(float3 R, float3 N, float n1, float n2);
float3			ReflectRay(float3 R, float3 N);


float3			rotate_ort(float3 point, float3 rot);
float3			return_f_color(int c);
int				return_int_color(float3 c);
float			sum_color(float f, float s);
void			swap(float f, float s);

float3			get_obj_color(float3 NL, float3 P, t_figure obj,
							__global int3 *t_i, __global int *textures);
float3			calc_uv(float3 N, float3 P, t_figure obj);

float2 			IntersectRaySphere(float3 O, float3 D, t_figure sphere);
float2 			IntersectRayCylinder(float3 O, float3 D, t_figure cyl);
float2 			IntersectRayCone(float3 O, float3 D, t_figure cone);
float2 			IntersectRayPlane(float3 O, float3 D, t_figure plane);

float3   		compute_normal(t_figure figure, float3 D, float3 P);
float			compute_light(float3 P, float3 N, float3 V, float s, __global t_figure *figures,
					__global t_figure *light, int o_n, int l_n);
t_closest		closest_fig(float3 O, float3 D,
					float min, float max, __global t_figure *figures, int o_n);
float3 TraceRay(float3 O, float3 D, float min, float max, __global t_figure *figures,
					__global t_figure *light, int o_n, int l_n, __global int *textures, __global int3 *textures_sz);
__kernel void rendering(__global int * data, __global t_figure *figures,
					__global t_figure *light, t_figure cam,
					int l_n, int o_n, __global int *textures, __global int3 *textures_sz, int effects);

#endif
