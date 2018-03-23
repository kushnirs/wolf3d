/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 09:09:57 by skushnir          #+#    #+#             */
/*   Updated: 2018/03/22 20:28:39 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void	download_tex(t_sdl *data)
{
	int		i;
	int		k;
	t_ui	*img;

	data->w[0] = IMG_Load("picture/wall_5.jpg");
	data->w[1] = IMG_Load("picture/wall_E.jpg");
	data->w[2] = IMG_Load("picture/wall_3.jpg");
	data->w[3] = IMG_Load("picture/wall_7.jpg");
	data->w[4] = IMG_Load("picture/wall_1.jpg");
	data->w[5] = IMG_Load("picture/side_5.jpg");
	data->w[6] = IMG_Load("picture/side_F.jpg");
	data->wall = (t_wall*)malloc(sizeof(t_wall) * 7);
	i = -1;
	while (++i < 7)
	{
		!data->w[i] ? exit(ft_printf("IMG %d error\n", i + 1)) : 0;
		data->wall[i].w = data->w[i]->w;
		data->wall[i].h = data->w[i]->h;
		img = (t_ui*)data->w[i]->pixels;
		k = -1;
		while (++k < data->w[i]->w * data->w[i]->h)
			data->wall[i].wall[k] = img[k];
	}
}

static void	init_sdl(t_sdl *data)
{
	SDL_Init(SDL_INIT_VIDEO) ? exit(ft_printf("SDL_Init error\n")) : 0;
	TTF_Init() ? exit(ft_printf("TTF_Init error")) : 0;
	!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) ?
		exit(ft_printf("IMG_Init error")) : 0;
	data->win = SDL_CreateWindow("Wolf3D", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIDTH, HIGH, 0);
	!data->win ? exit(ft_printf("Window error: %s\n", SDL_GetError())) : 0;
	data->surface = SDL_GetWindowSurface(data->win);
	!data->surface ? exit(ft_printf("Surface error: %s\n", SDL_GetError())) : 0;
}

static void	init_data(t_sdl *data, int ac, char **av)
{
	int		fd;

	*data = (t_sdl){.player = {{0, 0}, {-1, 0}, 0, 0, 0.06, 0.04},
			.plane = {0, -0.66}, .map = {.row = 0, .col = 0}};
	ac != 2 ?
		exit(write(1, "Usage : ./wolf3d <filename>\n", 28)) : 0;
	if ((fd = open(av[1], O_RDONLY)) == -1)
		exit(ft_printf("No file %s\n", av[1]));
	read_coordinate(data, fd, av[1], &data->map);
	download_tex(data);
}

int			main(int ac, char **av)
{
	t_sdl	data;

	init_data(&data, ac, av);
	init_sdl(&data);
	host_fract(&data);
	while (1)
	{
		kernel_param(&data);
		fps(&data);
		while (SDL_PollEvent(&data.event))
			!ft_handler(&data) ? exit(0) : 0;
		data.player.move ? move(&data.map, &data.player) : 0;
		data.player.rot ? rotate(&data.player, &data.plane) : 0;
		SDL_UpdateWindowSurface(data.win);
		SDL_GL_SetSwapInterval(1);
	}
	return (0);
}
