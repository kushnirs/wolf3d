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

#include "cl.h"

static void	draw(int x, int start, int end, int color, int *buff)
{
	while (start++ < end)
		buff[x + start * WIDTH] = color;
}

__kernel
void raycast(__global int *buff, __constant int *worldmap, t_player player, t_point plane)
{
	int		x;
	int		map_x;
	int		map_y;
	t_point	s_dist;
	t_point	d_dist;
	int		step[2];
	int		hit;
	int		side;
	float 	perpWallDist;
	float	camera_x;
	t_point	ray;

	x = -1;
	while(++x < WIDTH)
	{
		camera_x = 2.0f * x / WIDTH - 1.0f;
		ray.x = player.dir.x + plane.x * camera_x;
		ray.y = player.dir.y + plane.y * camera_x;
		map_x = (int)player.pos.x;
		map_y = (int)player.pos.y;
		d_dist.x = fabs(1.0f / ray.x);
		d_dist.y = fabs(1.0f / ray.y);
		if (ray.x < 0)
		{
			step[0] = -1;
			s_dist.x = (player.pos.x - map_x) * d_dist.x;
		}
		else
		{
			step[0] = 1;
			s_dist.x = (map_x + 1.0f - player.pos.x) * d_dist.x;
		}
		if (ray.y < 0)
		{
			step[1] = -1;
			s_dist.y = (player.pos.y - map_y) * d_dist.y;
		}
		else
		{
			step[1] = 1;
			s_dist.y = (map_y + 1.0f - player.pos.y) * d_dist.y;
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
			worldmap[map_x * data->map.row + map_y] > 0 ? hit = 1 : 0;
		}
		perpWallDist = !side ? (map_x - player.pos.x + (1.0f - step[0]) / 2.0f) / ray.x :
								(map_y - player.pos.y + (1.0f - step[1]) / 2.0f) / ray.y;
		int	line_h;
		line_h = HIGH / perpWallDist;
		int	start;
		int	end;
		start = -line_h / 2 + HIGH / 2;
		start < 0 ? start = 0 : 0;
		end = line_h / 2 + HIGH / 2;
		end >= HIGH ? end = HIGH - 1 : 0;
		int	color;
		worldmap[map_x * data->map.row + map_y] == 1 ? color = 0xCC0000 : 0;
		worldmap[map_x * data->map.row + map_y] == 2 ? color = 0x009900 : 0;
		worldmap[map_x * data->map.row + map_y] == 3 ? color = 0x000099 : 0;
		worldmap[map_x * data->map.row + map_y] == 4 ? color = 0xffffff : 0;
		side == 1 ? color /= 2 : 0;
		draw(x, start, end, color, data);
	}
}
