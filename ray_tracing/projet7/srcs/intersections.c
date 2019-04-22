/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 11:11:48 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/22 22:22:40 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

static	float	ft_min_ray(float t1, float t2)
{
	if ((t1 < t2 || t2 < 0) && t1 > 0)
		return (t1);
	else if ((t2 < t1 || t1 < 0) && t2 > 0)
		return (t2);
	else
		return (-1.0);
}

float			ft_intersection_sphere(t_object *s, t_ray *r)
{
	t_delta		d;
	t_vector	dist;
	float		t;

	dist = ft_vector_sub(r->start, s->pos);
	d.a = ft_vector_dot(r->dir, r->dir);
	d.b = 2 * ft_vector_dot(dist, r->dir);
	d.c = ft_vector_dot(dist, dist) - s->radius * s->radius;
	d.delta = d.b * d.b - 4 * d.a * d.c;
	if (d.delta < 0)
		t = -1.0;
	else
		t = ft_min_ray((-d.b - sqrt(d.delta)) / (2.0 * d.a),
					((-d.b + sqrt(d.delta)) / (2.0 * d.a)));
	return (t);
}

float			ft_intersection_plane(t_object *p, t_ray *r)
{
	float		t;
	t_vector	dist;

	dist = ft_vector_sub(r->start, p->pos);
	if (r->dir.y == 0)
		t = -1.0;
	else
		t = (-dist.y / (r->dir.y));
	return (t);
}

float			ft_intersection_cone(t_object *c, t_ray *r)
{
	t_delta		d;
	t_vector	dist;
	float		anglesin;
	float		anglecos;

	anglecos = pow(cos(c->angle), 2);
	anglesin = pow(sin(c->angle), 2);
	dist = ft_vector_sub(r->start, c->pos);
	d.a = anglecos * (r->dir.z * r->dir.z + r->dir.y * r->dir.y)
		- anglesin * (r->dir.x * r->dir.x);
	d.b = 2 * (anglecos * (dist.z * r->dir.z + dist.y * r->dir.y)
			- anglesin * (dist.x * r->dir.x));
	d.c = anglecos * (dist.z * dist.z + dist.y * dist.y)
		- anglesin * (dist.x * dist.x);
	d.delta = d.b * d.b - 4 * d.a * d.c;
	if (d.delta < 0)
		return (-1.0);
	else
		return (ft_min_ray(-d.b - sqrt(d.delta) / (2.0 * d.a),
					(-d.b + sqrt(d.delta) / (2.0 * d.a))));
}

float			ft_intersection_cylindre(t_object *c, t_ray *r)
{
	t_delta		d;
	t_vector	dist;
	float		t;

	d.a = (r->dir.z * r->dir.z + r->dir.y * r->dir.y);
	dist = ft_vector_sub(r->start, c->pos);
	d.b = 2 * (dist.z * r->dir.z + dist.y * r->dir.y);
	d.c = (dist.z * dist.z + dist.y * dist.y) - c->radius * c->radius;
	d.delta = d.b * d.b - 4 * d.a * d.c;
	if (d.delta < 0)
		t = -1.0;
	else
		t = ft_min_ray(-d.b - sqrt(d.delta) / (2.0 * d.a),
					(-d.b + sqrt(d.delta) / (2.0 * d.a)));
	return (t);
}
