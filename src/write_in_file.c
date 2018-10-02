/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_in_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstorcha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 22:02:09 by mstorcha          #+#    #+#             */
/*   Updated: 2018/07/30 22:02:11 by mstorcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <time.h>

static char			*get_fig_type(int type)
{
	if (type == SPHERE)
		return ("sphere");
	else if (type == CONE)
		return ("cone");
	else if (type == CYLINDER)
		return ("cylinder");
	else if (type == PLANE)
		return ("plane");
	else if (type == DISK)
		return ("disk");
	else if (type == CUBE)
		return ("cube");
	else if (type == HYPERBOLOID)
		return ("hyperboloid");
	else if (type == TWOSHEET_HYPERBOLOID)
		return ("2sheet_hyperboloid");
	else if (type == PARABOLOID)
		return ("paraboloid");
	else if (type == ELLIPSOID)
		return ("ellipsoid");
	return (NULL);
}

static char			*get_light_type(int type)
{
	if (type == 1)
		return ("ambient");
	else if (type == 2)
		return ("point");
	else if (type == 3)
		return ("direct");
	return (NULL);
}

static unsigned int	put_objects(char *str, t_scene sc)
{
	int			i;
	int			len;
	t_figure	*f;

	i = -1;
	len = 0;
	f = sc.objects;
	len += sprintf(str, "\n\t\"objects\" : [\n");
	while (++i < sc.o_num)
	{
		len += sprintf(str + len, "\t\t{\n\t\t\t\"origin\" : [%.2f,%.2f,%.2f],"
"\n\t\t\t\"direction\" : [%.2f,%.2f,%.2f],\n\t\t\t\"color\" : [%.2f,%.2f,%.2f],"
"\n\t\t\t\"type\" : \"%s\",\n\t\t\t\"reflective\" : \"%.2f\","
"\n\t\t\t\"radius\" : \"%.2f\",\n\t\t\t\"angle\" : \"%.2f\",\n",
			f[i].p.x, f[i].p.y, f[i].p.z, f[i].d.x, f[i].d.y, f[i].d.z,
			f[i].color.x, f[i].color.y, f[i].color.z,
			get_fig_type(f[i].type), f[i].rfl, f[i].radius, f[i].angle);
		if (f[i].type == CUBE)
			len += sprintf(str + len, "\t\t\t\"min\" : [%.2f,%.2f,%.2f],"
				"\n\t\t\t\"max\" : [%.2f,%.2f,%.2f],\n",
	f[i].min.x, f[i].min.y, f[i].min.z, f[i].max.x, f[i].max.y, f[i].max.z);
		len += sprintf(str + len, "\t\t},\n");
	}
	len += sprintf(str + len, "\t],");
	return (len);
}

static unsigned int	put_light(char *str, t_scene sc)
{
	int			i;
	int			len;
	t_figure	*l;

	i = -1;
	len = 0;
	l = sc.lights;
	len += sprintf(str, "\n\t\"light\" : [\n");
	while (++i < sc.l_num)
	{
		len += sprintf(str + len,
			"\t\t{\n\t\t\t\"position\" : [%.2f,%.2f,%.2f],"
				"\n\t\t\t\"intensity\" : %.2f,\n\t\t"
				"\t\"type\" : \"%s\",\n\t\t},\n",
	l[i].p.x, l[i].p.y, l[i].p.z, l[i].angle, get_light_type(l[i].type));
	}
	len += sprintf(str + len, "\t],");
	return (len);
}

void				write_in_file(t_scene sc)
{
	char			*str;
	char			*tmp1;
	unsigned int	len;
	t_figure		cam;
	FILE			*f;

	cam = sc.cam;
	str = malloc(sizeof(char) * MAX_SOURCE_SIZE);
	len = sprintf(str, "{\n\t");
	len += sprintf((str + len), "\"camera\" : [\n\t\t"
						"{\n\t\t\t\"origin\" : [%.2f,%.2f,%.2f],"
						"\n\t\t\t\"direction\" : [%.2f,%.2f,%.2f]\n\t\t}\n\t],",
			cam.p.x, cam.p.y, cam.p.z, cam.d.x, cam.d.y, cam.d.z);
	len += put_objects((str + len), sc);
	len += put_light((str + len), sc);
	len += sprintf(str + len, "\n}");
	tmp1 = ft_strjoin("./scenes/custom", ".j");
	f = fopen(tmp1, "w");
	free(tmp1);
	fwrite(str, sizeof(char), len, f);
}
