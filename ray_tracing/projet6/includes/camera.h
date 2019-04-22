/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 06:17:50 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/22 13:15:44 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H
# include "vector.h"

typedef struct	s_ray	t_ray;

typedef struct	s_ray
{
	t_vector	start;
	t_vector	dir;
	t_vector	(*ft_point_at_parameter)(float);
	int			x;
	int			y;
}		t_ray;


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
t_vector		ft_camera_dir(t_camera cam, int x, int y);
t_vector		ft_camer_pos(t_camera cam);

#endif
