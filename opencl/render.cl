/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1.cl                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 14:28:30 by mstorcha          #+#    #+#             */
/*   Updated: 2018/06/12 14:28:33 by mstorcha         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "rendering.h.cl"
#include "./opencl/intersections.cl"
#include "./opencl/effects.cl"

void	swap(float f, float s)
{
	float tmp = f;
	f = s;
	s = tmp;
}

int		return_int_color(float3 c)
{
	return ((int)c.x * 0x10000 + (int)c.y * 0x100 + (int)c.z);
}

float3		return_point_color(int c)
{
	float3 p;
	p.x = (c >> 16) & 255; // 255
	p.y = (c >> 8) & 255; // 122
	p.z = c & 255; // 15
	return p;
}

float	sum_color(float f, float s)
{
	float r;

	r = clamp(f + s, 0.0f, 255.0f);
	r = clamp(f + s, 0.0f, 255.0f);
	r = clamp(f + s, 0.0f, 255.0f);

	return r;
}

float3		rotate_ort(float3 point, float3 rot)
{
	float3 od;
	float3 dv;
	float3 tr;
	float3 rot_rad;

	rot_rad.x = rot.x * M_PI / 180.0f;
	rot_rad.y = rot.y * M_PI / 180.0f;
	rot_rad.z = rot.z * M_PI / 180.0f;
	od.x = point.x;
	od.y = point.y * cos(rot_rad.x) + point.z * sin(rot_rad.x);
	od.z = point.z * cos(rot_rad.x) - point.y * sin(rot_rad.x);
	dv.x = od.x * cos(rot_rad.y) - od.z * sin(rot_rad.y);
	dv.y = od.y;
	dv.z = od.z * cos(rot_rad.y) + od.x * sin(rot_rad.y);
	tr.x = dv.x * cos(rot_rad.z) + dv.y * sin(rot_rad.z);
	tr.y = dv.y * cos(rot_rad.z) - dv.x * sin(rot_rad.z);
	tr.z = dv.z;
	return tr;
}

t_closest		closest_fig(float3 O, float3 D,
			float min, float max, __global t_figure *figures, int o_n)
{
	t_figure ret;
	float closest = INFINITY;
	float2 tmp;
	for (int i = 0; i < o_n; i++)
	{
		if (figures[i].type == CYLINDER)
			tmp = IntersectRayCylinder(O, D, figures[i]);
		else if (figures[i].type == CONE)
			tmp = IntersectRayCone(O, D, figures[i]);
		else if (figures[i].type == PLANE)
			tmp = IntersectRayPlane(O, D, figures[i]);
		else if (figures[i].type == SPHERE)
			tmp = IntersectRaySphere(O, D, figures[i]);
		else if (figures[i].type == DISK)
			tmp = IntersectRayDisk(O, D, figures[i]);
		else if (figures[i].type == CUBE)
			tmp = IntersectRayCube(O, D, figures[i]);
		else if (figures[i].type == HYPERBOLOID)
			tmp = IntersectRayHyperboloid(O, D, figures[i]);
		else if (figures[i].type == TWOSHEET_HYPERBOLOID)
			tmp = IntersectRayTwoSheetHyperboloid(O, D, figures[i]);
		else if (figures[i].type == PARABOLOID)
			tmp = IntersectRayParaboloid(O, D, figures[i]);
		else if (figures[i].type == ELLIPSOID)
			tmp = IntersectRayEllipsoid(O, D, figures[i]);

		if (tmp.x >= min && tmp.x <= max && tmp.x < closest)
		{
			closest = tmp.x;
			ret = figures[i];
		}
		if (tmp.y >= min && tmp.y <= max && tmp.y < closest)
		{
			closest = tmp.y;
			ret = figures[i];
		}
	}
	return (t_closest){closest, ret};
}

float   compute_light(float3 P, float3 N, float3 V, float s, __global t_figure *figures,
                    __global t_figure *light, int o_n, int l_n)
{
	float koef = 0;
	int i = -1;
	while (++i < l_n)
	{
		t_figure l = light[i];
		float3 Lp = {l.p.x, l.p.y, l.p.z};
		if (l.type == 1)
		{
			koef += l.angle;
		}
		else if (l.type == 2)
		{
			float3 L = Lp - P;

			//shadow
			t_closest clos = closest_fig(P, L, 0.001, 0.99, figures, o_n);
			float closest = INFINITY;
			closest = clos.closest;
			if (closest != INFINITY)
				continue;

			//difuse
			float n_dot_l = N.x * L.x + N.y * L.y + N.z * L.z;
			if (n_dot_l > 0)
				koef += l.angle * n_dot_l / (fast_length(N) * fast_length(L));

			//zerk
			if (s != -1)
			{
				float3 R = N * 2 * n_dot_l - L;
				float r_dot_v = R.x * V.x + R.y * V.y + R.z * V.z;
				if (r_dot_v > 0)
					koef += l.angle*pow(r_dot_v / (fast_length(R) * fast_length(V)), s);
			}
		}
		else if (l.type == 3)
		{
			float3 L = Lp;
			
			//shadow
			t_closest clos = closest_fig(P, L, 0.001, INFINITY, figures, o_n);
			float closest = INFINITY;
			closest = clos.closest;
			if (closest != INFINITY)
				continue;
			
			//diffuse	
			float n_dot_l = N.x * L.x + N.y * L.y + N.z * L.z;
			if (n_dot_l > 0)
				koef += l.angle * n_dot_l / (fast_length(N) * fast_length(L));
			
			//zerk
			if (s != -1)
			{
				float3 R = N * 2 * n_dot_l - L;
				float r_dot_v = R.x * V.x + R.y * V.y + R.z * V.z;
				if (r_dot_v > 0)
					koef += l.angle*pow(r_dot_v / (fast_length(R) * fast_length(V)), s);
			}
		}
	}
	return (koef > 1.0) ? 1.0 : koef;
}

float3	ReflectRay(float3 R, float3 N)
{
	return 2.0f * N * dot(R, N) - R;
}

float3	RefractRay(float3 R, float3 N, float n1, float n2)
{
	float n = n1 / n2;
	float cosI = - dot(N, R);
	float sinT2 = n * n * (1.f - cosI * cosI);
	if (sinT2 > 1.f || sinT2 < -1.f)
		return (float3){ 0.f, 0.f, 0.f};
	float cosT = sqrt(1.f - sinT2);
	return n * R + (n * cosI - cosT) * N;
}

void 	fresnel(float3 R, float3 N, float n1, float n2, float *kr) 
{ 
	float ior = n1 / n2;
    float cosi = clamp((float)dot(R, N), -1.f, 1.f); 
    float etai = 1.f, etat = ior; 
    if (cosi > 0.f) 
    	swap(etai, etat);

    float sint = etai / etat * sqrt(max(0.f, 1.f - cosi * cosi));

    if (sint >= 1.f)
        *kr = 1.0f;
    else
    { 
        float cost = sqrtf(max(0.f, 1.f - sint * sint)); 
        cosi = fabsf(cosi); 
        float Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost)); 
        float Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost)); 
        *kr = (Rs * Rs + Rp * Rp) / 2.0f; 
    }
}

float3   compute_normal(t_figure figure, float3 D, float3 P)
{
	float3 N;
	
	if (figure.type == PLANE  || figure.type == DISK)
	{
		float3 d = {figure.d.x, figure.d.y, figure.d.z};
		if (dot(d,D) < 0.0f)
			N = fast_normalize(d);
		else 
		 	N = fast_normalize(-d);
	}
	else if (figure.type == CONE)
	{
		float3 d = {figure.d.x, figure.d.y, figure.d.z};
		float3 p = {figure.p.x, figure.p.y, figure.p.z};
		float3 T = d-p;
		T = T / fast_length(T);
		N = P - p;
		T = T * dot(N, T);
		N = N - T;
		N = fast_normalize(N);
	}
	else if (figure.type == SPHERE)
	{
		float3 p = {figure.p.x, figure.p.y, figure.p.z};
		N = P - p;
		N = N / fast_length(N);
	}
	else if (figure.type == CYLINDER)
	{
		float3 p = {figure.p.x, figure.p.y, figure.p.z};
		float3 d = {figure.d.x, figure.d.y, figure.d.z};
		N = P - p;
		float3 T = d - p;
		T = T / fast_length(T);
		T = T * dot(N, T);
		N = (N - T) / fast_length(N - T);
	}
	else if (figure.type == CUBE)
	{
		float3 center = {(figure.min.x + figure.max.x) / 2., 
			(figure.min.y + figure.max.y) / 2., (figure.min.z + figure.max.z) / 2.};
		float3 center_p = P - center;
		double bias = 1.00001;
		float3 d = {fabs(figure.min.x - figure.max.x) / 2., 
			fabs(figure.min.y - figure.max.y) / 2., fabs(figure.min.z - figure.max.z) / 2.};
		N = (float3){center_p.x / fabs(d.x) * bias, center_p.y / fabs(d.y) * bias,
		 center_p.z / fabs(d.z) * bias};
		N = fast_normalize(N);
		// printf("%f %f %f \n", N.x, N.y, N.z);
	}
	else if (figure.type == HYPERBOLOID || figure.type == TWOSHEET_HYPERBOLOID)
	{
		float3 p = {figure.p.x, figure.p.y, figure.p.z};
		float3 C = P - p;

		N = (float3){2.f * C.x, -2.f * C.y, 2.f * C.z};
		N = N / fast_length(N);
	}
	else if (figure.type == PARABOLOID)
	{
		float3	p = {figure.p.x, figure.p.y, figure.p.z};
		float3	d = {figure.d.x, figure.d.y, figure.d.z};
		d /= fast_length(d);
		float3	C = P - p;
		float	m = dot(C, d);
		float	radius = 1.f;
		N = C - d * (m + radius);
		N = N / fast_length(N);
	}
	else if (figure.type == ELLIPSOID)
	{
		float3	p = {figure.p.x, figure.p.y, figure.p.z};
		float3	d = {figure.d.x, figure.d.y, figure.d.z};
		d /= fast_length(d);

		float	coef = 0.7f;
		float	a = figure.radius;
		float	b = coef * a;

		float3	Cmid = p + d * (sqrtf(a * a - b * b));
		float3	R = P - Cmid;
		N = R - d * (1.f - (b * b / a * a)) * dot(R, d);
		N /= fast_length(N);
	}
	return N;
}
float3			calc_uv(float3 N, float3 P, t_figure obj)
{
	float3	U;
	float3	V;
	float3	ret = 0.0F;

	N = -N;
	ret.x = 0.5F + atan2pi(N.z, N.x) / 2.0f;
	if (obj.type == SPHERE)
		ret.y = 0.5F - asin(N.y) / M_PI;
	else if (obj.type == CYLINDER)
	{
		float H = fast_length(obj.d - obj.p);
		float h = fast_length(P - obj.p);
		ret.y = sqrt(h * h - obj.radius * obj.radius) / H / 2.0f * obj.radius;
	}
	else if (obj.type == CONE)
	{
		float H = fast_length(obj.d - obj.p);
		float h = fast_length(P - obj.d);
		ret.y = -h / H;
	}
	else if (obj.type == PLANE)
	{
		if (N.y >= 0 && N.y <= 0.0003f)
			N.y = N.z;
		else if (N.x >= 0 && N.x <= 0.0003f)
			N.x = N.z;

		U = fast_normalize((float3){N.y, N.x, 0.0F});
		V = cross(N, U);

		ret.x = 1.0F - dot(U, P);
		ret.y = dot(V, P);
	}
	return (ret);
}

float3			get_obj_color(float3 NL, float3 P, t_figure obj,
							__global int3 *t_i, __global int *textures)
{
	int2			textures_info;
	float3			UV;
	int2			tex_pos;
	__global int	*tex;
	float 			scale;
	int	tmp = 0;
	int i = -1;

	scale = obj.scale;

	while (t_i[++i].z != obj.index)
	{
		tmp += t_i[i].x * t_i[i].y;
	}
	tex = textures + tmp;
	
	UV = calc_uv(NL, P, obj);
	UV = rotate_ort(UV, (float3){0,0,0});
	textures_info = (int2) {t_i[i].y, t_i[i].x};

	tex_pos.x = (int)((UV.x) * scale * (float)textures_info.x) % textures_info.x;
	if (tex_pos.x < 0)
		tex_pos.x = textures_info.x + tex_pos.x;
	tex_pos.y = (int)((UV.y) * scale * (float)textures_info.y) % textures_info.y;
	if (tex_pos.y < 0)
		tex_pos.y = textures_info.y + tex_pos.y;
	tex_pos.y = textures_info.y - tex_pos.y - 1;
	return (return_point_color(tex[(tex_pos.y) * (textures_info.x) + (tex_pos.x)]));
}

float3 TraceRay(float3 O, float3 D, float min, float max, __global t_figure *figures,
					__global t_figure *light, int o_n, int l_n, __global int *textures, __global int3 *textures_sz)
{
	float3 hit_color;
	float3 P;
	float3 N;
	float3 local_c = (float3){0.0f,0.0f,0.0f};
	float closest = 0.0f;
	t_figure figure;
	float rfl_mask = 1.0f;
	float rfr_mask = 1.0f;
	int mat = 0;
	float3 NL;

	hit_color = (float3){0.0f, 0.0f, 0.0f};
	for (int i = 0;i < NUM_REFL;)
	{
		float c_l = 0.0f;
		t_closest clos = closest_fig(O, D, min, max, figures, o_n);
		closest = clos.closest;
		if (closest == INFINITY)
			//return (float3) {0, 0, 0};
			break ;
		figure = clos.figure;
		P = O + D * closest;
		N = compute_normal(figure, D, P);
		c_l = compute_light(P, N, -D, 20.0f, figures, light, o_n, l_n);

		if (figure.text)
		{
			//printf("%d\n", figure.index);
			NL = dot(N, D) > 0.0F ? N * (-1.0F) : N;
			local_c = get_obj_color(NL, P, figure, textures_sz, textures);
		}
		else
			local_c = figure.color;
		local_c *= c_l;


		mat = figure.matirial;
		if (mat == 0)
	 	{
			hit_color = hit_color + local_c * (rfl_mask * rfr_mask);
			break ;
	 	}
		else if (mat == 1)
		{
			D = ReflectRay(-D, N);
			O = P;
			hit_color = hit_color + local_c * ((1.0f - figure.rfl) * rfl_mask * rfr_mask);
			rfl_mask = rfl_mask * figure.rfl;
			min = 0.001f;
			i++;
		}/*
		else if (mat == 2)
		{	
			float kr;

			fresnel(D, N, 1.f, 2.f, &kr);
			if (kr < 1.f)
			{
				D = RefractRay(P, N, 1.f, 2.f);
				O = P;
				hit_color += local_c * (1.0f - figure.rfr) * rfr_mask * (1.f - kr);
				rfr_mask *= figure.rfr;
				min = 0.001f;
				i++;
				continue ;
			}
			D = ReflectRay(-D, N);
			O = P;
			hit_color += local_c * ((1.0f - figure.rfl) * rfl_mask * (kr));
			rfl_mask *= figure.rfl;
			min = 0.001f;
		}
		i++;*/
	}
	return hit_color;
}

float fade(float t) { return t * t * t * (t * (t * 6 - 15) + 10); }

float lerp(float t, float a, float b) { return a + t * (b - a); }

float grad(int hash, float x, float y, float z)
{
	int h = hash & 15;                      // CONVERT LO 4 BITS OF HASH CODE
	float u = h<8 ? x : y,                 // INTO 12 GRADIENT DIRECTIONS.
	v = h<4 ? y : h==12||h==14 ? x : z;
	return ((h&1) == 0 ? u : -u) + ((h&2) == 0 ? v : -v);
}

float noise1(float x, float y, float z, __global int * rand)
{
	__global int *p = rand;
	int X = (int)floor(x) & 255,                  // FIND UNIT CUBE THAT
	    Y = (int)floor(y) & 255,                  // CONTAINS POINT.
	    Z = (int)floor(z) & 255;
	x -= floor(x);                                // FIND RELATIVE X,Y,Z
	y -= floor(y);                                // OF POINT IN CUBE.
	z -= floor(z);
	float u = fade(x),                                // COMPUTE FADE CURVES
	       v = fade(y),                                // FOR EACH OF X,Y,Z.
	       w = fade(z);
	int A = p[X  ]+Y, AA = p[A]+Z, AB = p[A+1]+Z,      // HASH COORDINATES OF
	    B = p[X+1]+Y, BA = p[B]+Z, BB = p[B+1]+Z;      // THE 8 CUBE CORNERs
	return lerp(w, lerp(v, lerp(u, grad(p[AA  ], x  , y  , z   ),  // AND ADD
	                               grad(p[BA  ], x-1, y  , z   )), // BLENDED
	                       lerp(u, grad(p[AB  ], x  , y-1, z   ),  // RESULTS
	                               grad(p[BB  ], x-1, y-1, z   ))),// FROM  8
	               lerp(v, lerp(u, grad(p[AA+1], x  , y  , z-1 ),  // CORNERS
	                               grad(p[BA+1], x-1, y  , z-1 )), // OF CUBE
	                       lerp(u, grad(p[AB+1], x  , y-1, z-1 ),
	                               grad(p[BB+1], x-1, y-1, z-1 ))));
}

__kernel void create_disruption(__global int * data, float3 color, int type, __global int * rand)
{
	int j = get_global_id(0);
	int i = get_global_id(1);
	int finalValue = 0;

	if (type == 1)
	{
		float koef = 40.f;
		float dx = (float) j / 1200.0f;
	    float dy = (float) i / 1200.0f;
	    int frequency = 100;
	    float noise = noise1((dx * koef) + koef , (dy * koef) + koef, koef, rand);
	    noise = (noise - 1) / 2;
	    int b = (int)(noise * 0xFF);
	    int g = b * 0x100;
	    int r = b * 0x10000;
	    finalValue = r;
	}
	else if (type == 2)
	{
		if ((i % 100 <= 50 && j % 100 <= 50) || (i % 100 >= 50 && j % 100 >= 50))
			finalValue = return_int_color(color);
		else if ((i % 100 >= 50 && j % 100 <= 50) || (i % 100 <= 50 && j % 100 >= 50))
			finalValue = return_int_color((float3){0,0,0});
	}
    data[j * 1200 + i] = finalValue;
}

__kernel void find_figure(__global int *returnable,
							__global t_figure *figures,
							t_figure cam, int i, int j, int o_n)
{
	float d = 1;
	float3 O = { cam.p.x, cam.p.y, cam.p.z };
	float3 D;
	D.x = ((float)i - (float)WIDTH / 2.0f) * 0.5f / (float)WIDTH;
	D.y = (-(float)j + (float)WIDTH / 2.0f) * 0.5f / (float)HEIGHT;
	D.z = d;
	D = rotate_ort(D, cam.d);

	t_closest clos = closest_fig(O, D, 1.0F, INFINITY, figures, o_n);
	if (clos.closest == INFINITY)
		*returnable = -1;
	else
		*returnable = clos.figure.index;
}

int apply_effects(float3 a, int type)
{
	float3 c;
	
	c = a;
	if (type == 1)
	{
		c = e_grades_gray(a);
	}
	else if (type == 2)
	{
		c = e_sepia(a);
	}
	else if (type == 3)
	{
		c = e_negative(a);
	}
	else if (type == 4)
	{
		c = e_black_white(a);
	}
	else if (type == 5)
	{
		c = e_casting(a);
	}
	else if (type == 6)
	{
		c = e_comic(a);
	}
	return return_int_color(c);
}

__kernel void rendering(__global int * data, __global t_figure *figures,
					__global t_figure *light, t_figure cam,
					int l_n, int o_n, __global int *textures, __global int3 *textures_sz, int effects)
{
	int j = get_global_id(0);
	int i = get_global_id(1);

	float3 O = { cam.p.x, cam.p.y, cam.p.z };
	float3 D;
	D.x = ((float)i - (float)WIDTH / 2.0f) * 0.5f / (float)WIDTH;
	D.y = (-(float)j + (float)WIDTH / 2.0f) * 0.5f / (float)HEIGHT;
	D.z = 1.f; // vv from cam
	D = rotate_ort(D, cam.d);

	float3 c = TraceRay(O, D, 1.0F, INFINITY, figures, light, o_n, l_n, textures, textures_sz);
	int new = apply_effects(c, effects);
	data[j * 1200 + i] = new;
}

// /******************************************************************************/
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   1.cl                                               :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2018/06/12 14:28:30 by mstorcha          #+#    #+#             */
// /*   Updated: 2018/06/12 14:28:33 by mstorcha         ###   ########.fr       */
// /*                                                                            */
// /******************************************************************************/

// #include "rendering.h.cl"
// #include "./opencl/intersections.cl"
// #include "./opencl/effects.cl"

// void	swap(float f, float s)
// {
// 	float tmp = f;
// 	f = s;
// 	s = tmp;
// }

// int		return_int_color(float3 c)
// {
// 	return ((int)c.x * 0x10000 + (int)c.y * 0x100 + (int)c.z);
// }

// float3		return_point_color(int c)
// {
// 	float3 p;
// 	p.x = (c >> 16) & 255; // 255
// 	p.y = (c >> 8) & 255; // 122
// 	p.z = c & 255; // 15
// 	return p;
// }

// float	sum_color(float f, float s)
// {
// 	float r;

// 	r = clamp(f + s, 0.0f, 255.0f);
// 	r = clamp(f + s, 0.0f, 255.0f);
// 	r = clamp(f + s, 0.0f, 255.0f);

// 	return r;
// }

// float3		rotate_ort(float3 point, float3 rot)
// {
// 	float3 od;
// 	float3 dv;
// 	float3 tr;
// 	float3 rot_rad;

// 	rot_rad.x = rot.x * M_PI / 180.0f;
// 	rot_rad.y = rot.y * M_PI / 180.0f;
// 	rot_rad.z = rot.z * M_PI / 180.0f;
// 	od.x = point.x;
// 	od.y = point.y * cos(rot_rad.x) + point.z * sin(rot_rad.x);
// 	od.z = point.z * cos(rot_rad.x) - point.y * sin(rot_rad.x);
// 	dv.x = od.x * cos(rot_rad.y) - od.z * sin(rot_rad.y);
// 	dv.y = od.y;
// 	dv.z = od.z * cos(rot_rad.y) + od.x * sin(rot_rad.y);
// 	tr.x = dv.x * cos(rot_rad.z) + dv.y * sin(rot_rad.z);
// 	tr.y = dv.y * cos(rot_rad.z) - dv.x * sin(rot_rad.z);
// 	tr.z = dv.z;
// 	return tr;
// }

// t_closest		closest_fig(float3 O, float3 D,
// 			float min, float max, __global t_figure *figures, int o_n)
// {
// 	t_figure ret;
// 	float closest = INFINITY;
// 	float2 tmp;
// 	for (int i = 0; i < o_n; i++)
// 	{
// 		if (figures[i].type == CYLINDER)
// 			tmp = IntersectRayCylinder(O, D, figures[i]);
// 		else if (figures[i].type == CONE)
// 			tmp = IntersectRayCone(O, D, figures[i]);
// 		else if (figures[i].type == PLANE)
// 			tmp = IntersectRayPlane(O, D, figures[i]);
// 		else if (figures[i].type == SPHERE)
// 			tmp = IntersectRaySphere(O, D, figures[i]);
// 		else if (figures[i].type == DISK)
// 			tmp = IntersectRayDisk(O, D, figures[i]);
// 		else if (figures[i].type == CUBE)
// 			tmp = IntersectRayCube(O, D, figures[i]);
// 		else if (figures[i].type == HYPERBOLOID)
// 			tmp = IntersectRayHyperboloid(O, D, figures[i]);
// 		else if (figures[i].type == TWOSHEET_HYPERBOLOID)
// 			tmp = IntersectRayTwoSheetHyperboloid(O, D, figures[i]);
// 		else if (figures[i].type == PARABOLOID)
// 			tmp = IntersectRayParaboloid(O, D, figures[i]);
// 		else if (figures[i].type == ELLIPSOID)
// 			tmp = IntersectRayEllipsoid(O, D, figures[i]);

// 		if (tmp.x >= min && tmp.x <= max && tmp.x < closest)
// 		{
// 			closest = tmp.x;
// 			ret = figures[i];
// 		}
// 		if (tmp.y >= min && tmp.y <= max && tmp.y < closest)
// 		{
// 			closest = tmp.y;
// 			ret = figures[i];
// 		}
// 	}
// 	return (t_closest){closest, ret};
// }

// float   compute_light(float3 P, float3 N, float3 V, float s, __global t_figure *figures,
//                     __global t_figure *light, int o_n, int l_n)
// {
//     float koef = 0.1f;
//     for (int i = 0; i < l_n; i++)
//     {
//         t_figure l = light[i];
//         float3 Lp = {l.p.x, l.p.y, l.p.z};
//         float3 L = Lp - P;
//         //shadow
//         t_closest clos = closest_fig(P, L, 0.001f, 0.99f, figures, o_n);
//         float closest = INFINITY;
//         closest = clos.closest;
//         if (closest != INFINITY)
//             continue;
//         //difuse
//         float n_dot_l = dot(N,L);
//         if (n_dot_l > 0.0f)
//             koef += l.angle * n_dot_l / (fast_length(N) * fast_length(L));
//         //zerk
//         if (s != -1.0f)
//         {
//             float3 R = N * 2.0f * n_dot_l - L;
//             float r_dot_v = dot(R,V);
//             if (r_dot_v > 0.0f)
//                 koef += l.angle*pow(r_dot_v / (fast_length(R) * fast_length(V)), s);
//         }
//     }
//     return (koef > 1.0f) ? 1.0f : koef;
// }

// float3	ReflectRay(float3 R, float3 N)
// {
// 	return 2.0f * N * dot(R, N) - R;
// }

// float3	RefractRay(float3 R, float3 N, float n1, float n2)
// {
// 	float n = n1 / n2;
// 	float cosI = - dot(N, R);
// 	float sinT2 = n * n * (1.f - cosI * cosI);
// 	if (sinT2 > 1.f || sinT2 < -1.f)
// 		return (float3){ 0.f, 0.f, 0.f};
// 	float cosT = sqrt(1.f - sinT2);
// 	return n * R + (n * cosI - cosT) * N;
// }

// void 	fresnel(float3 R, float3 N, float n1, float n2, float *kr) 
// { 
// 	float ior = n1 / n2;
//     float cosi = clamp((float)dot(R, N), -1.f, 1.f); 
//     float etai = 1.f, etat = ior; 
//     if (cosi > 0.f) 
//     	swap(etai, etat);

//     float sint = etai / etat * sqrt(max(0.f, 1.f - cosi * cosi));

//     if (sint >= 1.f)
//         *kr = 1.0f;
//     else
//     { 
//         float cost = sqrtf(max(0.f, 1.f - sint * sint)); 
//         cosi = fabsf(cosi); 
//         float Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost)); 
//         float Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost)); 
//         *kr = (Rs * Rs + Rp * Rp) / 2.0f; 
//     }
// }

// float3   compute_normal(t_figure figure, float3 D, float3 P)
// {
// 	float3 N;
	
// 	if (figure.type == PLANE  || figure.type == DISK)
// 	{
// 		float3 d = {figure.d.x, figure.d.y, figure.d.z};
// 		if (dot(d,D) < 0.0f)
// 			N = fast_normalize(d);
// 		else 
// 		 	N = fast_normalize(-d);
// 	}
// 	else if (figure.type == CONE)
// 	{
// 		float3 d = {figure.d.x, figure.d.y, figure.d.z};
// 		float3 p = {figure.p.x, figure.p.y, figure.p.z};
// 		float3 T = d-p;
// 		T = T / fast_length(T);
// 		N = P - p;
// 		T = T * dot(N, T);
// 		N = N - T;
// 		N = fast_normalize(N);
// 	}
// 	else if (figure.type == SPHERE)
// 	{
// 		float3 p = {figure.p.x, figure.p.y, figure.p.z};
// 		N = P - p;
// 		N = N / fast_length(N);
// 	}
// 	else if (figure.type == CYLINDER)
// 	{
// 		float3 p = {figure.p.x, figure.p.y, figure.p.z};
// 		float3 d = {figure.d.x, figure.d.y, figure.d.z};
// 		N = P - p;
// 		float3 T = d - p;
// 		T = T / fast_length(T);
// 		T = T * dot(N, T);
// 		N = (N - T) / fast_length(N - T);
// 	}
// 	else if (figure.type == CUBE)
// 	{
// 		float3 center = {(figure.min.x + figure.max.x) / 2., 
// 			(figure.min.y + figure.max.y) / 2., (figure.min.z + figure.max.z) / 2.};
// 		float3 center_p = P - center;
// 		double bias = 1.00001;
// 		float3 d = {fabs(figure.min.x - figure.max.x) / 2., 
// 			fabs(figure.min.y - figure.max.y) / 2., fabs(figure.min.z - figure.max.z) / 2.};
// 		N = (float3){center_p.x / fabs(d.x) * bias, center_p.y / fabs(d.y) * bias,
// 		 center_p.z / fabs(d.z) * bias};
// 		N = fast_normalize(N);
// 		// printf("%f %f %f \n", N.x, N.y, N.z);
// 	}
// 	else if (figure.type == HYPERBOLOID || figure.type == TWOSHEET_HYPERBOLOID)
// 	{
// 		float3 p = {figure.p.x, figure.p.y, figure.p.z};
// 		float3 C = P - p;

// 		N = (float3){2.f * C.x, -2.f * C.y, 2.f * C.z};
// 		N = N / fast_length(N);
// 	}
// 	else if (figure.type == PARABOLOID)
// 	{
// 		float3	p = {figure.p.x, figure.p.y, figure.p.z};
// 		float3	d = {figure.d.x, figure.d.y, figure.d.z};
// 		d /= fast_length(d);
// 		float3	C = P - p;
// 		float	m = dot(C, d);
// 		float	radius = 1.f;
// 		N = C - d * (m + radius);
// 		N = N / fast_length(N);
// 	}
// 	else if (figure.type == ELLIPSOID)
// 	{
// 		float3	p = {figure.p.x, figure.p.y, figure.p.z};
// 		float3	d = {figure.d.x, figure.d.y, figure.d.z};
// 		d /= fast_length(d);
// 		float	r = figure.radius;

// 		float	coef = 0.7f;
// 		float	k = r * sqrtf(1.f - coef * coef);

// 		float3	Cmid = p + (d * k / 2.f);
// 		float3	R = P - Cmid;
// 		N = R - d * (1.f - (coef * coef)) * dot(R, d);
// 		N = N / fast_length(N);
// 	}
// 	return N;
// }
// float3			calc_uv(float3 N, float3 P, t_figure obj)
// {
// 	float3	U;
// 	float3	V;
// 	float3	ret = 0.0F;

// 	N = -N;
// 	ret.x = 0.5F + atan2pi(N.z, N.x) / 2.0f;
// 	if (obj.type == SPHERE)
// 		ret.y = 0.5F - asin(N.y) / M_PI;
// 	else if (obj.type == CYLINDER)
// 	{
// 		float H = fast_length(obj.d - obj.p);
// 		float h = fast_length(P - obj.p);
// 		ret.y = sqrt(h * h - obj.radius * obj.radius) / H / 2.0f * obj.radius;
// 	}
// 	else if (obj.type == CONE)
// 	{
// 		float H = fast_length(obj.d - obj.p);
// 		float h = fast_length(P - obj.d);
// 		ret.y = -h / H;
// 	}
// 	else if (obj.type == PLANE)
// 	{
// 		if (N.y >= 0 && N.y <= 0.0003f)
// 			N.y = N.z;
// 		else if (N.x >= 0 && N.x <= 0.0003f)
// 			N.x = N.z;

// 		U = fast_normalize((float3){N.y, N.x, 0.0F});
// 		V = cross(N, U);

// 		ret.x = 1.0F - dot(U, P);
// 		ret.y = dot(V, P);
// 	}
// 	return (ret);
// }

// float3			get_obj_color(float3 NL, float3 P, t_figure obj,
// 							__global int3 *t_i, __global int *textures)
// {
// 	int2			textures_info;
// 	float3			UV;
// 	int2			tex_pos;
// 	__global int	*tex;
// 	float 			scale;
// 	int	tmp = 0;
// 	int i = -1;

// 	//for (int i = 0; i < 2; i++)
// 	//	printf("%d %d %d\n", t_i[i].x, t_i[i].y, t_i[i].z);

// 	while (t_i[++i].z != obj.index)
// 	{
// 		//printf("%d %d %d\n", t_i[i].x, t_i[i].y, t_i[i].z);
// 		tmp += t_i[i].x * t_i[i].y;
// 	}
// 	//printf("our\n");
// 	tex = textures + tmp;
	
// 	UV = calc_uv(NL, P, obj);
// 	UV = rotate_ort(UV, (float3){0,0,0});
// 	textures_info = (int2) {t_i[i].y, t_i[i].x};

// 	//if (obj.scale <= EPSILON)
// 	scale = 1.0F;

// 	tex_pos.x = (int)((UV.x) * scale * (float)textures_info.x) % textures_info.x;
// 	if (tex_pos.x < 0)
// 		tex_pos.x = textures_info.x + tex_pos.x;
// 	tex_pos.y = (int)((UV.y) * scale * (float)textures_info.y) % textures_info.y;
// 	if (tex_pos.y < 0)
// 		tex_pos.y = textures_info.y + tex_pos.y;
// 	tex_pos.y = textures_info.y - tex_pos.y - 1;
// 	return (return_point_color(tex[(tex_pos.y) * (textures_info.x) + (tex_pos.x)]));
// }

// float3 TraceRay(float3 O, float3 D, float min, float max, __global t_figure *figures,
// 					__global t_figure *light, int o_n, int l_n, __global int *textures, __global int3 *textures_sz)
// {
// 	float3 hit_color;
// 	float3 P;
// 	float3 N;
// 	float3 local_c = (float3){0.0f,0.0f,0.0f};
// 	float closest = 0.0f;
// 	t_figure figure;
// 	float rfl_mask = 1.0f;
// 	float rfr_mask = 1.0f;
// 	int mat = 0;
// 	float3 NL;

// 	hit_color = (float3){0.0f, 0.0f, 0.0f};
// 	for (int i = 0;i < NUM_REFL;)
// 	{
// 		float c_l = 0.0f;
// 		t_closest clos = closest_fig(O, D, min, max, figures, o_n);
// 		closest = clos.closest;
// 		if (closest == INFINITY)
// 			//return (float3) {0, 0, 0};
// 			break ;
// 		figure = clos.figure;
// 		P = O + D * closest;
// 		N = compute_normal(figure, D, P);
// 		c_l = compute_light(P, N, -D, 20.0f, figures, light, o_n, l_n);

// 		if (figure.text)
// 		{
// 			//printf("%d\n", figure.index);
// 			NL = dot(N, D) > 0.0F ? N * (-1.0F) : N;
// 			local_c = get_obj_color(NL, P, figure, textures_sz, textures);
// 		}
// 		else
// 			local_c = figure.color;
// 		local_c *= c_l;


// 		mat = figure.matirial;
// 		if (mat == 0)
// 	 	{
// 			hit_color = hit_color + local_c * (rfl_mask * rfr_mask);
// 			break ;
// 	 	}
// 		else if (mat == 1)
// 		{
// 			D = ReflectRay(-D, N);
// 			O = P;
// 			hit_color = hit_color + local_c * ((1.0f - figure.rfl) * rfl_mask * rfr_mask);
// 			rfl_mask = rfl_mask * figure.rfl;
// 			min = 0.001f;
// 			i++;
// 		}/*
// 		else if (mat == 2)
// 		{	
// 			float kr;

// 			fresnel(D, N, 1.f, 2.f, &kr);
// 			if (kr < 1.f)
// 			{
// 				D = RefractRay(P, N, 1.f, 2.f);
// 				O = P;
// 				hit_color += local_c * (1.0f - figure.rfr) * rfr_mask * (1.f - kr);
// 				rfr_mask *= figure.rfr;
// 				min = 0.001f;
// 				i++;
// 				continue ;
// 			}
// 			D = ReflectRay(-D, N);
// 			O = P;
// 			hit_color += local_c * ((1.0f - figure.rfl) * rfl_mask * (kr));
// 			rfl_mask *= figure.rfl;
// 			min = 0.001f;
// 		}
// 		i++;*/
// 	}
// 	return hit_color;
// }


// float fade(float t) { return t * t * t * (t * (t * 6 - 15) + 10); }

// float lerp(float t, float a, float b) { return a + t * (b - a); }

// float grad(int hash, float x, float y, float z)
// {
// 	int h = hash & 15;                      // CONVERT LO 4 BITS OF HASH CODE
// 	float u = h<8 ? x : y,                 // INTO 12 GRADIENT DIRECTIONS.
// 	v = h<4 ? y : h==12||h==14 ? x : z;
// 	return ((h&1) == 0 ? u : -u) + ((h&2) == 0 ? v : -v);
// }

// float noise1(float x, float y, float z, __global int * rand)
// {
// 	__global int *p = rand;
// 	int X = (int)floor(x) & 255,                  // FIND UNIT CUBE THAT
// 	    Y = (int)floor(y) & 255,                  // CONTAINS POINT.
// 	    Z = (int)floor(z) & 255;
// 	x -= floor(x);                                // FIND RELATIVE X,Y,Z
// 	y -= floor(y);                                // OF POINT IN CUBE.
// 	z -= floor(z);
// 	float u = fade(x),                                // COMPUTE FADE CURVES
// 	       v = fade(y),                                // FOR EACH OF X,Y,Z.
// 	       w = fade(z);
// 	int A = p[X  ]+Y, AA = p[A]+Z, AB = p[A+1]+Z,      // HASH COORDINATES OF
// 	    B = p[X+1]+Y, BA = p[B]+Z, BB = p[B+1]+Z;      // THE 8 CUBE CORNERs
// 	return lerp(w, lerp(v, lerp(u, grad(p[AA  ], x  , y  , z   ),  // AND ADD
// 	                               grad(p[BA  ], x-1, y  , z   )), // BLENDED
// 	                       lerp(u, grad(p[AB  ], x  , y-1, z   ),  // RESULTS
// 	                               grad(p[BB  ], x-1, y-1, z   ))),// FROM  8
// 	               lerp(v, lerp(u, grad(p[AA+1], x  , y  , z-1 ),  // CORNERS
// 	                               grad(p[BA+1], x-1, y  , z-1 )), // OF CUBE
// 	                       lerp(u, grad(p[AB+1], x  , y-1, z-1 ),
// 	                               grad(p[BB+1], x-1, y-1, z-1 ))));
// }

// __kernel void create_disruption(__global int * data, float3 color, int type, __global int * rand)
// {
// 	int j = get_global_id(0);
// 	int i = get_global_id(1);
// 	int finalValue = 0;

// 	if (type == 1)
// 	{
// 		float koef = 40.f;
// 		float dx = (float) j / 1200.0f;
// 	    float dy = (float) i / 1200.0f;
// 	    int frequency = 100;
// 	    float noise = noise1((dx * koef) + koef , (dy * koef) + koef, koef, rand);
// 	    noise = (noise - 1) / 2;
// 	    int b = (int)(noise * 0xFF);
// 	    int g = b * 0x100;
// 	    int r = b * 0x10000;
// 	    finalValue = r;
// 	}
// 	else if (type == 2)
// 	{
// 		if ((i % 100 <= 50 && j % 100 <= 50) || (i % 100 >= 50 && j % 100 >= 50))
// 			finalValue = return_int_color(color);
// 		else if ((i % 100 >= 50 && j % 100 <= 50) || (i % 100 <= 50 && j % 100 >= 50))
// 			finalValue = return_int_color((float3){255,255,255});
// 	}
//     data[j * 1200 + i] = finalValue;
// }

// int apply_effects(float3 a, int type)
// {
// 	float3 c;
// 	if (type == 1)
// 	{
// 		c = e_grades_gray(a);
// 	}
// 	else if (type == 2)
// 	{
// 		c = e_sepia(a);
// 	}
// 	else if (type == 3)
// 	{
// 		c = e_negative(a);
// 	}
// 	else if (type == 4)
// 	{
// 		c = e_black_white(a);
// 	}
// 	return return_int_color(c);
// }


// __kernel void rendering(__global int * data, __global t_figure *figures,
// 					__global t_figure *light, t_figure cam,
// 					int l_n, int o_n, __global int *textures, __global int3 *textures_sz, int effects)
// {
// 	int j = get_global_id(0);
// 	int i = get_global_id(1);

// 	float3 O = { cam.p.x, cam.p.y, cam.p.z };
// 	float3 D;
// 	D.x = ((float)i - (float)WIDTH / 2.0f) * 0.5f / (float)WIDTH;
// 	D.y = (-(float)j + (float)WIDTH / 2.0f) * 0.5f / (float)HEIGHT;
// 	D.z = 1.f; // vv from cam
// 	D = rotate_ort(D, cam.d);

// 	float3 c = TraceRay(O, D, 1.0F, INFINITY, figures, light, o_n, l_n, textures, textures_sz);
	
// 	int new = apply_effects(c, effects);
// 	data[j * 1200 + i] = (new);
// }


// __kernel void find_figure(__global int *returnable,
// 							__global t_figure *figures,
// 							t_figure cam, int i, int j, int o_n)
// {
// 	float d = 1;
// 	float3 O = { cam.p.x, cam.p.y, cam.p.z };
// 	float3 D;
// 	D.x = ((float)i - (float)WIDTH / 2.0f) * 0.5f / (float)WIDTH;
// 	D.y = (-(float)j + (float)WIDTH / 2.0f) * 0.5f / (float)HEIGHT;
// 	D.z = d;
// 	D = rotate_ort(D, cam.d);

// 	t_closest clos = closest_fig(O, D, 1.0F, INFINITY, figures, o_n);
// 	if (clos.closest == INFINITY)
// 		*returnable = -1;
// 	else
// 		*returnable = clos.figure.index;
// }
