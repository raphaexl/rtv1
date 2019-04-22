/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 07:01:12 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/22 13:22:08 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_vector		ft_point_at_parameter(t_ray *r, float t)
{
	return (ft_vector_sum(r->start, ft_vector_kmult(t, r->dir)));
}

t_camera		ft_camera_new(t_vector eye, t_vector look_at, t_vector up, float a)
{
	t_camera	cam;

	cam.rot = (t_vector){0.0, 0.0, 0.0};
	cam.trans = (t_vector){0.0, 0.0, 0.0};
	cam.ratio = (float)W_W / (float)W_H;
	cam.pos = eye;
	cam.fov = a;
	cam.look_at = look_at;
	cam.up = up;
	cam.dir = ft_vector_normalized(ft_vector_sub(look_at, eye));
	cam.u = ft_vector_normalized(ft_vector_cross(up, cam.dir));
	cam.v = ft_vector_cross(cam.dir, cam.u);
	cam.w = tan(a / 2.0);
	cam.h = cam.ratio * cam.w;
	cam.low_left = ft_vector_sub(cam.pos, ft_vector_sum(ft_vector_kmult(cam.h, cam.v), ft_vector_kmult(cam.w, cam.u)));
	cam.horiz = ft_vector_kmult(2.0 * cam.w, cam.u);
	cam.vert = ft_vector_kmult(2.0 * cam.h, cam.v);
	return (cam);
}

t_vector		ft_camera_pos(t_camera cam)
{
	return (cam.pos);
}

t_vector		ft_camera_dir(t_camera cam, int x, int y)
{
	t_vector	dir;
	t_vector	tmp;

	tmp = ft_vector_sum(cam.low_left, ft_vector_multk(cam.horiz, (float)x));
	tmp = ft_vector_sum(tmp, ft_vector_multk(cam.vert, (float)y));
	dir = ft_vector_normalized(ft_vector_sub(tmp, cam.pos));
	return (dir);
}
