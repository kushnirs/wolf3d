/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 15:19:57 by skushnir          #+#    #+#             */
/*   Updated: 2018/04/24 15:23:43 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static int	close_sdl(t_sdl *data)
{
	SDL_DestroyWindow(data->win);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	return (0);
}

void		move(t_map *map, t_player *p)
{
	float	w;
	float	x;
	float	y;

	w = p->m_s * p->move > 0.0f ? 0.333f : -0.333f;
	x = (int)(p->pos.x + p->dir.x * (p->m_s * p->move + w)) +
		((int)p->pos.y - (int)(p->dir.y * w)) * map->col;
	!map->map[(int)x] ? p->pos.x += p->dir.x * p->m_s * p->move : 0;
	y = (int)p->pos.x - (int)(p->dir.x * w) +
	(int)(p->pos.y + p->dir.y * (p->m_s * p->move + w)) * map->col;
	!map->map[(int)y] ? p->pos.y += p->dir.y * p->m_s * p->move : 0;
}

void		rotate(t_player *p, t_point *pl)
{
	const t_point	old_pl = {pl->x, pl->y};
	const t_point	old_dir = {p->dir.x, p->dir.y};

	p->dir.x = p->dir.x * cos(p->r_s * p->rot) -
			p->dir.y * sin(p->r_s * p->rot);
	p->dir.y = old_dir.x * sin(p->r_s * p->rot) +
			p->dir.y * cos(p->r_s * p->rot);
	pl->x = pl->x * cos(p->r_s * p->rot) - pl->y * sin(p->r_s * p->rot);
	pl->y = old_pl.x * sin(p->r_s * p->rot) + pl->y * cos(p->r_s * p->rot);
}

static void	ft_handler_up(t_sdl *data)
{
	if (data->event.type == SDL_KEYUP)
	{
		if (data->event.key.keysym.sym == SDLK_UP ||
			data->event.key.keysym.sym == SDLK_DOWN)
			data->player.move = 0;
		if (data->event.key.keysym.sym == SDLK_RIGHT ||
			data->event.key.keysym.sym == SDLK_LEFT)
			data->player.rot = 0;
		if (data->event.key.keysym.sym == SDLK_SPACE)
			data->player.fire = 0;
	}
}

int			ft_handler(t_sdl *data)
{
	if (data->event.type == SDL_KEYDOWN)
	{
		if (data->event.key.keysym.sym == SDLK_UP)
			data->player.move = 1;
		else if (data->event.key.keysym.sym == SDLK_DOWN)
			data->player.move = -1;
		else if (data->event.key.keysym.sym == SDLK_RIGHT)
			data->player.rot = 1;
		else if (data->event.key.keysym.sym == SDLK_LEFT)
			data->player.rot = -1;
		else if (data->event.key.keysym.sym == SDLK_ESCAPE)
			return (close_sdl(data));
		if (data->event.key.keysym.sym == SDLK_SPACE)
			data->player.fire = 1;
	}
	else if (data->event.type == SDL_QUIT)
		return (close_sdl(data));
	ft_handler_up(data);
	return (1);
}
