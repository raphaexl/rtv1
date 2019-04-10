/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylindre.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 18:43:31 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/08 15:38:48 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int		ft_cylindre_compute(t_object *p, t_intersect *in)
{ 
	int		hit;
	t_ray	r;

	hit = 0;
	r = in->ray;
	r.start = ft_rotate_vec3(r.start, p->rotate, -1);
	r.dir = ft_rotate_vec3(r.dir, p->rotate, -1);
	r.start = ft_translate_vec3(r.start, p->translate, -1);
	if (ft_cylindre_intersect(p, &r, &in->t))
	{
		in->current = p;
		in->p = ft_vector_sum(in->ray.start, ft_vector_kmult(in->t, in->ray.dir));
		in->n = ft_normal_cylindre(p, ft_vector_sub(in->p, p->pos));
		hit = 1;
	}
	return (hit);
}

int		ft_cylindre_intersect(t_object *c, t_ray *r, float *t)
{
	t_delta		d;
	t_vector	dist;
	float		t1;
	float		t2;

	d.a = (r->dir.x * r->dir.x + r->dir.z * r->dir.z);
	dist = ft_vector_sub(r->start, c->pos);
	d.b = 2.0 * (dist.x * r->dir.x + dist.z * r->dir.z);
	d.c = (dist.x * dist.x + dist.z * dist.z) - c->radius * c->radius;
	d.delta = d.b * d.b - 4.0 * d.a * d.c;
	if (d.delta < 0.0)
		return (0);
	d.delta = sqrt(d.delta);
	t1 = (-d.b + d.delta) / (2.0 * d.a);
	t2 = (-d.b - d.delta) / (2.0 * d.a);
	if (t1 > t2)
		t1 = t2;
	if (t1 > 0.001 && t1 < *t)
	{
		*t = t1;
		return (1);
	}
	return (0);
}
