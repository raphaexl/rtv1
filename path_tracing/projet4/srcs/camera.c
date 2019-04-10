/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 07:01:12 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/08 20:38:23 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_vector		ft_point_at_parameter(t_ray *r, float t)
{
	return (ft_vector_sum(r->start, ft_vector_kmult(t, r->dir)));
}

t_camera		ft_camera_new(t_vector pos, t_vector rot, t_vector trans)
{
	t_camera	cam;

	cam.rot = rot;
	cam.trans = trans;
	cam.pos = pos;
	cam.look_at = (t_vector){0.0, 0.0, 0.0};
	cam.dir = ft_vector_normalized(ft_vector_sub(cam.look_at, pos));
	cam.right = ft_vector_normalized(ft_vector_cross(ft_vector(0, 1.0, 0), cam.dir));
	cam.down = ft_vector_cross(cam.right, cam.dir);
	return (cam);
}

t_vector		ft_camera_pos(t_camera cam)
{
	return (cam.pos);
}

t_vector		ft_camera_dir(t_camera cam, int x, int y)
{
	float		u;
	float		v;
	t_vector 	ll_corner = {-2.0, -1.0, -1.0};
	t_vector 	hz = {4.0, 0.0, 0.0};
	t_vector 	vt = {0.0, 2.0, 0.0};
	t_vector 	origin = {0.0, 0.0, 0.0};
	u = ((float)x + ft_rand48()) / (float)W_W;
	v = ((float)y + ft_rand48())/ (float)W_H;
	t_vector tmp;

	cam.pos = origin;
	tmp = ft_vector_sum(ft_vector_kmult(u, hz), ft_vector_kmult(v, vt));
	tmp = ft_vector_sum(tmp, ll_corner);
	return (tmp);
}
