/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 07:01:12 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/25 20:57:59 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_vector		ft_point_at_parameter(t_ray *r, float t)
{
	return (ft_vector_sum(r->start, ft_vector_kmult(t, r->dir)));
}

t_camera		ft_camera_new(t_vector pos, t_vector at, float fov)
{
	t_camera	cam;
	t_vector	temp1;
	t_vector	temp2;

	cam.pos = pos;
	cam.at = at;
	cam.dir = ft_vector_normalized(ft_vector_sub(at, pos));
	cam.rt = ft_vector_cross(ft_vector(0.0f, 1.0f, 0.0), cam.dir);
	cam.up = ft_vector_cross(cam.dir, cam.rt);
	cam.dist = 1.0f;
	cam.h = tan(fov / 2.0);
	cam.w = cam.h * (float)W_W / (float)W_H;
	temp1 = ft_vector_sum(ft_vector_multk(cam.dir, cam.dist), ft_vector_multk(cam.up, cam.h / 2.0));
	temp2 = ft_vector_sub(temp1, ft_vector_multk(cam.rt, cam.w / 2.0));
	cam.up_left = ft_vector_sum(pos, temp2);
	return (cam);
}

t_vector		ft_camera_dir(t_camera *cam, int x, int y)
{
	float 		x_indent;
	float		y_indent;
	t_vector	temp1;
	t_vector	temp2;

	x_indent = cam->w / (float)W_W;
	y_indent = cam->h / (float)W_H;
	temp1 = ft_vector_kmult(x_indent * (float)x, cam->rt);
	temp2 = ft_vector_kmult(y_indent * (float)y, cam->up);
	temp1 = ft_vector_sub(temp1, temp2);
	temp2 = ft_vector_sum(temp1, cam->up_left);
	return (ft_vector_normalized(ft_vector_sub(temp2, cam->pos)));
}
