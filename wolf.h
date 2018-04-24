/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 12:14:12 by sergee            #+#    #+#             */
/*   Updated: 2018/04/24 15:23:08 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# include <math.h>
# include <time.h>
# include <OpenCL/opencl.h>
# include "SDL.h"
# include "SDL_ttf.h"
# include "SDL_image.h"
# include "ft_printf.h"

# define DEVICE_TYPE CL_DEVICE_TYPE_CPU
# define WIDTH 1600
# define HIGH 1200

typedef	struct			s_host
{
	cl_device_id		dev_id;
	cl_context			context;
	cl_command_queue	com_queue;
	cl_mem				memobj;
	cl_mem				map;
	cl_mem				wall;
	cl_program			program;
	cl_kernel			kernel;
	cl_platform_id		p_id;
	cl_uint				ret_num_dev;
	cl_uint				ret_num_p;
	size_t				gl_w_s;
}						t_host;

typedef struct			s_point
{
	float				x;
	float				y;
}						t_point;

typedef struct			s_player
{
	t_point				pos;
	t_point				dir;
	int					move;
	int					rot;
	int					fire;
	float				m_s;
	float				r_s;
}						t_player;

typedef struct			s_map
{
	int					row;
	int					col;
	int					*map;
}						t_map;

typedef struct			s_wall
{
	int					w;
	int					h;
	t_ui				wall[512 * 512];
}						t_wall;

typedef struct			s_sdl
{
	SDL_Window			*win;
	SDL_Surface			*surface;
	SDL_Surface			*fps;
	SDL_Surface			*weapon;
	SDL_Surface			*weapon_fire;
	SDL_Surface			*bar;
	SDL_Surface			*w[7];
	SDL_Event			event;
	TTF_Font			*ttf;
	t_host				host;
	t_wall				*wall;
	t_player			player;
	t_map				map;
	t_point				plane;
}						t_sdl;

int						raycast(t_sdl *data, int *worldmap, t_player player,
							t_point plane);
void					read_coordinate(t_sdl *data, int fd, char *av,
							t_map *map);
void					download_tex(t_sdl *data);
void					toolbar(t_sdl *data);
void					fps(t_sdl *data);
void					move(t_map *map, t_player *p);
void					rotate(t_player *p, t_point *pl);
int						ft_handler(t_sdl *data);
int						host_fract(t_sdl *data);
void					kernel_param(t_sdl *data);

#endif
