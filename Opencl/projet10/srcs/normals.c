/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 11:33:09 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/05 16:32:32 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_vector	ft_normal_sphere(t_object *s, t_vector p)
{
	p = ft_rotate_vec3(p, s->rotate, -1);
	p = ft_translate_vec3(p, s->translate, -1);
	return (ft_vector_kmult(1.0 / s->radius, p));
}

t_vector	ft_normal_plane(t_object *plane, int ret)
{
	t_vector	p;

	if (ret == 1)
		p = plane->normal;
	else
		p = ft_vector_kmult(-1.0, plane->normal);
	p = ft_rotate_vec3(p, plane->rotate, -1);
    p = ft_translate_vec3(p, plane->translate, -1);
	return (ft_vector_normalized(p));
}

t_vector	ft_normal_cone(t_object *cone, t_vector p)
{
	if (p.y > 0)
		p.y = -sqrt(p.z * p.z + p.x * p.x) * tan(cone->angle);
	else
		p.y = sqrt(p.z * p.z + p.x * p.x) * tan(cone->angle);
	p = ft_rotate_vec3(p, cone->rotate, -1);
	p = ft_translate_vec3(p, cone->translate, -1);
	return (ft_vector_normalized(p));
}

t_vector	ft_normal_cylindre(t_object *cylindre, t_vector p)
{
	p = ft_rotate_vec3(p, cylindre->rotate, -1);
	p = ft_translate_vec3(p, cylindre->translate, -1);
	p = ft_vector_kmult(1.0 / cylindre->radius, p);
	return (ft_vector(p.x, 0.001, p.z));
}
