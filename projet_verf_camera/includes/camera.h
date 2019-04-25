/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 06:17:50 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/25 18:38:31 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H
# include "vector.h"

typedef struct	s_ray	t_ray;

typedef enum	e_mode
{
	RAY_TRACE, PATH_TRACE
}				t_mode;

typedef	struct	s_camera
{
	t_vector	pos;
	t_vector	rot;
	float		zoom;
}				t_camera;

t_camera		ft_camera_new(t_vector o, t_vector r, float zoom);
t_ray		ft_camera_dir(t_camera *cam, int x, int y);
#endif
