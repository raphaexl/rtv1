/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 18:11:42 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/05 16:50:26 by ebatchas         ###   ########.fr       */
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

t_object		*ft_cone_new(void)
{
	t_object	*new;

	if ((new = (t_object *)malloc(sizeof(*new))))
	{
		new->type = CONE;
		new->name = "CONE";
		new->pos = (t_vector){0.0, 0.0, 0.0};
		new->translate = (t_vector){0.0, 0.0, 0.0};
		new->rotate = (t_vector){0.0, 0.0, 0.0};
		new->normal = (t_vector){0.0, 0.0, 0.0};
		new->material = (t_material){{1.0, 1.0, 1.0}, {0, 0, 0}, 0, 0, 0, 0};
		new->radius = 0.0;
		new->angle = 20.0;
		new->next = NULL;
	}
	else
		ft_print_error("malloc error");
	return (new);
}

int				ft_cone_compute(t_object *p, t_intersect *in)
{
	t_ray	r;

	r = in->ray;
	r.start = ft_rotate_vec3(r.start, p->rotate, -1);
	r.dir = ft_rotate_vec3(r.dir, p->rotate, -1);
	r.start = ft_translate_vec3(r.start, p->translate, -1);
	if (!ft_cone_intersect(p, &r, &in->t))
		return (0);
	in->current = p;
	in->p = ft_vector_sum(r.start, ft_vector_kmult(in->t, r.dir));
	in->n = ft_normal_cone(p, ft_vector_sub(in->p, p->pos));
	in->p = ft_translate_vec3(in->p, p->translate, 0);
	in->p = ft_rotate_vec3(in->p, p->rotate, 0);
	in->n = ft_rotate_vec3(in->n, p->rotate, 0);
	return (1);
}

int				ft_cone_intersect(t_object *c, t_ray *r, float *t)
{
	t_delta		d;
	t_vector	dist;
	float		anglesin;
	float		anglecos;

	anglecos = pow(cos(c->angle), 2.0);
	anglesin = pow(sin(c->angle), 2.0);
	dist = ft_vector_sub(r->start, c->pos);
	d.a = anglecos * (r->dir.z * r->dir.z + r->dir.x * r->dir.x)
		- anglesin * (r->dir.y * r->dir.y);
	d.b = 2.0 * (anglecos * (dist.z * r->dir.z + dist.x * r->dir.x)
			- anglesin * (dist.y * r->dir.y));
	d.c = anglecos * (dist.z * dist.z + dist.x * dist.x)
		- anglesin * (dist.y * dist.y);
	d.delta = d.b * d.b - 4.0 * d.a * d.c;
	if (d.delta < 0.00000001)
		return (0);
	d.delta = sqrt(d.delta);
	return (ft_min_ray((-d.b + d.delta) / (2.0 * d.a),
				(-d.b - d.delta) / (2.0 * d.a), t));
}
