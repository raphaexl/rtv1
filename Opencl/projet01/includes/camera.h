/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 06:17:50 by ebatchas          #+#    #+#             */
/*   Updated: 2019/03/06 09:52:56 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H
# include "vector.h"

typedef struct	s_ray
{
	t_vector	start;
	t_vector	dir;
}		t_ray;

typedef struct	s_intersect
{
	t_ray		ray;
	t_ray		ray_light;
	double		t;
	t_vector	n;
	t_vector	p;
	int			id;
}				t_intersect;

typedef	struct		s_camera
{
	t_vector	start;
	t_vector	fd;
	t_vector	up;
	t_vector	rt;
	double		h;
	double		w;
}					t_camera;

t_camera		ft_camera_perspective(t_vector	o, t_vector t, t_vector up, double fov, double ratio);
t_ray			ft_camera_ray(t_vector point, t_camera cam);	

#endif
