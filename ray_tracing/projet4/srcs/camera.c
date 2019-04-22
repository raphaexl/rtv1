/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 07:01:12 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/22 15:34:12 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_vector		ft_point_at_parameter(t_ray *r, float t)
{
	return (ft_vector_sum(r->start, ft_vector_kmult(t, r->dir)));
}

t_camera		ft_camera_new(t_vector o, t_vector r, t_vector t, float a)
{
	t_camera	cam;

	cam.rot = r;
	cam.trans = t;
	cam.cam_space = (t_vector){0.0, 0.0, 0.0};
	cam.ratio = (float)W_W / (float)W_H;
	cam.pos = o;
	//cam.pos.z = 10.0;
	cam.fov = a;
	cam.ndcw = 0.0;
	cam.ndch = 0.0;
	cam.screen = (t_vect2d){(float)W_W, (float)W_H};
	return (cam);
}

t_vector		ft_camera_pos(t_camera cam)
{
	return (cam.pos);
}

t_vector		ft_camera_dir(t_camera cam, int x, int y)
{
	t_vector	pix_cam;
	t_vect2d	pix_scr;
	t_vector	dir;
	t_vector	tmp_pos;
	t_vector	tmp_p;

	cam.ndcw = ((float)x + 0.5 /*+ ft_rand48()*/) / cam.screen.x;
	cam.ndch = ((float)y + 0.5 /*+ ft_rand48()*/) / cam.screen.y;
	pix_cam.z = -1.0;
	pix_scr.x = 2.0 * cam.ndcw -1.0;
	pix_scr.y = -(2.0 * cam.ndch - 1.0);
	pix_cam.x = pix_scr.x * cam.ratio * tan(cam.fov / 2.0); 
	pix_cam.y = pix_scr.y * tan(cam.fov / 2.0);
	tmp_pos = ft_translate_vec3(cam.pos, cam.trans, -1);
	tmp_pos = ft_rotate_vec3(tmp_pos, cam.rot, -1);
	//pix_cam = ft_translate_vec3(pix_cam, cam.trans, -1);
	tmp_p = ft_rotate_vec3(pix_cam, cam.rot, -1);
	//ft_vector_print(cam.rot);
	tmp_p = ft_translate_vec3(tmp_p, cam.trans, -1);
	dir = ft_vector_normalized(ft_vector_sub(tmp_p, tmp_pos));
	return (dir);
}
