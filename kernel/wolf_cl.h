/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_cl.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 12:14:12 by sergee            #+#    #+#             */
/*   Updated: 2018/03/15 13:35:29 by sergee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_CL_H
# define WOLF_CL_H

# define WIDTH 1280
# define HIGH 1024

typedef struct			s_point
{
	float				x;
	float				y;
}						t_point;

// void					raycast(__global int *buff, __constant int *worldmap,
// 								t_player player, t_point plane);
#endif
