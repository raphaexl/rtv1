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

t_camera		ft_camera_new(t_vector pos, t_vector rot, float fov)
{
	t_camera	cam;

	cam.pos = pos;
	cam.rot = rot;
	cam.dir = (t_vector){0, 0, -1.0};
	cam.up = (t_vector){0, -1.0, 0.0};
	/*cam.dir = ft_rotate_vec3(ft_vector(0, 0, -1.0), rot, 0);
	cam.up = ft_rotate_vec3(ft_vector(0, 1.0, 0), rot, 0);*/
	cam.ldir = ft_vector_cross(cam.dir, cam.up);
	cam.dist = 1.0f;
	cam.dir = ft_vector_normalized(cam.dir);
	return (cam);
}

t_vector		ft_camera_dir(t_camera *cam, int x, int y)
{
	t_vector	dir;
	t_vector	ppc;

	ppc = ft_vector_sum(cam->pos, ft_vector_kmult(PPD, cam->dir));
	dir = ft_vector_sub(ppc, ft_vector_kmult(x - W_W / 2.0, cam->ldir));
	dir = ft_vector_sum(dir, ft_vector_kmult(y - W_H / 2.0, cam->up));
	return (ft_vector_normalized(ft_vector_sub(dir, cam->pos)));
}
