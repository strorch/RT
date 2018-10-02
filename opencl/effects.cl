/* **************************************************************************** */
/*                                                                              */
/*                                                         :::      ::::::::    */
/*    effects.cl                                         :+:      :+:    :+:    */
/*                                                     +:+ +:+         +:+      */
/*    By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+         */
/*                                                 +#+#+#+#+#+   +#+            */
/*    Created: 2018/07/02 18:29:45 by mstorcha          #+#    #+#              */
/*    Updated: 2018/07/02 18:29:46 by mstorcha         ###   ########.fr        */
/*                                                                              */
/* **************************************************************************** */

#include "rendering.h.cl"

float3		e_grades_gray(float3 a)
{
	float3 c;
	float tmp = (a.x + a.y + a.z) / 3;

	c.x = tmp;
	c.y = tmp;
	c.z = tmp;
	return c;
}

float3		e_sepia(float3 a)
{
	float3 c;
	float3 tmp = e_grades_gray(a);

	tmp.x = tmp.x + 40 * 2;
	tmp.y = tmp.y + 40;
	tmp.z = tmp.z;
	c.x = clamp((float)tmp.x, 0.0f, 255.f);
	c.y = clamp((float)tmp.y, 0.0f, 255.f);
	c.z = clamp((float)tmp.z, 0.0f, 255.f);
	return c;
}

float3		e_negative(float3 a)
{
	float3 c;

	c.x = 255 - a.x;
	c.y = 255 - a.y;
	c.z = 255 - a.z;
	return c;
}

float3		e_black_white(float3 a)
{
	float3 c;

	float tmp = (a.x + a.y + a.z) / 3.0f;
	if (tmp > 100)
	{
		c.x = 255;
		c.y = 255;
		c.z = 255;
	}
	else
	{
		c.x = 0;
		c.y = 0;
		c.z = 0;
	}
	return c;
}

float3		e_casting(float3 a)
{
	a.x = a.x * 128.0F / (a.y + a.z + 1.0F);
	a.y = a.y * 128.0F / (a.x + a.z + 1.0F);
	a.z = a.z * 128.0F / (a.y + a.x + 1.0F);
	return a;
}

float3		e_comic(float3 a)
{
	float3 tmp = a;
	a.x = fabs(tmp.y - tmp.z + tmp.y + tmp.x) * tmp.x / 256.0F;
	a.y = fabs(tmp.z - tmp.y + tmp.z + tmp.x) * tmp.x / 256.0F;
	a.z = fabs(tmp.z - tmp.y + tmp.z + tmp.x) * tmp.y / 256.0F;
	return a;
}
