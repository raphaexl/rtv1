/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 06:17:50 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/25 16:34:45 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H
# include "vector.h"

typedef struct	s_ray	t_ray;

typedef enum	e_mode
{
	RAYTRACE, PATH_TRACE
}				t_mode;

typedef	struct		s_camera
{
	t_vector	pos;
	t_vector	dir;
	t_mode		mode;
	t_vector	look_at;
	t_vector	right;
	t_vector	down;
	t_vector	rot;
	t_vector	trans;
}					t_camera;

t_camera		ft_camera_new(t_vector pos, t_vector rot, t_vector trans);
t_vector		ft_camera_dir(t_camera *cam, int x, int y);
#endif
