/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 06:39:09 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/19 19:13:33 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_plane		ft_plane(t_vector pos, t_vector norm, t_material material)
{
	t_plane		plane;

	plane.pos = pos;
	plane.normal = norm;
	plane.material = material;
	return (plane);
}

int			ft_plane_compute(t_object *p, t_intersect *in)
{
	int		hit;
	t_ray	r;

	hit = 0;
	r = in->ray;
	r.start = ft_rotate_vec3(r.start, p->rotate, -1);
	r.dir = ft_rotate_vec3(r.dir, p->rotate, -1);
	r.start = ft_translate_vec3(r.start, p->translate, -1);
	if (ft_plane_intersect(p, &r, &in->t))
	{
		in->current = p;
		in->p = ft_vector_sum(in->ray.start, ft_vector_kmult(in->t, in->ray.dir));
		//in->n = ft_vector_normalized(p->normal);
			in->n = ft_normal_plane(p, ft_vector_sub(in->p, p->pos));
		hit = 1;
	}
	return (hit);
}

int			ft_plane_intersect(t_object *plane, t_ray *r, float *t)
{
	float		ddn;
	t_vector	dist;
	float		t1;

	ddn = ft_vector_dot(r->dir, plane->normal);
	if (ddn == 0.000001)
		return (0);
	dist = ft_vector_sub(r->start, plane->pos);
	t1 = (-ft_vector_dot(dist, plane->normal)) / ddn;
	if (t1 < 0.001 || t1 > *t)
		return (0);
	*t = t1;
	/*if (ddn > 0)
	  plane->normal = ft_vector_kmult(-1, plane->normal);*/
	return (1);
}
/*
   int			ft_plane_intersect(t_object *plane, t_ray *r, float *t)
   {
   float		ddn;
   t_vector	dist;
   float		t1;

   ddn = ft_vector_dot(r->dir, plane->normal);
//	if (ddn == 0.000001)
//		return (0);
dist = ft_vector_sub(r->start, plane->pos);
//	t1 = (-ft_vector_dot(dist, plane->normal)) / ddn;
t1 = (-dist.y / r->dir.y);
if (r->dir.y == 0.00)
return (0);
if (t1 < 0.001 || t1 > *t)
return (0);
 *t = t1;
 if (ddn > 0)
 plane->normal = ft_vector_kmult(-1, plane->normal);
 if (r->dir.y == 0.00)
 return (0);
 return (1);
 }*/
