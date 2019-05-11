/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 06:17:50 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/10 20:28:13 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# define PPD 925
# define FOV 60.0
# define FOV_H 30
# include "vector.h"

typedef	struct	s_camera
{
	cl_float	ratio;
	cl_float	fov;
	cl_float	h;
	cl_float	w;
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
}				t_camera;

#endif