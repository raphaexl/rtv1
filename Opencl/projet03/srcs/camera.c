/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 07:01:12 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/10 18:11:39 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/camera.h"

t_camera		ft_camera_perspective(t_vector	o, t_vector t, t_vector up, cl_float fov, cl_float ratio)
{
	t_camera	cam;

	cam.start = o;
	/*cam.fd = ft_vector_normalized(ft_vector_sub(t, o));
	cam.rt = ft_vector_normalized(ft_vector_cross(cam.fd, up));*/
	cam.fd = ft_vector_sub(t, o);
	cam.rt = ft_vector_cross(cam.fd, up);
	cam.up = ft_vector_cross(cam.rt, cam.fd);
	cam.h = tan(fov);
	cam.w = cam.h * ratio;
	return (cam);
}

t_ray			ft_camera_ray(t_vector point, t_camera cam)
{
	t_vector	h1;
	t_vector	h2;
	t_ray		ray;

	h1 = ft_vector_kmult(point.x * cam.w, cam.rt);
	h2 = ft_vector_sum(ft_vector_kmult(point.y * cam.h, cam.up), h1);
	ray.start = cam.start;
	ray.dir = ft_vector_normalized(ft_vector_sum(cam.fd, h2));
	return (ray);
}	
