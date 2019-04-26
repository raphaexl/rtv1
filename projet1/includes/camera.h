/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 06:17:50 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/25 20:33:33 by ebatchas         ###   ########.fr       */
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
	RAYTRACE, PATH_TRACE
}				t_mode;

typedef	struct		s_camera
{
	t_vector	pos;
	t_vector	dir;
        t_vector	ldir;
	t_vector	up;
	float		dist;
	float       	fov;
	t_vector	rot;
	t_vector	trans;
}					t_camera;

t_camera		ft_camera_new(t_vector pos, t_vector rt, float fov);
t_vector		ft_camera_dir(t_camera *cam, int x, int y);
#endif
