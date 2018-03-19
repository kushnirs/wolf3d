/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 09:09:57 by skushnir          #+#    #+#             */
/*   Updated: 2018/03/19 14:03:41 by sergee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void	download_tex(t_sdl *data)
{
	data->w[0] = IMG_Load("picture/bluestone.png");
	data->w[1] = IMG_Load("picture/colorstone.png");
	data->w[2] = IMG_Load("picture/eagle.png");
	data->w[3] = IMG_Load("picture/purplestone.png");
	data->w[4] = IMG_Load("picture/wood.png");
	data->wall[0] = (int*)data->w[0]->pixels;
	data->wall[1] = (int*)data->w[1]->pixels;
	data->wall[2] = (int*)data->w[2]->pixels;
	data->wall[3] = (int*)data->w[3]->pixels;
	data->wall[4] = (int*)data->w[4]->pixels;
}

int			main(int ac, char **av)
{
	int		fd;
	t_sdl	data;

	data = (t_sdl){.player = {{22, 22}, {-1, 0}, 0, 0, 0.02, 0.007}, .plane = {0, -0.66},
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
	download_tex(&data);
	host_fract(&data);
	while (1)
	{
		kernel_param(&data);
		fps(&data);
		while (SDL_PollEvent(&data.event))
			!ft_handler(&data) ? exit(0) : 0;
		data.player.move || data.player.rot ?
			move(&data.map, &data.player, &data.plane) : 0;
		SDL_UpdateWindowSurface(data.win);
		vsync();
	}
	return (0);
}
