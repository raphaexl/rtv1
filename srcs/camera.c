/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 07:01:12 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/24 18:05:19 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_camera		ft_camera_new(t_vector o, t_vector r, t_vector t, float a)
{
	t_camera	cam;

	cam.rot = r;
	cam.trans = t;
	cam.cam_space = (t_vector){0.0, 0.0, 0.0};
	cam.ratio = (float)W_W / (float)W_H;
	cam.pos = o;
	cam.fov = a;
	cam.ndcw = 0.0;
	cam.ndch = 0.0;
	cam.pos = ft_rotate_vec3(cam.pos, cam.rot, -1);
	cam.pos = ft_translate_vec3(cam.pos, cam.trans, -1);
	return (cam);
}

t_vector		ft_camera_dir(t_camera cam, int x, int y)
{
	t_vector	pix_cam;
	t_vect2d	pix_scr;
	t_vector	tmp_o;
	t_vector	tmp_p;

	cam.ndcw = ((float)x + 0.5) / (float)W_W;
	cam.ndch = ((float)y + 0.5) / (float)W_H;
	pix_cam.z = -1.0;
	pix_scr.x = 2.0 * cam.ndcw - 1.0;
	pix_scr.y = -(2.0 * cam.ndch - 1.0);
	pix_cam.x = pix_scr.x * cam.ratio * tan(cam.fov / 2.0);
	pix_cam.y = pix_scr.y * tan(cam.fov / 2.0);
	tmp_o = ft_rotate_vec3(cam.pos, cam.rot, -1);
	tmp_p = ft_rotate_vec3(pix_cam, cam.rot, -1);
	tmp_o = ft_translate_vec3(tmp_o, cam.trans, -1);
	return (ft_vector_normalized(ft_vector_sub(tmp_p, tmp_o)));
}
