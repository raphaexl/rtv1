/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 11:55:38 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/27 21:31:52 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include <math.h>

# define MAX_DEPTH 5
# define MAX_DISTANCE 1000.0f
# define RAND_N 3
# define DELTA_TRANS 0.5
# define DELTA_ANGLE 10
# define DEG_TO_RAD(x) ((x) * (M_PI / 180.0))

typedef struct	s_point
{
	int		x;
	int		y;
}				t_point;

typedef	struct	s_vect2d
{
	float	x;
	float	y;
}				t_vect2d;

typedef struct	s_delta
{
	float	a;
	float	b;
	float	c;
	float	delta;
}				t_delta;

typedef	enum	e_opt
{
	NNE = 0, ZOOM, MOVE_X, MOVE_Z, MOVE_Y, ROTATE_X, ROTATE_Z, ROTATE_Y
}				t_options;

typedef	struct	s_font
{
	char		*mes;
	char		*file;
	int			size;
}				t_font;
#endif
