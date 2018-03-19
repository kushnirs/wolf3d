/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 09:09:57 by skushnir          #+#    #+#             */
/*   Updated: 2018/03/20 00:39:08 by sergee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void	download_tex(t_sdl *data)
{
	int	i;
	int	k;
	t_ui	*img;

	data->w[0] = IMG_Load("picture/wall_1.jpg");
	data->w[1] = IMG_Load("picture/wall_E.jpg");
	data->w[2] = IMG_Load("picture/wall_3.jpg");
	data->w[3] = IMG_Load("picture/wall_7.jpg");
	data->w[4] = IMG_Load("picture/wall_5.jpg");
	data->w[5] = IMG_Load("picture/side_5.jpg");
	data->w[6] = IMG_Load("picture/side_F.jpg");
	data->wall = (t_wall*)malloc(sizeof(t_wall) * 7);
	i = -1;
	while (++i < 7)
	{
		img = (t_ui*)data->w[i]->pixels;
		k = -1;
		while (++k < T_W * T_H)
			data->wall[i].w[k] = img[k];
	}
}
static void	init_sdl(t_sdl *data)
{
	SDL_Init(SDL_INIT_VIDEO) ? exit(ft_printf("SDL_Init error\n")) : 0;
	TTF_Init() ? exit(ft_printf("TTF_Init error")) : 0;
	!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) ? exit(ft_printf("IMG_Init error")) : 0;
	data->win = SDL_CreateWindow("Wolf3D", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIDTH, HIGH, 0);
	!data->win ? exit(ft_printf("Window error: %s\n", SDL_GetError())) : 0;
	data->surface = SDL_GetWindowSurface(data->win);
	!data->surface ? exit(ft_printf("Surface error: %s\n", SDL_GetError())) : 0;
}
int			main(int ac, char **av)
{
	int		fd;
	t_sdl	data;

	data = (t_sdl){.player = {{22, 22}, {-1, 0}, 0, 0, 0.09, 0.03},
			.plane = {0, -0.66}, .map = {.row = 0, .col = 0}};
	ac != 2 ?
		exit(write(1, "Usage : ./wolf3d <filename>\n", 28)) : 0;
	if ((fd = open(av[1], O_RDONLY)) == -1)
		exit(ft_printf("No file %s\n", av[1]));
	read_coordinate(fd, av[1], &data.map);
	init_sdl(&data);
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
