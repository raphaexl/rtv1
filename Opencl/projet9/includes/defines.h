/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 11:55:38 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/10 20:29:01 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include <math.h>

# ifdef __APPLE__
# include <OpenCL/opencl.h>
# else
# include <CL/cl.h>
#endif
# define MAX_DEPTH 5
# define MAX_DISTANCE 1000.0f
# define NB_OPTIONS 12
# define RAND_N 3
# define DELTA_TRANS 0.5
# define DELTA_ANGLE 2
# define MAX_SOURCE_SIZE 0x1000000
# define DEG_TO_RAD(x) ((x) * (M_PI / 180.0))

typedef struct	s_point
{
	cl_int		x;
	cl_int		y;
}				t_point;

typedef	struct	s_vect2d
{
	cl_float	x;
	cl_float	y;
}				t_vect2d;

typedef struct	s_delta
{
	cl_float	a;
	cl_float	b;
	cl_float	c;
	cl_float	delta;
}				t_delta;

typedef	enum	e_opt
{
	NNE = 0, NEW, EDIT_TRACE, RAY_TRACE, PATH_TRACE, ZOOM, MOVE_X, MOVE_Z,
	MOVE_Y, ROTATE_X, ROTATE_Z, ROTATE_Y
}				t_options;

typedef	struct	s_font
{
	char		*mes;
	char		*file;
	int			size;
}				t_font;
#endif
