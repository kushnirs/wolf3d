/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 21:58:17 by sergee            #+#    #+#             */
/*   Updated: 2018/03/22 00:31:02 by sergee           ###   ########.fr       */
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

void		fps(t_sdl *data)
{
	static t_ui	prev;
	static t_ui	fps;
	static t_ui	t_p;
	t_ui		t;
	char		*fps_str;

	t = time(NULL);
	if (t - t_p)
		fps = (SDL_GetTicks() - prev);
	t_p = t;
	prev = SDL_GetTicks();
	fps_str = ft_itoa(1000 / fps);
	data->fps = NULL;
	data->ttf = TTF_OpenFont("ARIAL.TTF", 22);
	data->fps = TTF_RenderText_Solid(data->ttf, fps_str,
		(SDL_Color){255, 255, 255, 255});
	SDL_BlitSurface(data->fps, NULL, data->surface, NULL);
	TTF_CloseFont(data->ttf);
	SDL_FreeSurface(data->fps);
	ft_memdel((void**)&fps_str);
}

void		move(t_map *map, t_player *p)
{
	float	w;
	float	x;
	float	y;

	w = p->dir.x > 0 ? 0.2 : -0.2;
	x = p->pos.x + p->dir.x * p->m_s * p->move + w + (int)p->pos.y * map->col;
	!map->map[(int)(x)] ? p->pos.x += p->dir.x * p->m_s * p->move : 0;
	w = p->dir.y > 0 ? 0.2 : -0.2;
	y = p->pos.x + (int)(p->pos.y + w + p->dir.y * p->m_s * p->move)* map->col;
	!map->map[(int)(y)] ? p->pos.y +=	p->dir.y * p->m_s * p->move : 0;
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
	}
	else if (data->event.type == SDL_KEYUP)
	{
		if (data->event.key.keysym.sym == SDLK_UP ||
			data->event.key.keysym.sym == SDLK_DOWN)
			data->player.move = 0;
		if (data->event.key.keysym.sym == SDLK_RIGHT ||
			data->event.key.keysym.sym == SDLK_LEFT)
			data->player.rot = 0;
	}
	else if (data->event.type == SDL_QUIT)
		return (close_sdl(data));
	return (1);
}
