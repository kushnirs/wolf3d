/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 21:58:17 by sergee            #+#    #+#             */
/*   Updated: 2018/04/24 16:08:14 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	fps(t_sdl *data)
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

void	toolbar(t_sdl *data)
{
	SDL_Rect dest;

	if (!data->weapon && !data->bar && !data->weapon_fire)
	{
		data->weapon = IMG_Load("picture/weapon.gif");
		SDL_SetColorKey(data->weapon, SDL_TRUE,
			SDL_MapRGB(data->weapon->format, 255, 255, 255));
		data->weapon_fire = IMG_Load("picture/weapon_fire.gif");
		SDL_SetColorKey(data->weapon_fire, SDL_TRUE,
			SDL_MapRGB(data->weapon_fire->format, 255, 255, 255));
		data->bar = IMG_Load("picture/toolbar.jpg");
		!data->weapon || !data->weapon_fire || !data->bar ?
			exit(ft_printf("IMG toolbar error\n")) : 0;
	}
	dest.w = WIDTH;
	dest.h = data->bar->h + 30;
	dest.y = HIGH - data->bar->h - 30;
	SDL_BlitScaled(data->bar, NULL, data->surface, &dest);
	dest.x = WIDTH / 2;
	dest.y = HIGH - data->weapon->h - data->bar->h - 30;
	if (data->player.fire)
		SDL_BlitSurface(data->weapon_fire, NULL, data->surface, &dest);
	SDL_BlitSurface(data->weapon, NULL, data->surface, &dest);
}

void	download_tex(t_sdl *data)
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
