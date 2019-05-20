/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 11:33:09 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/20 18:11:43 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_vector	ft_normal_sphere(t_object *s, t_vector p)
{
	return (ft_vector_kmult(1.0 / s->radius, p));
}

t_vector	ft_normal_plane(t_object *plane, int ret)
{
	t_vector	p;

	if (ret == 1)
		p = plane->normal;
	else
		p = ft_vector_kmult(-1.0, plane->normal);
	return (p);
}

t_vector	ft_normal_cone(t_object *cone, t_vector p)
{
	if (p.y > 0)
		p.y = -sqrt(p.z * p.z + p.x * p.x) * tan(cone->angle);
	else
		p.y = sqrt(p.z * p.z + p.x * p.x) * tan(cone->angle);
	return (ft_vector_normalized(p));
}

t_vector	ft_normal_cylindre(t_object *cylindre, t_vector p)
{
	p = ft_vector_kmult(1.0 / cylindre->radius, p);
	return (ft_vector(p.x, 0.001, p.z));
}

t_vector	ft_normal_box(t_object *b, t_vector h)
{
	t_vector	c;
	t_vector	d;
	t_vector	p;
	float		bias;

	bias = 1.00001;
	c = ft_vector_kmult(0.5, ft_vector_sum(b->pos, b->normal));
	d = ft_vector_kmult(0.5, ft_vector_sub(b->pos, b->normal));
	d.x = fabs(d.x) * bias;
	d.y = fabs(d.y) * bias;
	d.z = fabs(d.z) * bias;
	p = ft_vector_sub(h, c);
	return (ft_vector_normalized(ft_vector(p.x / d.x, p.y / d.y, p.z / d.z)));
}
