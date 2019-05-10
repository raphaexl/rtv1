/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 08:43:45 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/10 18:14:15 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_sphere	ft_sphere(cl_float radius, t_vector pos, cl_int material)
{
	t_sphere s;

	s.pos.x = pos.x;
	s.pos.y = pos.y;
	s.pos.z = pos.z;
	s.radius = radius;
	s.material = material;
	return (s);
}

cl_int			ft_sphere_intersect(t_sphere *s, t_ray *r, cl_float *t)
{
	t_vector	dist;
	t_delta		d;
	cl_float 		t1;
	cl_float		t2;

	d.a = ft_vector_dot(r->dir, r->dir);
	dist = ft_vector_sub(r->start, s->pos);
	d.b = 2 * ft_vector_dot(r->dir, dist);
	d.c = ft_vector_dot(dist, dist) - (s->radius * s->radius);
	d.delta = d.b * d.b - 4 * d.a * d.c;
	if (d.delta < 0)
		return (0);
	d.delta = sqrt(d.delta);
	t1 = (-d.b + d.delta) / 2.0;
	t2 = (-d.b - d.delta) / 2.0;
	if (t1 > t2)
		t1 = t2;
	if ((t1 > 0.001) && (t1 < *t))
	{	
		*t = t1;
		return (1);	
	}
	return (0);
}
