/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 21:58:17 by sergee            #+#    #+#             */
/*   Updated: 2018/03/15 15:12:40 by sergee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	fps(t_sdl *data)
{
	static t_ui	prev;
	static t_ui	fps;
	TTF_Font	*ttf;
	char		*fps_str;

	fps = 1000 / (SDL_GetTicks() - prev);
	prev = SDL_GetTicks();
	fps_str = ft_itoa(fps);
	data->fps = NULL;
	ttf = TTF_OpenFont("ARIAL.TTF", 22);
	data->fps = TTF_RenderText_Solid(ttf, fps_str,
		(SDL_Color){255, 255, 255, 255});
	SDL_BlitSurface(data->fps, NULL, data->surface, NULL);
	TTF_CloseFont(ttf);
	SDL_FreeSurface(data->fps);
	ft_memdel((void**)&fps_str);
}

int	ft_handler(t_sdl *data, t_map *map, t_player *player, t_point *pl)
{
	const t_point	p_p = player->pos;
	const t_point	p_d = player->dir;

	if (data->event.type == SDL_KEYDOWN)
	{
		if (data->event.key.keysym.sym == SDLK_UP)
		{
			!map->map[(int)(p_p.x + p_d.x * data->move) + (int)(p_p.y) * data->map.row] ?
				player->pos.x += p_d.x * data->move: 0;
			!map->map[(int)p_p.x + (int)(p_p.y + p_d.y * data->move) * data->map.row] ?
				player->pos.y += p_d.y * data->move : 0;
		}
		else if (data->event.key.keysym.sym == SDLK_DOWN)
		{
			!map->map[(int)(p_p.x - p_d.x * data->move) + (int)(p_p.y) * data->map.row] ?
				player->pos.x -= p_d.x * data->move: 0;
			!map->map[(int)(p_p.x) - (int)(p_p.y+ p_d.y * data->move) * data->map.row ] ?
				player->pos.y -= p_d.y * data->move : 0;
		}
		else if (data->event.key.keysym.sym == SDLK_RIGHT)
		{
			t_point	old_dir = {p_d.x, p_d.y};
			player->dir.x = p_d.x * cos(-data->rot) - p_d.y * sin(-data->rot);
			player->dir.y = old_dir.x * sin(-data->rot) + p_d.y * cos(-data->rot);
			t_point	old_pl = {pl->x, pl->y};
			pl->x = pl->x * cos(-data->rot) - pl->y * sin(-data->rot);
			pl->y = old_pl.x * sin(-data->rot) + pl->y * cos(-data->rot);
		}
		else if (data->event.key.keysym.sym == SDLK_LEFT)
		{
			t_point	old_dir = {p_d.x, p_d.y};
			player->dir.x = p_d.x * cos(data->rot) - p_d.y * sin(data->rot);
			player->dir.y = old_dir.x * sin(data->rot) + p_d.y * cos(data->rot);
			t_point	old_pl = {pl->x, pl->y};
			pl->x = pl->x * cos(data->rot) - pl->y * sin(data->rot);
			pl->y = old_pl.x * sin(data->rot) + pl->y * cos(data->rot);
		}
		else if (data->event.key.keysym.sym == SDLK_ESCAPE)
		{
			SDL_DestroyWindow(data->win);
			SDL_Quit();
			return (0);
		}			
	}
	return (1);
}
