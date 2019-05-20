/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 11:55:38 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/20 20:05:29 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include <math.h>

# define MAX_DEPTH 5
# define NB_OPTIONS 20
# define DELTA_TRANS 1.5
# define DELTA_ANGLE 2
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
	NNE = 0, NEW_SPHERE, NEW_CONE, NEW_CYLINDRE, NEW_BOX, NEW_PLANE, NEW_DISK,
	EDIT_TRACE, RAY_TRACE, PATH_TRACE, ZOOM, MOVE_X, MOVE_Z,
	MOVE_Y, ROTATE_X, ROTATE_Z, ROTATE_Y, SCALE, SAVE, DELETE
}				t_options;

typedef	struct	s_font
{
	char		*mes;
	char		*file;
	int			size;
}				t_font;
#endif
