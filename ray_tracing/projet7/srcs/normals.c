/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 11:33:09 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/22 21:40:44 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_vector ft_normal_sphere(t_object *s, t_vector p)
{
	p = ft_rotate_vec3(p, s->rotate, -1);
	p = ft_translate_vec3(p, s->translate, -1);
	return (ft_vector_normalized(p));
}

t_vector ft_normal_plane(t_object *plane, t_vector p)
{
	p = ft_rotate_vec3(plane->normal, plane->rotate, -1);
	return (ft_vector(0, 0, 1.0));
}

t_vector ft_normal_cone(t_object *cone, t_vector p)
{
	t_vector	res;

	p = ft_rotate_vec3(p, cone->rotate, -1);
	p = ft_translate_vec3(p, cone->translate, -1);
	/*if (p.x > 0)
		res.x = -sqrt(p.z * p.z + p.x * p.x) * tan(cone->angle);
	else
		res.x = sqrt(p.z * p.z + p.x * p.x) * tan(cone->angle);
	res.y = p.y;
	res.z = p.z;*/
	p.y = 0.01;
	//res = ft_rotate_vec3(res, cone->rotate, 0);
	//return (ft_vector_normalized(ft_vector(res.x,  res.y,  res.z)));
	return (ft_vector_normalized(p));
}

t_vector ft_normal_cylindre(t_object *cylindre, t_vector p)
{
	p = ft_rotate_vec3(p, cylindre->rotate, -1);
	p = ft_translate_vec3(p, cylindre->translate, -1);
	return (ft_vector_normalized(ft_vector(p.x,  0.0,  p.z)));
}
