/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 06:39:09 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/22 13:52:59 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_object	*ft_plane_new(void)
{
	t_object	*new;

	if ((new = (t_object *)malloc(sizeof(*new))))
	{
		new->type = PLANE;
		new->name = "PLANE";
		new->pos = (t_vector){0.0, -1.0, 0.0};
		new->translate = (t_vector){0.0, 0.0, 0.0};
		new->rotate = (t_vector){0.0, 0.0, 0.0};
		new->scale = (t_vector){1.0f, 1.0f, 1.0f};
		new->normal = (t_vector){0.0, 1.0, 0.0};
		new->material = (t_material){{ft_rand48(), ft_rand48(), ft_rand48()},
			{ft_rand48(), ft_rand48(), ft_rand48()}, 60.0, 0, 0, 0};
		new->radius = 0.0;
		new->angle = 0.0;
		new->next = NULL;
	}
	else
		ft_print_error("malloc error");
	return (new);
}

t_vector	ft_normal_plane(t_object *plane, int ret)
{
	t_vector	p;

	if (ret == 1)
		p = plane->normal;
	else
		p = ft_vector_kmult(-1.0, plane->normal);
	return (p);
}

int			ft_plane_compute(t_object *p, t_intersect *in)
{
	t_ray	r;
	int		ret;

	r = in->ray;
	r.start = ft_rotate_vec3(r.start, p->rotate, -1);
	r.dir = ft_rotate_vec3(r.dir, p->rotate, -1);
	r.start = ft_translate_vec3(r.start, p->translate, -1);
	ret = ft_plane_intersect(p, &r, &in->t);
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

int			ft_plane_intersect(t_object *plane, t_ray *r, float *t)
{
	float		ddn;
	t_vector	dist;
	float		t1;

	ddn = ft_vector_dot(plane->normal, r->dir);
	if (fabs(ddn) >= 1.0e-6)
	{
		dist = ft_vector_sub(plane->pos, r->start);
		t1 = (ft_vector_dot(dist, plane->normal)) / ddn;
		if (t1 < *t && t1 > 0.001f)
		{
			*t = t1;
			if (ddn > 0.001f)
				return (2);
			return (1);
		}
	}
	return (0);
}
