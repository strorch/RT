/* **************************************************************************** */
/*                                                                              */
/*                                                         :::      ::::::::    */
/*    intersections.h.cl                                 :+:      :+:    :+:    */
/*                                                     +:+ +:+         +:+      */
/*    By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+         */
/*                                                 +#+#+#+#+#+   +#+            */
/*    Created: 2018/07/02 13:37:39 by mstorcha          #+#    #+#              */
/*    Updated: 2018/07/02 13:37:41 by mstorcha         ###   ########.fr        */
/*                                                                              */
/* **************************************************************************** */

#include "rendering.h.cl"

static inline float2 SolveQuadEquation(float A, float B, float C)
{
	float desk = B * B - 4.0f * A * C;

	if (desk < 0.0f)
		return (float2){INFINITY, INFINITY};

	float t1 = (-B + sqrt(desk)) / (2.0f * A);
	float t2 = (-B - sqrt(desk)) / (2.0f * A);
	return (float2){t1, t2};
}

float2 IntersectRayCone(float3 O, float3 D, t_figure cone)
{
	float A = cone.angle * M_PI / 180.0f;
	float tmp;
	float3 d = {cone.d.x, cone.d.y, cone.d.z};
	float3 p = {cone.p.x, cone.p.y, cone.p.z};

	float3 V = D;
	float3 P = O;
	float3 Pa = {cone.p.x, cone.p.y, cone.p.z};
	float3 Va = (d - p) / fast_length(d - p);
	float3 dP = P - Pa;

	float sc1 = dot(V, Va);
	float sc2 = dot(dP, Va);
	float3 tmp1 = V - Va * dot(V, Va);
	float3 tmp2 = dP - Va * dot(Va, dP);

	float A1 = cos(A) * cos(A) * dot(tmp1, tmp1)
					- sin(A) * sin(A)* sc1 * sc1;
	float B1 = 2.0f * cos(A) * cos(A) * dot(tmp1, tmp2)
					- 2.0f * sin(A) * sin(A) * sc1 * sc2;
	float C1 = cos(A) * cos(A) * dot(tmp2, tmp2)
					- sin(A) * sin(A)* sc2 * sc2;

	float2 r_f = SolveQuadEquation(A1, B1, C1);
	float t1 = r_f.x;
	float t2 = r_f.y;

	/*if (t1 < t2)
		tmp = t1;
	else
		tmp = t2;
	if (tmp >= 1. && tmp <= INFINITY)
	{
		float3 P = O + D * tmp;
		float3 v = P - cone.p;
		float l = dot(v, v);
		if (l >= cone.size)
			return INFINITY;
	}*/
	return (float2){t1, t2};
}

float2 IntersectRaySphere(float3 O, float3 D, t_figure sphere)
{
	float R = sphere.radius;
	float3 C = {sphere.p.x, sphere.p.y, sphere.p.z};
	float3 oc = (float3){O.x - C.x, O.y - C.y, O.z - C.z};

	float k1 = dot(D,D);
	float k2 = 2.0f * dot(oc,D);
	float k3 = dot(oc,oc) - R * R;

	
	return SolveQuadEquation(k1, k2, k3);
}

float2 IntersectRayCylinder(float3 O, float3 D, t_figure cyl)
{
	float R = cyl.radius;
	float tmp;

	float3 V = D;
	float3 P = O;
	float3 P2 = {cyl.d.x, cyl.d.y, cyl.d.z};
	float3 P1 = {cyl.p.x, cyl.p.y, cyl.p.z};
	float3 Va = (P2 - P1) / fast_length(P2 - P1);	
	float3 dP = P - P1;

	float3 tmp1 = V - (Va * dot(V, Va));
	float3 tmp2 = dP - (Va * dot(Va, dP));
	float A = dot(tmp1, tmp1);
	float B = 2.0f * dot(tmp1, tmp2);
	float C = dot(tmp2, tmp2) - R * R;

	float2 cc = SolveQuadEquation(A, B, C);
	float t1 = cc.x;
	float t2 = cc.y;
	// if (t1 < t2)
	// 	tmp = t1;
	// else
	// 	tmp = t2;
	// if (tmp >= 1. && tmp <= INFINITY)
	// {
	// 	float3 P = O + D * tmp;
	// 	float3 v = P - cyl.p;
	// 	float l = dot(v, v);
	// 	if (l >= cyl.size)
	// 		return INFINITY;

	// }
	return (float2){t1, t2};
}

float2 IntersectRayPlane(float3 O, float3 D, t_figure plane)
{
	float	t;
	float3 d = {plane.d.x, plane.d.y, plane.d.z};
	float3 p = {plane.p.x, plane.p.y, plane.p.z};

	d = fast_normalize(d);
	float3 oc = O - p;
	float k1 = dot(d, D);
	float k2 = dot(oc, d);
	if (k1 != 0.0f)
	{
		t = -k2 / k1;
		return (float2) {t, INFINITY};
	}
	return (float2) {INFINITY, INFINITY};
}

float2 IntersectRayDisk(float3 O, float3 D, t_figure disk)
{
	float2 t1;
	float	t;
	float3 	p;
	float 	d;
	float3 	v;

	float3 p0 = {disk.p.x, disk.p.y, disk.p.z};
	t1 = IntersectRayPlane(O, D, disk);
	t = t1.x;

	if (t > 1.0 && t < INFINITY)
	{
		p = O + D * t;
		v = p - p0;
		d = dot(v, v);
		if (d <= disk.radius)
        return (float2){t, INFINITY}; 
	}
    return (float2){INFINITY, INFINITY}; 
}

float IntersectRayCube(float3 O, float3 D, t_figure box)
{
	float3 min = {box.min.x, box.min.y, box.min.z};
  	float3 max = {box.max.x, box.max.y, box.max.z};
  	if (D.x == 0 && (O.x < 0.5 || O.x > 0.5))
		return INFINITY;
	float tmin = (min.x - O.x) / D.x;
	float tmax = (max.x - O.x) / D.x;
	float tmp = 0;
	if (tmin > tmax)
    {
    	float tmp = tmin;
    	tmin = tmax;
    	tmax = tmp;
    }
    if (D.y == 0 && (O.y < 0.5 || O.y > 0.5))
		return INFINITY;
    float tymin = (min.y - O.y) / D.y; 
    float tymax = (max.y - O.y) / D.y; 
    if (tymin > tymax)
    {
    	float tmp = tymin;
    	tymin = tymax;
    	tymax = tmp;
    } 
    if ((tmin > tymax) || (tymin > tmax)) 
        return INFINITY;

    if (tymin > tmin) 
        tmin = tymin;
 
    if (tymax < tmax) 
        tmax = tymax;
    if (D.z == 0 && (O.z < 0.5 || O.z > 0.5))
		return INFINITY;
    float tzmin = (min.z - O.z) / D.z; 
    float tzmax = (max.z - O.z) / D.z; 
    if (tzmin > tzmax)
    {
    	float tmp = tzmin;
    	tzmin = tzmax;
    	tzmax = tmp;
    }

    if ((tmin > tzmax) || (tzmin > tmax)) 
        return INFINITY; 
 
    if (tzmin > tmin) 
        tmin = tzmin; 
 
    if (tzmax < tmax) 
        tmax = tzmax; 

    // printf("%f\n", tmin);
    return tmin;
}

float2 IntersectRayHyperboloid(float3 O, float3 D, t_figure h_boloid)
{
	float3	c = {h_boloid.p.x, h_boloid.p.y, h_boloid.p.z};
	float3	P = O - c;
	float	R = h_boloid.radius;

	float	A = D.x * D.x - D.y * D.y + D.z * D.z;
	float	B = 2.0f * (P.x * D.x - P.y * D.y + P.z * D.z);
	float	C = P.x * P.x - P.y * P.y + P.z * P.z - R * R;
	return (SolveQuadEquation(A, B, C));
}

float2 IntersectRayTwoSheetHyperboloid(float3 O, float3 D, t_figure h_boloid)
{
	float3	c = {h_boloid.p.x, h_boloid.p.y, h_boloid.p.z};
	float3	P = O - c;
	float	R = h_boloid.radius;

	float	A = D.x * D.x - D.y * D.y + D.z * D.z;
	float	B = 2.0f * (P.x * D.x - P.y * D.y + P.z * D.z);
	float	C = P.x * P.x - P.y * P.y + P.z * P.z + R * R;
	return (SolveQuadEquation(A, B, C));
}

float2 IntersectRayParaboloid(float3 O, float3 D, t_figure p_boloid)
{
	float3	c = {p_boloid.p.x, p_boloid.p.y, p_boloid.p.z};
	float3	V = {p_boloid.d.x, p_boloid.d.y, p_boloid.d.z};
	V /= fast_length(V);
	float3	P = O - c;

	float	k = 1.0;
	float	A = dot(D, D) - dot(D, V) * dot(D, V);
	float	B = 2.0f * (dot(D, P) - dot(D, V) * (dot(P, V) + 2.0f*k));
	float	C = dot(P, P) - dot(P, V) * (dot(P, V) + 4.0f*k);

	float2	t = SolveQuadEquation(A, B, C);
	float	t_min = t.x < t.y ? t.x : t.y;

	float	cap = p_boloid.cap;
	float	m = dot(O + D * t_min - c, V);
	if (m > INFINITY)
		return ((float2){INFINITY, INFINITY});
	else
		return (t);
}

float2 IntersectRayEllipsoid(float3 O, float3 D, t_figure ellipse)
{
	float3 c = {ellipse.p.x, ellipse.p.y, ellipse.p.z};
	float3 V = {ellipse.d.x, ellipse.d.y, ellipse.d.z};
	V /= fast_length(V);
	float3 OC = (float3){O.x - c.x, O.y - c.y, O.z - c.z};

	float	coef = 0.7f;
	float	a = ellipse.radius;
	float	b = coef * a;
	float	r = 2.f * a;
	float	r2 = r * r;
	
	float	k = 2.f * sqrtf(a * a - b * b);

	float	A1 = 2.f * k * dot(D, V);
	float	A2 = r2 + 2.f * k * dot(OC, V) - k;
	float	A = 4.f * r2 * dot(D, D) - A1 * A1;
	float	B = 8.f * r2 * dot(D, OC) - 2.f * A1 * A2;
	float	C = 4.f * r2 * dot(OC, OC) - A2 * A2;
	return (SolveQuadEquation(A, B, C));
}
