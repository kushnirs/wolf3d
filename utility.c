/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 21:58:17 by sergee            #+#    #+#             */
/*   Updated: 2018/03/19 13:48:20 by sergee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static int	close_sdl(t_sdl *data)
{
	SDL_DestroyWindow(data->win);
	SDL_Quit();
	return (0);
}

void	vsync(void)
{
	static t_ui	prev;
	static t_ui	fps;

	fps = SDL_GetTicks() - prev;
	if (17 > fps)
		SDL_Delay(17 - fps);
}

void	fps(t_sdl *data)
{
	static t_ui	prev;
	static t_ui	fps;
	static t_ui	t_p;
	t_ui		t;
	TTF_Font	*ttf;
	char		*fps_str;

	t = time(NULL);
	if (t - t_p)
		fps = (SDL_GetTicks() - prev);
	t_p = t;
	prev = SDL_GetTicks();
	fps_str = ft_itoa(1000 / fps);
	data->fps = NULL;
	ttf = TTF_OpenFont("ARIAL.TTF", 22);
	data->fps = TTF_RenderText_Solid(ttf, fps_str,
		(SDL_Color){255, 255, 255, 255});
	SDL_BlitSurface(data->fps, NULL, data->surface, NULL);
	TTF_CloseFont(ttf);
	SDL_FreeSurface(data->fps);
	ft_memdel((void**)&fps_str);
}

void move(t_map *map, t_player *p, t_point *pl)
{
	const t_point	old_pl = {pl->x, pl->y};
	const t_point	old_dir = {p->dir.x, p->dir.y};

	if (p->move)
	{
		!map->map[(int)(p->pos.x + p->dir.x * p->m_s * p->move) + 
			(int)p->pos.y * map->row] ? p->pos.x +=
				p->dir.x * p->m_s * p->move : 0;
		!map->map[(int)p->pos.x + (int)(p->pos.y + p->dir.y * p->m_s * p->move)
			* map->row] ? p->pos.y +=
				p->dir.y * p->m_s * p->move : 0;
	}
	if (p->rot)
	{
		p->dir.x = p->dir.x * cos(p->r_s * p->rot) -
				p->dir.y * sin(p->r_s * p->rot);
		p->dir.y = old_dir.x * sin(p->r_s * p->rot) +
				p->dir.y * cos(p->r_s * p->rot);
		pl->x = pl->x * cos(p->r_s * p->rot) - pl->y * sin(p->r_s * p->rot);
		pl->y = old_pl.x * sin(p->r_s * p->rot) + pl->y * cos(p->r_s * p->rot);
	}
}

int	ft_handler(t_sdl *data)
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
	return (1);
}
