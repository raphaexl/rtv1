/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylindre.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 09:39:40 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/22 20:21:20 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

static int		ft_min_ray(float t1, float t2, float *t)
{
	if (((t1 < t2 || t2 < 0.001) && t1 > 0.1) && (t1 < *t))
	{
		*t = t1;
		return (1);
	}
	else if (((t2 < t1 || t1 < 0.001) && t2 > 0.1) && (t2 < *t))
	{
		*t = t2;
		return (1);
	}
	else
		return (0);
}

t_object		*ft_cylindre_new(void)
{
	t_object	*new;

	if ((new = (t_object *)malloc(sizeof(*new))))
	{
		new->type = CYLINDRE;
		new->name = "CYLINDRE";
		new->pos = (t_vector){0.0, 0.0, 0.0};
		new->translate = (t_vector){0.0, 0.0, 0.0};
		new->rotate = (t_vector){0.0, 0.0, 0.0};
		new->scale = (t_vector){1.0f, 1.0f, 1.0f};
		new->normal = (t_vector){0.0, 0.0, 0.0};
		new->material = (t_material){{ft_rand48(), ft_rand48(), ft_rand48()},
			{ft_rand48(), ft_rand48(), ft_rand48()}, 60.0, 0, 0, 0};
		new->radius = 1.0;
		new->angle = 0.0;
		new->next = NULL;
	}
	else
		ft_print_error("malloc error");
	return (new);
}

t_vector		ft_normal_cylindre(t_object *cylindre, t_vector p)
{
	p = ft_vector_kmult(1.0 / cylindre->radius, p);
	return (ft_vector(p.x, 0.001, p.z));
}

int				ft_cylindre_compute(t_object *p, t_intersect *in)
{
	t_ray	r;

	r = in->ray;
	r.start = ft_scale_vec3(r.start, p->scale, -1);
	r.start = ft_rotate_vec3(r.start, p->rotate, -1);
	r.start = ft_translate_vec3(r.start, p->translate, -1);
	r.dir = ft_scale_vec3(r.dir, p->scale, -1);
	r.dir = ft_rotate_vec3(r.dir, p->rotate, -1);
	if (!ft_cylindre_intersect(p, &r, &in->t))
		return (0);
	in->current = p;
	in->p = ft_vector_sum(r.start, ft_vector_kmult(in->t, r.dir));
	in->n = ft_normal_cylindre(p, ft_vector_sub(in->p, p->pos));
	in->p = ft_translate_vec3(in->p, p->translate, 0);
	in->p = ft_rotate_vec3(in->p, p->rotate, 0);
	in->p = ft_scale_vec3(in->p, p->scale, 0);
	in->n = ft_rotate_vec3(in->n, p->rotate, 0);
	in->n = ft_scale_vec3(in->n, p->scale, -1);
	in->n = ft_vector_normalized(in->n);
	return (1);
}

int				ft_cylindre_intersect(t_object *c, t_ray *r, float *t)
{
	t_delta		d;
	t_vector	dist;

	d.a = (r->dir.x * r->dir.x + r->dir.z * r->dir.z);
	dist = ft_vector_sub(r->start, c->pos);
	d.b = 2.0 * (dist.x * r->dir.x + dist.z * r->dir.z);
	d.c = (dist.x * dist.x + dist.z * dist.z) - c->radius * c->radius;
	d.delta = d.b * d.b - 4.0 * d.a * d.c;
	if (d.delta < 0.0)
		return (0);
	d.delta = sqrt(d.delta);
	return (ft_min_ray((-d.b + d.delta) / (2.0 * d.a),
				(-d.b - d.delta) / (2.0 * d.a), t));
}
