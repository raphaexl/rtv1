/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 11:55:38 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/22 20:43:39 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include <math.h>
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif
# define MAX_DEPTH 5
# define NB_OPTIONS 25
# define DELTA_TRANS 1.5
# define DELTA_SCALE 1.0
# define DELTA_ANGLE 2
# define DEG_TO_RAD(x) ((x) * (M_PI / 180.0))
# define EQN_EPS 1e-9
# define IS_ZERO(x) ((x) > -EQN_EPS && (x) < EQN_EPS)
# ifndef CBRT
#  define POW1(x) (pow((double)(x), 1.0 / 3.0))
#  define POW2(x) (pow((double)-(x), 1.0 / 3.0))
#  define CBRT(x) ((x) > 0.0 ? POW1(x) : ((x) < 0.0 ? -POW2(x) : 0.0))
# endif

typedef struct	s_point
{
	int		x;
	int		y;
}				t_point;

typedef struct	s_delta
{
	float	a;
	float	b;
	float	c;
	float	delta;
}				t_delta;

typedef struct	s_cubic
{
	double	a;
	double	b;
	double	c;
	double	d;
	double	sq_a;
	double	p;
	double	q;
	double	cb_p;
}				t_cubic;

typedef struct	s_quartic
{
	double	a;
	double	b;
	double	c;
	double	d;
	double	z;
	double	u;
	double	v;
	double	sub;
	double	sq_a;
	double	p;
	double	q;
	double	r;
}				t_quartic;

typedef	enum	e_opt
{
	NNE = 0, NEW_SPHERE, NEW_CONE, NEW_CYLINDRE, NEW_BOX, NEW_PLANE, NEW_DISK,
	NEW_TORUS, NEW_CUBE, EDIT_TRACE, RAY_TRACE, PATH_TRACE, ZOOM, MOVE_X,
	MOVE_Z, MOVE_Y, ROTATE_X, ROTATE_Z, ROTATE_Y, SCALE_X, SCALE_Z, SCALE_Y,
	RESIZE, SAVE, DELETE
}				t_options;

typedef	struct	s_font
{
	char		*mes;
	char		*file;
	int			size;
}				t_font;
#endif
