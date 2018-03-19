/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_cl.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 12:14:12 by sergee            #+#    #+#             */
/*   Updated: 2018/03/19 16:55:28 by sergee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_CL_H
# define WOLF_CL_H

# define WIDTH 1280
# define HIGH 1024
# define T_W 512
# define T_H 512

typedef struct			s_point
{
	float				x;
	float				y;
}						t_point;

typedef struct			s_wall
{
	unsigned int		w[T_W * T_H];
}						t_wall;

// void					raycast(__global int *buff, __constant int *worldmap,
// 								t_player player, t_point plane);
#endif
