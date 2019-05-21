/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 07:01:12 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/21 17:52:18 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_camera	ft_camera_new(t_vector eye, t_vector at, t_vector up, float a)
{
	t_camera	cam;

	cam.rot = (t_vector){0.0, 0.0, 0.0};
	cam.trans = (t_vector){0.0, 0.0, 0.0};
	cam.ratio = (float)W_W / (float)W_H;
	cam.pos = eye;
	cam.fov = a;
	cam.h = tan((cam.fov * M_PI * (1.0 / 180.0)) / 2.0);
	cam.w = cam.ratio * cam.h;
	cam.dir = ft_vector_normalized(ft_vector_sub(at, eye));
	cam.u = ft_vector_normalized(ft_vector_cross(cam.dir, up));
	cam.v = ft_vector_cross(cam.u, cam.dir);
	cam.low_left = ft_vector_sub(cam.pos, ft_vector_sum(ft_vector_kmult(cam.h,
					cam.v), ft_vector_kmult(cam.w, cam.u)));
	cam.low_left = ft_vector_sum(cam.low_left, cam.dir);
	cam.horiz = ft_vector_kmult(2.0 * cam.w, cam.u);
	cam.vert = ft_vector_kmult(2.0 * cam.h, cam.v);
	return (cam);
}

t_ray		ft_camera_ray(t_camera *cam, float x, float y)
{
	t_ray		r;
	t_vector	tmp;

	tmp = ft_vector_sum(cam->low_left, ft_vector_kmult((x + 0.5) / (float)W_W,
				cam->horiz));
	tmp = ft_vector_sum(tmp, ft_vector_kmult((y + 0.5) / (float)W_H,
				cam->vert));
	r.start = cam->pos;
	r.dir = ft_vector_normalized(ft_vector_sub(tmp, cam->pos));
	return (r);
}

void		ft_camera_transform(t_camera *cam)
{
	cam->pos = ft_translate_vec3(cam->pos, cam->trans, 0);
	cam->dir = ft_vector_normalized(ft_rotate_vec3(cam->dir, cam->rot, 0));
	cam->u = ft_vector_normalized(ft_vector_cross(cam->dir,
				ft_vector(0.0, 1.0, 0.0)));
	cam->v = ft_vector_cross(cam->u, cam->dir);
	cam->low_left = ft_vector_sub(cam->pos,
			ft_vector_sum(ft_vector_kmult(cam->h,
					cam->v), ft_vector_kmult(cam->w, cam->u)));
	cam->low_left = ft_vector_sum(cam->low_left, cam->dir);
	cam->horiz = ft_vector_kmult(2.0 * cam->w, cam->u);
	cam->vert = ft_vector_kmult(2.0 * cam->h, cam->v);
	cam->rot = (t_vector){0.0, 0.0, 0.0};
	cam->trans = (t_vector){0.0, 0.0, 0.0};
}
