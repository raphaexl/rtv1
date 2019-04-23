/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 07:01:12 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/23 18:52:56 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_camera		ft_camera_new(t_vector o, t_vector at, t_vector up, float a)
{
	t_camera	cam;

	cam.rot = (t_vector){0.0, 30.0, 0.0};
	cam.trans = (t_vector){0.0, 0.0, 0.0};
	cam.ratio = (float)W_W / (float)W_H;
	cam.pos = o;
	cam.fov = a;
	cam.look_at = at;
	cam.up = up;
	cam.h = tan(a / 2.0);
	cam.w = cam.ratio * cam.h;
	cam.dir = ft_vector_normalized(ft_vector_sub(at, o));
	cam.u = ft_vector_normalized(ft_vector_cross(cam.dir, cam.up));
	cam.v = ft_vector_cross(cam.u, cam.dir);
	cam.low_left = ft_vector_sub(cam.pos, ft_vector_sum(
				ft_vector_kmult(cam.h, cam.v), ft_vector_kmult(cam.w, cam.u)));
	cam.low_left = ft_vector_sum(cam.low_left, cam.dir);
	cam.horiz = ft_vector_kmult(2.0 * cam.w * (1.0 / (float)W_W), cam.u);
	cam.vert = ft_vector_kmult(2.0 * cam.h * (1.0 / (float)W_H), cam.v);
	return (cam);
}

t_vector		ft_camera_dir(t_camera cam, int x, int y)
{
	t_vector	dir;
	t_vector	tmp;
	t_vector	tmp_p;
	t_vector	tmp_pos;

	tmp = ft_vector_sum(cam.low_left, ft_vector_multk(cam.horiz, (float)x));
	tmp = ft_vector_sum(tmp, ft_vector_multk(cam.vert, (float)y));
//	dir = ft_vector_normalized(ft_vector_sub(tmp, cam.pos));
	dir = ft_vector_normalized(ft_vector_sub(tmp, cam.pos));
	/*tmp_pos = ft_translate_vec3(cam.pos, cam.trans, -1);*/
	dir = ft_rotate_vec3(dir, cam.rot, -1);
	//ft_vector_print(cam.rot);
   // tmp_p = ft_translate_vec3(tmp, cam.trans, -1);
//	tmp_p = ft_rotate_vec3(tmp, cam.rot, -1);
	dir = ft_vector_normalized(dir);
	return (dir);
}
