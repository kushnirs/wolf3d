/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_cl.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 12:14:12 by sergee            #+#    #+#             */
/*   Updated: 2018/03/21 18:25:34 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_CL_H
# define WOLF_CL_H

# define WIDTH 1600
# define HIGH 1200

typedef struct			s_point
{
	float				x;
	float				y;
}						t_point;

typedef struct			s_wall
{
	int					w;
	int					h;
	unsigned int		wall[512 * 512];
}						t_wall;

#endif
