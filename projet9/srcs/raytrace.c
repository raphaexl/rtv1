/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 14:03:14 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/06 14:48:50 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

static	int		ft_reflect_light(t_intersect *in)
{
	t_vector	reflect;

	reflect = ft_reflect(in->ray.dir, in->n);
	in->ray.start = ft_vector_sum(in->p, ft_vector_kmult(0.001, reflect));
	in->ray.dir = ft_vector_normalized(reflect);
	return (1);
}

static void		ft_floor_object(t_object *o, t_material *m, t_vector pos)
{
	int		square;

	square = 0;
	if (o->type != PLANE)
		return ;
	if ((m)->chess)
	{
		if (o->normal.y > 0)
		square = floor(pos.x) + floor(pos.z);
		if (o->normal.z > 0)
		square = floor(pos.x) + floor(pos.y);
		if (o->normal.x > 0)
		square = floor(pos.z) + floor(pos.y);
		if (square % 2)
			(m)->diffuse = (t_color){0.0, 0.0, 0.0};
	}
}

static t_color	ft_light(t_scene *s, t_intersect *in, t_material m, t_color c)
{
	t_light			*p;
	t_vector		dist;

	p = s->light;
	ft_floor_object(in->current, &m, in->p);
	while (p)
	{
		dist = ft_vector_sub(p->pos, in->p);
		if ((ft_vector_dot(in->n, dist) <= 0.0f))
		{
			p = p->next;
			continue;
		}
		if ((in->t = sqrt(ft_vector_dot(dist, dist))) && in->t <= 0.01)
		{
			p = p->next;
			continue;
		}
		in->ray_light = (t_ray){in->p, ft_vector_kmult(1.0 / in->t, dist)};
		if (!ft_scene_intersectl(s, in))
			c = ft_color_sum(c, ft_trace(in, &m, p, &s->ambiant));
		p = p->next;
	}
	return (c);
}

t_color			ft_ray_trace(t_scene *s, t_intersect *in, int depth)
{
	t_color		c;

	c = (t_color){0.0, 0.0, 0.0};
	in->t = INFINITY;
	if (!ft_scene_intersect(s, in))
		return (s->bg_color);
	if (depth >= MAX_DEPTH)
		return (c);
	c = ft_color_sum(c, ft_light(s, in, in->current->material, c));
	if (in->current->material.reflection > 1.0 && ft_metal_sc(in, &c))
		c = ft_color_mult(c, ft_ray_trace(s, in, depth + 1));
	else if (in->current->material.refraction > 0.0)
	{
		if (ft_dielectric_sc(in, &c, in->current->material.refraction))
			c = ft_color_mult(c, ft_ray_trace(s, in, depth + 1));
	}
	else if (in->current->material.reflection > 0.0)
	{
		ft_reflect_light(in);
		c = ft_color_sum(c, ft_color_kmult(in->current->material.reflection,
					ft_ray_trace(s, in, depth + 1)));
	}
	return (c);
}
