/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 09:09:57 by skushnir          #+#    #+#             */
/*   Updated: 2018/02/24 13:18:49 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf_cl.h"

__kernel
void raycast(__global int *buff, __constant int *worldmap, __constant t_wall *tex,
			t_point pos, t_point dir, t_point plane, t_point map_size)
{
	int		x = get_global_id(0);
	int		step[2];
	int		hit;
	int		side;
	t_point	ray;

	int ppc = -1;
	while (++ppc < HIGH)
		buff[x + ppc * WIDTH] = 0;
	float camera_x = 2.0f * x / WIDTH - 1.0f;
	ray.x = dir.x + plane.x * camera_x;
	ray.y = dir.y + plane.y * camera_x;
	t_point	s_dist;
	t_point	d_dist;
	d_dist.x = fabs(1.0f / ray.x);
	d_dist.y = fabs(1.0f / ray.y);
	int	map_x = (int)pos.x;
	int	map_y = (int)pos.y;
	if (ray.x < 0)
	{
		step[0] = -1;
		s_dist.x = (pos.x - (float)map_x) * d_dist.x;
	}
	else
	{
		step[0] = 1;
		s_dist.x = ((float)map_x + 1.0f - pos.x) * d_dist.x;
	}
	if (ray.y < 0)
	{
		step[1] = -1;
		s_dist.y = (pos.y - (float)map_y) * d_dist.y;
	}
	else
	{
		step[1] = 1;
		s_dist.y = ((float)map_y + 1.0f - pos.y) * d_dist.y;
	}
	hit = 0;
	while (!hit)
	{
		if (s_dist.x < s_dist.y)
		{
			s_dist.x += d_dist.x;
			map_x += step[0];
			side = 0;
		}
		else
		{
			s_dist.y += d_dist.y;
			map_y += step[1];
			side = 1;
		}
		worldmap[map_x + map_y * (int)map_size.x] > 0 ? hit = 1 : 0;
	}
	float wall_d = !side ? (map_x - pos.x + (1.0f - step[0]) / 2.0f) / ray.x :
							(map_y - pos.y + (1.0f - step[1]) / 2.0f) / ray.y;
	// WALL
	int	line_h;
	line_h = HIGH / wall_d;
	int	start;
	int	end;
	start = -line_h / 2 + HIGH / 2;
	start < 0 ? start = 0 : 0;
	end = line_h / 2 + HIGH / 2;
	end >= HIGH ? end = HIGH - 1 : 0;
	float texture = (worldmap[map_x + map_y * (int)map_size.x]) / 1000.0f;
	int	t_n;
	int t[4];
	t[0] = int(texture);
	texture = (texture - t[0]) * 10.0f;
	t[1] = int(texture);
	texture = (texture - t[1]) * 10.0f;
	t[2] = int(texture);
	texture = (texture - t[2]) * 10.0f;
	t[3] = round(texture);
	int why = -1;
	while (++why < 4)
		t[why] > 6 || t[why] < 0 ? t[why] = 0 : 0;
	!side && ray.x < 0 ? t_n = t[3] : 0;
	!side && ray.x > 0 ? t_n = t[0] : 0;
	side && ray.y > 0 ? t_n = t[2] : 0;
	side && ray.y < 0 ? t_n = t[1] : 0;
	float w_x;
	w_x = !side ? pos.y + wall_d * ray.y : pos.x + wall_d * ray.x;
	w_x -= floor(w_x);
	int tex_x = int(w_x * float(tex[t_n].w));
	!side && ray.x > 0 ? tex_x = tex[t_n].w - tex_x - 1 : 0;
	side && ray.y < 0 ? tex_x = tex[t_n].w - tex_x - 1 : 0;
	int i = start;
	while (++i < end)
	{
		int d = i * 256 - HIGH * 128 + line_h * 128;
		int tex_y = d * tex[t_n].h / line_h / 256;
		int color = tex[t_n].wall[tex[t_n].h * tex_y + tex_x];
		buff[x + i * WIDTH] = color;
	}
	// FLOOR
	t_point floor;
	if (!side)
	{
		floor.x = ray.x > 0 ? map_x : map_x + 1.0f;
		floor.y = map_y + w_x;
	}
	else
	{
		floor.y = ray.y > 0 ? map_y : map_y + 1.0f;
		floor.x = map_x + w_x;
	}
	end < 0 ? end = HIGH : 0;
	i = end;
	while (++i < HIGH)
	{
		float c_d = HIGH / (2.0f * i - HIGH);
		float weight = c_d / wall_d;
		t_point c_f;
		c_f.x = weight * floor.x + (1.0f - weight) * pos.x;
		c_f.y = weight * floor.y + (1.0f - weight) * pos.y;
		int	f_tex_x;
		int	f_tex_y;
		f_tex_x = (int)(c_f.x * tex[t_n].w) % tex[t_n].w;
		f_tex_y = (int)(c_f.y * tex[t_n].h) % tex[t_n].h;
		buff[x + i * WIDTH] = tex[5].wall[tex[t_n].h * f_tex_y + f_tex_x];
		buff[x + (HIGH - i) * WIDTH] = tex[6].wall[tex[t_n].h * f_tex_y + f_tex_x];
	}
}
