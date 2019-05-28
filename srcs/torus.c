/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   torus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 10:57:27 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/22 13:58:17 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

static int	ft_min_ray(double s[4], float *t, int n)
{
	double	min;
	int		i;

	i = -1;
	while (++i < n)
	{
		if (s[i] > 0.0001)
		{
			min = s[i];
			break ;
		}
	}
	if (i == n)
		return (0);
	while (++i < n)
	{
		if (s[i] > 0.0001 && s[i] < min)
			min = s[i];
	}
	if (min < *t && min > 0.0001)
	{
		*t = min;
		return (n);
	}
	return (0);
}

t_vector	ft_normal_torus(t_object *b, t_vector h)
{
	t_vector	p;
	float		x;
	float		y;
	float		z;

	x = h.x;
	y = h.y;
	z = h.z;
	p.x = 4.0 * x * (x * x + y * y + z * z -
			b->angle * b->angle - b->radius * b->radius);
	p.y = 4.0 * y * (x * x + y * y + z * z - b->angle * b->angle - b->radius
			* b->radius + 2.0 * b->radius * b->radius);
	p.z = 4.0 * z * (x * x + y * y + z * z -
			b->angle * b->angle - b->radius * b->radius);
	return (ft_vector_normalized(p));
}

t_object	*ft_torus_new(void)
{
	t_object	*new;

	if ((new = (t_object *)malloc(sizeof(*new))))
	{
		new->type = TORUS;
		new->name = "TORUS";
		new->pos = (t_vector){0.0, 0.0, 0.0};
		new->translate = (t_vector){0.0, 0.0, 0.0};
		new->rotate = (t_vector){0.0, 0.0, 0.0};
		new->normal = (t_vector){0.0, 0.0, 0.0};
		new->scale = (t_vector){1.0, 1.0, 1.0};
		new->material = (t_material){{ft_rand48(), ft_rand48(), ft_rand48()},
			{ft_rand48(), ft_rand48(), ft_rand48()}, 60.0, 0, 0, 0};
		new->radius = 1.0;
		new->angle = 0.5;
		new->next = NULL;
	}
	else
		ft_print_error("malloc error");
	return (new);
}

int			ft_torus_compute(t_object *p, t_intersect *in)
{
	t_ray		r;

	r = in->ray;
	r.start = ft_scale_vec3(r.start, p->scale, -1);
	r.start = ft_rotate_vec3(r.start, p->rotate, -1);
	r.start = ft_translate_vec3(r.start, p->translate, -1);
	r.dir = ft_scale_vec3(r.dir, p->scale, -1);
	r.dir = ft_rotate_vec3(r.dir, p->rotate, -1);
	if (!ft_torus_intersect(p, &r, &in->t))
		return (0);
	in->current = p;
	in->p = ft_vector_sum(r.start, ft_vector_kmult(in->t, r.dir));
	in->n = ft_normal_torus(p, ft_vector_sub(in->p, p->pos));
	in->p = ft_translate_vec3(in->p, p->translate, 0);
	in->p = ft_rotate_vec3(in->p, p->rotate, 0);
	in->p = ft_scale_vec3(in->p, p->scale, 0);
	in->n = ft_rotate_vec3(in->n, p->rotate, 0);
	in->n = ft_scale_vec3(in->n, p->scale, -1);
	in->n = ft_vector_normalized(in->n);
	return (1);
}

int			ft_torus_intersect(t_object *t, t_ray *r, float *min)
{
	t_vector	dist;
	int			num;
	double		c[5];
	double		s[4];

	c[4] = pow(ft_vector_dot(r->dir, r->dir), 2);
	dist = ft_vector_sub(r->start, t->pos);
	c[3] = 4.0 * ft_vector_dot(r->dir, r->dir) * ft_vector_dot(dist, r->dir);
	c[2] = 2.0 * ft_vector_dot(r->dir, r->dir) * (ft_vector_dot(dist, dist) -
			(t->radius * t->radius + t->angle * t->angle)) + 4.0 *
		pow(ft_vector_dot(dist, r->dir), 2) +
		4.0 * t->radius * t->radius * r->dir.y * r->dir.y;
	c[1] = 4.0 * (ft_vector_dot(dist, dist) - (t->radius * t->radius +
				t->angle * t->angle)) * ft_vector_dot(dist, r->dir) +
		8.0 * (t->radius * t->radius) * dist.y * r->dir.y;
	c[0] = pow(ft_vector_dot(dist, dist) - (t->radius * t->radius +
				t->angle * t->angle), 2) - 4.0 * (t->radius * t->radius) *
		(t->angle * t->angle - dist.y * dist.y);
	num = ft_solve_quartic(c, s);
	if (num == 0)
		return (0);
	else
		return (ft_min_ray(s, min, num));
}
