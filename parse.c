/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 15:13:38 by sergee            #+#    #+#             */
/*   Updated: 2018/03/20 14:47:38 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void	parse_coordinate(int c, char **coord, t_map *map)
{
	int			x;
	static int	y;

	!map->col ? (map->col = c) &&
		(map->map = (int*)ft_memalloc(sizeof(int) * map->row * map->col)) : 0;
	map->col != c ?
		exit(write(1, "Found wrong line length. Exiting.\n", 34)) : 0;
	x = -1;
	while (coord[++x])
	{
		map->map[x + y * map->col] = ft_atoi(coord[x]);
		ft_memdel((void **)&coord[x]);
	}
	ft_memdel((void **)&coord);
	y++;
}

void		read_coordinate(int fd, char *av, t_map *map)
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
	close(fd);
	!map->row ? exit(ft_printf("No data found\n")) : close(fd);
	(fd = open(av, O_RDONLY)) == -1 ? exit(ft_printf("No file %s\n", av)) : 0;
	coord = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		coord = ft_strsplit(line, ' ');
		i = 0;
		while (coord[i])
			i++;
		parse_coordinate(i, coord, map);
		ft_memdel((void **)&line);
	}
	close(fd);
}
