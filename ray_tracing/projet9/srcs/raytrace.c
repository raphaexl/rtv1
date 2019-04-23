/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 20:09:53 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/23 09:29:31 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

static t_ray	ft_ray(t_vector start, t_vector dir)
{
	t_ray	res;

	res.start = start;
	res.dir = dir;
	return (res);
}

static void		ft_reflect_light(t_intersect *in)
{
	float		reflected;
	t_vector	tmp;

	in->ray.start = in->p;
	reflected = 2.0f * ft_vector_dot(in->ray.dir, in->n);
	tmp = ft_vector_kmult(reflected, in->n);
	in->ray.dir = ft_vector_normalized(ft_vector_sub(in->ray.dir, tmp));
}

static void		ft_floor_plane(t_object *p, t_material *m, t_vector pos)
{
	int		square;

	square = 0;
	if (p->type == PLANE && m->reflection > 0.5)
	{
		square = floor(pos.x) + floor(pos.z);
		if (square % 2)
		{
			m->diffuse.red = 0.0;
			m->diffuse.green = 0.0;
			m->diffuse.blue = 0.0;
		}
	}
}

static t_color	ft_light(t_scene *s, t_intersect *in, t_color c, float coef)
{
	t_light		*p;
	t_vector	dist;

	p = s->light;
	while (p)
	{
		dist = ft_vector_sub(p->pos, in->p);
		if (ft_vector_dot(in->n, dist) <= 0.0f)
		{
			p = p->next;
			continue;
		}
		if ((in->t = sqrt(ft_vector_dot(dist, dist))) && in->t <= 0.0)
		{
			p = p->next;
			continue;
		}
		in->ray_light = ft_ray(in->p, ft_vector_kmult(1.0 / in->t, dist));
		ft_floor_plane(in->current, &s->curr_material, in->p);
		if (!ft_scene_intersectl(s, in))
			c = ft_color_sum(c, ft_trace(in, s->curr_material, p, coef));
		p = p->next;
	}
	return (c);
}

t_color			ft_ray_trace(t_scene *s, t_intersect *in)
{
	t_color		c;
	int			level;
	float		coef;

	level = -1;
	coef = 1.0;
	c = (t_color){.red = 0.0f, .green = 0.0f, .blue = 0.0f};
	while (coef > 0.0f && ++level < 10)
	{
		in->t = 20000.0f;
		if (!ft_scene_intersect(s, in))
			break ;
		s->curr_material = in->current->material;
		c = ft_light(s, in, c, coef);
		ft_reflect_light(in);
		coef *= s->curr_material.reflection;
	}
	return (c);
}
