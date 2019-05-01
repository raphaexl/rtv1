/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 06:39:09 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/30 19:36:40 by ebatchas         ###   ########.fr       */
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
		new->normal = (t_vector){0.0, 1.0, 0.0};
		new->material = (t_material){{1.0, 1.0, 1.0}, {0, 0, 0}, 0, 0, 0, 0};
		new->radius = 0.0;
		new->angle = 0.0;
		new->next = NULL;
	}
	else
		ft_print_error("malloc error");
	return (new);
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
	in->p = ft_vector_sum(in->ray.start, ft_vector_kmult(in->t, in->ray.dir));
	in->n = ft_normal_plane(p, ret);
	return (1);
}

int			ft_plane_intersect(t_object *plane, t_ray *r, float *t)
{
	float		ddn;
	t_vector	dist;
	float		t1;

	ddn = ft_vector_dot(r->dir, plane->normal);
	if (ddn == 0.000001)
		return (0);
	dist = ft_vector_sub(plane->pos, r->start);
	t1 = (ft_vector_dot(dist, plane->normal)) / ddn;
	if (t1 < 0.001 || t1 > *t)
		return (0);
	*t = t1;
	if (ddn > 0)
		return (2);
	return (1);
}
