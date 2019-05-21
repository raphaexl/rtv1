/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disque.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 19:13:22 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/20 17:36:08 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_object	*ft_disk_new(void)
{
	t_object	*new;

	if ((new = (t_object *)malloc(sizeof(*new))))
	{
		new->type = DISK;
		new->name = "DISK";
		new->pos = (t_vector){0.0, 0.0, 0.0};
		new->translate = (t_vector){0.0, -1.01, 0.0};
		new->rotate = (t_vector){0.0, 0.0, 0.0};
		new->normal = (t_vector){0.0, 0.0, 1.0};
		new->material = (t_material){{ft_rand48(), ft_rand48(), ft_rand48()},
			{ft_rand48(), ft_rand48(), ft_rand48()}, 60.0, 0, 0, 0};
		new->radius = 10.0;
		new->angle = new->radius * new->radius;
		new->next = NULL;
	}
	else
		ft_print_error("malloc error");
	return (new);
}

int			ft_disk_compute(t_object *p, t_intersect *in)
{
	t_ray	r;
	int		ret;

	r = in->ray;
	r.start = ft_rotate_vec3(r.start, p->rotate, -1);
	r.dir = ft_rotate_vec3(r.dir, p->rotate, -1);
	r.start = ft_translate_vec3(r.start, p->translate, -1);
	ret = ft_disk_intersect(p, &r, &in->t);
	if (!ret)
		return (0);
	in->current = p;
	in->p = ft_vector_sum(r.start, ft_vector_kmult(in->t, r.dir));
	in->n = ft_normal_plane(p, ret);
	in->p = ft_translate_vec3(in->p, p->translate, 0);
	in->p = ft_rotate_vec3(in->p, p->rotate, 0);
	in->n = ft_rotate_vec3(in->n, p->rotate, 0);
	return (1);
}

int			ft_disk_intersect(t_object *d, t_ray *r, float *t)
{
	float		ddn;
	t_vector	v;
	t_vector	dist;
	float		t1;

	ddn = ft_vector_dot(r->dir, d->normal);
	if (ddn == 0.000001)
		return (0);
	dist = ft_vector_sub(d->pos, r->start);
	t1 = (ft_vector_dot(dist, d->normal)) / ddn;
	v = ft_vector_sum(r->start, ft_vector_kmult(t1, r->dir));
	if (t1 < *t && t1 > 0.001 && (ft_vector_dot(v, v) <= d->angle))
	{
		*t = t1;
		if (ddn > 0)
			return (2);
		return (1);
	}
	return (0);
}