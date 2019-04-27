/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 17:51:42 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/27 21:16:22 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_object	*ft_sphere_new(void)
{
	t_object	*new;

	if ((new = (t_object *)malloc(sizeof (*new))))
	{
		new->type = SPHERE;
		new->pos = (t_vector){0.0, 0.0, 0.0};
		new->translate =(t_vector){0.0, 0.0, 0.0};
		new->rotate = (t_vector){0.0, 0.0, 0.0};
		new->normal = (t_vector){0.0, 0.0, 0.0};
		new->material = (t_material){{1.0, 1.0, 1.0}, {0, 0, 0}, 0, 0, 0, 0};
		new->radius = 1.0;
		new->angle = 0.0;
		new->next = NULL;
	}
	else
		ft_print_error("malloc error");
	return (new);
}

int			ft_sphere_compute(t_object *p, t_intersect *in)
{
	t_ray		r;
	t_vector	tmp;

	r = in->ray;
	r.start = ft_rotate_vec3(r.start, p->rotate, -1);
	r.dir = ft_rotate_vec3(r.dir, p->rotate, -1);
	r.start = ft_translate_vec3(in->ray.start, p->translate, -1);
	if (!ft_sphere_intersect(p, &r, &in->t))
		return (0);
	in->current = p;
	in->p = ft_vector_sum(in->ray.start, ft_vector_kmult(in->t, in->ray.dir));
	tmp = ft_vector_sub(in->p, p->pos);
	in->n = ft_normal_sphere(p, tmp);
	//in->n = ft_vector_kmult(1.0 / p->radius, tmp);
	return (1);
}

int			ft_sphere_intersect(t_object *s, t_ray *r, float *t)
{
	t_vector	dist;
	t_delta		d;
	float		t1;
	float		t2;

	d.a = ft_vector_dot(r->dir, r->dir);
	dist = ft_vector_sub(s->pos, r->start);
	d.b = 2.0 * ft_vector_dot(r->dir, dist);
	d.c = ft_vector_dot(dist, dist) - (s->radius * s->radius);
	d.delta = d.b * d.b - 4.0 * d.c * d.a;
	if (d.delta < 0.0001)
		return (0);
	d.delta = sqrt(d.delta);
	t1 = (d.b + d.delta) / (2.0 * d.a);
	t2 = (d.b - d.delta) / (2.0 * d.a);
	if (t1 > t2)
		t1 = t2;
	if ((t1 > 0.001) && (t1 < *t))
	{
		*t = t1;
		return (1);
	}
	return (0);
}
