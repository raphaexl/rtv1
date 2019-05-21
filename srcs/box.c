/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 20:12:46 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/21 16:51:40 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

static int	ft_min_ray(float t1, float t2, float *t)
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

t_object	*ft_box_new(void)
{
	t_object	*new;

	if ((new = (t_object *)malloc(sizeof(*new))))
	{
		new->type = BOX;
		new->name = "BOX";
		new->pos = (t_vector){-1.0, -1.0, -1.0};
		new->translate = (t_vector){0.0, 0.0, 0.0};
		new->rotate = (t_vector){0.0, 0.0, 0.0};
		new->normal = (t_vector){1.0, 1.0, 1.0};
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

int			ft_box_compute(t_object *p, t_intersect *in)
{
	t_ray	r;

	r = in->ray;
	r.start = ft_rotate_vec3(r.start, p->rotate, -1);
	r.start = ft_translate_vec3(r.start, p->translate, -1);
	r.dir = ft_rotate_vec3(r.dir, p->rotate, -1);
	if (!ft_box_intersect(p, &r, &in->t))
		return (0);
	in->current = p;
	in->p = ft_vector_sum(r.start, ft_vector_kmult(in->t, r.dir));
	in->n = ft_normal_box(p, in->p);
	in->p = ft_translate_vec3(in->p, p->translate, 0);
	in->p = ft_rotate_vec3(in->p, p->rotate, 0);
	in->n = ft_rotate_vec3(in->n, p->rotate, 0);
	in->n = ft_vector_normalized(in->n);
	return (1);
}

int			ft_box_intersect(t_object *b, t_ray *r, float *min)
{
	t_vector		t[3];
	int				sign[3];
	t_vector		bounds[2];

	bounds[0] = b->pos;
	bounds[1] = b->normal;
	t[2] = (t_vector){1.0 / r->dir.x, 1.0 / r->dir.y, 1.0 / r->dir.z};
	sign[0] = t[2].x < 0.00001;
	sign[1] = t[2].y < 0.00001;
	sign[2] = t[2].z < 0.00001;
	t[0].x = (bounds[sign[0]].x - r->start.x) * t[2].x;
	t[1].x = (bounds[1 - sign[0]].x - r->start.x) * t[2].x;
	t[0].y = (bounds[sign[1]].y - r->start.y) * t[2].y;
	t[1].y = (bounds[1 - sign[1]].y - r->start.y) * t[2].y;
	if ((t[0].x > t[1].y) || (t[0].y > t[1].x))
		return (0);
	t[0].x = (t[0].y > t[0].x) ? t[0].y : t[0].x;
	t[1].x = (t[1].y < t[1].x) ? t[1].y : t[1].x;
	t[0].z = (bounds[sign[2]].z - r->start.z) * t[2].z;
	t[1].z = (bounds[1 - sign[2]].z - r->start.z) * t[2].z;
	if ((t[0].x > t[1].z) || (t[0].z > t[1].x))
		return (0);
	t[0].x = (t[0].z > t[0].x) ? t[0].z : t[0].x;
	t[1].x = (t[1].z < t[1].x) ? t[1].z : t[1].x;
	return (ft_min_ray(t[0].x, t[1].x, min));
}
