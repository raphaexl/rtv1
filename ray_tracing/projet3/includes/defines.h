/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 11:55:38 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/20 17:07:21 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H
# define M_I_PI 1.0 / M_PI
# define DEG_TO_RAD(x) ((x) * (M_PI / 180.0))
# include "color.h"

typedef struct		s_point
{
	int		x;
	int		y;
}					t_point;

typedef	struct		s_vect2d
{
	float	x;
	float	y;
}					t_vect2d;


typedef	enum	s_options
{
	NNE = 0, DIFFUSE, SPECULAR, AMBIANT, REFLECTION, REFRACTION, SHADOW, RAYTRACE, CLEAR,
	ZOOM_OUT, ZOOM_IN, MOVE_LEFT, MOVE_RIGHT, MOVE_UP, MOVE_DOWN, ROTATE_X, ROTATE_Y, ROTATE_Z
}				t_options;

typedef	struct		s_font
{
	char	*mes;
	char	*file;
	int		size;
}					t_font;
# endif
