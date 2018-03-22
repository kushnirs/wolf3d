/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 15:13:38 by sergee            #+#    #+#             */
/*   Updated: 2018/03/22 19:43:31 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void	parse_wall(t_sdl *data, t_map *map)
{
	int	i;

	i = -1;
	while (++i < map->col)
		!map->map[i] || !map->map[i + (map->row - 1) * map->col] ?
			exit(ft_printf("Wall(c)=0\n")) : 0;
	i = -1;
	while (++i < map->row)
		!map->map[i * map->col] || !map->map[map->col - 1 + i * map->col] ?
			exit(ft_printf("Wall(r)=0\n")) : 0;
	(int)data->player.pos.x >= map->col || (int)data->player.pos.y >= map->row
	|| map->map[(int)data->player.pos.x + (int)data->player.pos.y * map->col] ?
		exit(ft_printf("Wrong player position\n")) : 0;
	data->player.pos.x < 0 ? exit(ft_printf("Negative position x\n")) : 0;
	data->player.pos.y < 0 ? exit(ft_printf("Negative position y\n")) : 0;
}

static void	parse_coordinate(t_sdl *data, int c, char **coord, t_map *map)
{
	int			x;
	static int	y;

	y && !map->col ? (map->col = c) &&
		(map->map = (int*)ft_memalloc(sizeof(int) * map->row * map->col)) : 0;
	y && map->col != c ?
		exit(write(1, "Found wrong line length. Exiting.\n", 34)) : 0;
	x = -1;
	while (coord[++x])
	{
		!y && c != 2 ? exit(ft_printf("Wrong player position\n")) : 0;
		!y && !x ? data->player.pos.x = ft_atoi(coord[x]) + 0.5 : 0;
		!y && x == 1 ? data->player.pos.y = ft_atoi(coord[x]) + 0.5 : 0;
		y && (int)ft_strlen(coord[x]) != ft_strpcmp("0123456", coord[x]) ?
			exit(ft_printf("Wrong symbol \n")) : 0;
		y && (map->map[x + (y - 1) * map->col] = ft_atoi(coord[x])) < 0 ?
			exit(ft_printf("Negative number'n")) : 0;
		ft_memdel((void **)&coord[x]);
	}
	ft_memdel((void **)&coord);
	y++;
}

void		read_coordinate(t_sdl *data, int fd, char *av, t_map *map)
{
	int		i;
	char	*line;
	char	**coord;

	line = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		ft_memdel((void **)&line);
		map->row++;
	}
	!map->row ? exit(ft_printf("No data found\n")) : close(fd);
	map->row < 4 ? exit(ft_printf("Wrong number of row\n")) : map->row--;
	(fd = open(av, O_RDONLY)) == -1 ? exit(ft_printf("No file %s\n", av)) : 0;
	coord = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		coord = ft_strsplit(line, ' ');
		i = 0;
		while (coord[i])
			i++;
		parse_coordinate(data, i, coord, map);
		ft_memdel((void **)&line);
	}
	parse_wall(data, map);
	close(fd);
}
