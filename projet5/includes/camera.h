/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 06:17:50 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/27 17:28:35 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# define PPD 925
# define FOV 60.0
# define FOV_H 30
# include "vector.h"

typedef struct	s_ray	t_ray;

typedef enum	e_mode
{
	EDIT, RAYTRACE, PATH_TRACE
}				t_mode;

typedef	struct		s_camera
{
	t_vector	pos;
	t_vector	rot;
	t_vector	trans;
	t_vector	look_at;
	t_vector	dir;
	t_vector	up;
	t_vector	u;
	t_vector	v;
	t_vector	horiz;
	t_vector	vert;
	t_vector	low_left;
	float		ratio;
	float		fov;
	float		h;
	float		w;
}					t_camera;

t_camera		ft_camera_new(t_vector eye, t_vector look_at, t_vector up, float a);
t_ray		ft_camera_ray(t_camera *cam, float x, float y);
void		ft_camera_transform(t_camera *cam);
#endif
