/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 07:01:12 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/25 20:11:27 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_camera		ft_camera_new(t_vector o, t_vector r, float z)
{
	t_camera	cam;

	cam.pos = o;
	cam.rot = r;
	cam.zoom = z;
//	cam.pos = ft_rotate_vec3(cam.pos, cam.rot, -1);
	return (cam);
}

t_ray	ft_camera_dir(t_camera *cam, int x, int y)
{
	t_ray	r;
	t_vector	tmp_p;
	t_vector	tmp_o;

	r.start = cam->pos;
	tmp_o = ft_rotate_vec3(cam->pos, cam->rot, -1);
	tmp_p = ft_rotate_vec3(tmp_p, cam->rot, -1);
	tmp_p = ft_vector((float)x - W_W / 2, (float)y - W_H / 2, -cam->zoom);
	//return (ft_vector_normalized(ft_vector_sub(tmp_p, tmp_o)));*/
	//r.dir = ft_vector_normalized(ft_vector_sub(tmp_p, tmp_o));
	r.dir = ft_vector_sub(tmp_p, tmp_o);
	return (r);
}
