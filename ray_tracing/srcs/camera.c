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
	t_vector	tmp;
	t_vector	dir;
	float		u;
	float		v;

	u = ((x + 0.5) / W_W) * ((float) W_W / (float) W_H) - (((W_W - W_H) / (float)W_H) / 2.0);
	v = ((W_H - y) + 0.5) / (float)W_H;
	tmp = ft_vector_kmult(u - 0.5, cam.right); 
	tmp = ft_vector_sum(tmp, ft_vector_kmult(v - 0.5, cam.down));
	dir = ft_vector_normalized(ft_vector_sum(cam.dir, tmp));
	return (dir);
}
