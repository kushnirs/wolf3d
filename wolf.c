/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 09:09:57 by skushnir          #+#    #+#             */
/*   Updated: 2018/03/15 15:19:12 by sergee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

// static void	draw(int x, int start, int end, int color, t_sdl *data)
// {
// 	int *lox;
// 	lox = (int*)data->surface->pixels;
// 	while (start++ < end)
// 		lox[x + start * WIDTH] = color;
// }

// int raycast(t_sdl *data, int *worldmap, t_player player, t_point plane)
// {
// 	int		x;
// 	int		map_x;
// 	int		map_y;
// 	t_point	s_dist;
// 	t_point	d_dist;
// 	int		step[2];
// 	int		hit;
// 	int		side;
// 	float 	perpWallDist;
// 	float	camera_x;
// 	t_point	ray;

// 	x = -1;
// 	while(++x < WIDTH)
// 	{
// 		camera_x = 2.0 * x / WIDTH - 1.0;
// 		ray.x = player.dir.x + plane.x * camera_x;
// 		ray.y = player.dir.y + plane.y * camera_x;
// 		map_x = (int)player.pos.x;
// 		map_y = (int)player.pos.y;
// 		d_dist.x = fabs(1 / ray.x);
// 		d_dist.y = fabs(1 / ray.y);
// 		if (ray.x < 0)
// 		{
// 			step[0] = -1;
// 			s_dist.x = (player.pos.x - map_x) * d_dist.x;
// 		}
// 		else
// 		{
// 			step[0] = 1;
// 			s_dist.x = (map_x + 1.0f - player.pos.x) * d_dist.x;
// 		}
// 		if (ray.y < 0)
// 		{
// 			step[1] = -1;
// 			s_dist.y = (player.pos.y - map_y) * d_dist.y;
// 		}
// 		else
// 		{
// 			step[1] = 1;
// 			s_dist.y = (map_y + 1.0f - player.pos.y) * d_dist.y;
// 		}
// 		hit = 0;
// 		while (!hit)
// 		{
// 			if (s_dist.x < s_dist.y)
// 			{
// 				s_dist.x += d_dist.x;
// 				map_x += step[0];
// 				side = 0;
// 			}
// 			else
// 			{
// 				s_dist.y += d_dist.y;
// 				map_y += step[1];
// 				side = 1;
// 			}
// 			worldmap[map_x * data->map.row + map_y] > 0 ? hit = 1 : 0;
// 		}
// 		perpWallDist = !side ? (map_x - player.pos.x + (1 - step[0]) / 2) / ray.x :
// 								(map_y - player.pos.y + (1 - step[1]) / 2) / ray.y;
// 		int	line_h;
// 		line_h = HIGH / perpWallDist;
// 		int	start;
// 		int	end;
// 		start = -line_h / 2 + HIGH / 2;
// 		start < 0 ? start = 0 : 0;
// 		end = line_h / 2 + HIGH / 2;
// 		end >= HIGH ? end = HIGH - 1 : 0;
// 		int	color;
// 		worldmap[map_x * data->map.row + map_y] == 1 ? color = 0xCC0000 : 0;
// 		worldmap[map_x * data->map.row + map_y] == 2 ? color = 0x009900 : 0;
// 		worldmap[map_x * data->map.row + map_y] == 3 ? color = 0x000099 : 0;
// 		worldmap[map_x * data->map.row + map_y] == 4 ? color = 0xffffff : 0;
// 		side == 1 ? color /= 2 : 0;
// 		draw(x, start, end, color, data);
// 	}
// 	return (0);
// }

int			main(int ac, char **av)
{
	int		fd;
	t_sdl	data;

	data = (t_sdl){.player = {{22, 12}, {-1, 0}}, .plane = {0, 0.66},
			.map = {.row = 0, .col = 0}};
	ac != 2 ?
		exit(write(1, "Usage : ./wolf3d <filename>\n", 28)) : 0;
	if ((fd = open(av[1], O_RDONLY)) == -1)
		exit(ft_printf("No file %s\n", av[1]));
	read_coordinate(fd, av[1], &data.map);
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	data.win = SDL_CreateWindow("Wolf3D", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIDTH, HIGH, 0);
	!data.win ? exit(ft_printf("Window error: %s\n", SDL_GetError())) : 0;
	data.surface = SDL_GetWindowSurface(data.win);
	!data.surface ? exit(ft_printf("Surface error: %s\n", SDL_GetError())) : 0;
	// for(int i = 0; i < 24 * 24; i++)
	// {
	// 	if (!(i % 24))
	// 		printf("\n");
	// 	printf("%d ", data.map.map[i]);
	// }
	host_fract(&data);
	while (1)
	{
		ft_bzero(data.surface->pixels, data.surface->w * data.surface->h * 4);
		raycast(&data,data.map.map, data.player, data.plane);
		// kernel_param(&data);
		fps(&data);
		while (SDL_PollEvent(&data.event))
			!ft_handler(&data, &data.map, &data.player, &data.plane) ? exit(0) : 0;
		SDL_UpdateWindowSurface(data.win);
	}
	return (0);
}
