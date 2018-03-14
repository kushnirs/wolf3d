/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergee <sergee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 12:14:12 by sergee            #+#    #+#             */
/*   Updated: 2018/03/14 13:56:57 by sergee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CL_H
# define CL_H

# define WIDTH 1280
# define HIGH 1024
typedef struct			s_point
{
	float				x;
	float				y;
}						t_point;

typedef struct			s_player
{
	t_point				pos;
	t_point				dir;
}						t_player;

#endif
