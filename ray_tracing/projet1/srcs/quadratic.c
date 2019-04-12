/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadratic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 16:18:19 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/08 16:14:02 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"


t_quadratic		ft_quadratic_new(float a, float b, float c, float d, float e, float f, float g, float h, float i, float j)
{
	t_quadratic		q;

	q.a = a;
	q.b = b;
	q.c = c;
	q.d = d;
	q.e = e;
	q.f = f;
	q.g = g;
	q.h = h;
	q.i = i;
	q.j = j;
	return (q);
}

float	ft_intersection(t_quadratic	q, t_intersect *in, t_ray *r)
{
	t_delta		d;
	float		t;
	float 		t1;
	float		t2;
	t_vector	o;

	o = r->start;
	d.a = q.a * r->dir.x * r->dir.x + q.b * r->dir.y * r->dir.y + q.c * r->dir.z * r->dir.z
		+q.d * r->dir.x * r->dir.y + q.e * r->dir.x + r->dir.z + q.f * r->dir.y * r->dir.z;
	d.b = 2 * q.a * r->dir.x * o.x + 2 * q.b * r->dir.y * o.y + 2 * q.c * r->dir.z * o.z 
		+ q.d * (o.x * r->dir.y + o.y * r->dir.x) + q.e * (r->dir.z * o.x + r->dir.x * o.z)
		+ q.f * (o.y * r->dir.z + o.y * r->dir.y) + q.g * r->dir.x + q.h * r->dir.y + q.i * r->dir.z;
	d.c = q.a * o.x * o.x + q.b * o.y * o.y + q.c * o.z * o.z + q.d * o.x * o.y + q.e * o.x * o.z
		+ q.f * o.y * o.z + q.g * o.x + q.h * o.y + q.i * o.z + q.j;
	if (d.a == 0.0)
		t = -(d.a / d.b);
	else
	{
		d.delta = d.b * d.b - 4 * d.a * d.c;
		if (d.delta < 0)
			t = -1;
		else
		{
			d.delta = sqrt(d.delta);
			t1 = -d.b + d.delta;
			t2 = -d.b - d.delta;
			if (t1 < t2 && t1 > 0.0001)
				t = t1;
			else if (t2 < t1 && t2 > 0.0001)
				t = t2;
			else t = -1;
		}
	}
	in->p = ft_vector_sum(o, ft_vector_kmult(t, r->dir));
	in->n.x = 2 * q.a * in->p.x + q.d * in->p.y + q.e * in->p.z + q.g;
	in->n.y = 2 * q.b * in->p.y + q.d * in->p.x + q.f * in->p.z + q.h;
	in->n.z = 2 * q.c * in->p.z + q.e * in->p.x + q.f * in->p.y + q.i;
	if (ft_vector_dot(in->n, r->dir) > 0.0)
		in->n = (ft_vector_kmult(-1, in->n));
	return (t);
}
