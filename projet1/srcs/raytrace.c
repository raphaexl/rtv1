/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 20:09:53 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/26 23:17:24 by ebatchas         ###   ########.fr       */
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


static	int	ft_reflect_light(t_intersect *in)
{
	t_vector	reflect;

	reflect = ft_reflect(in->ray.dir, in->n);
	in->ray.start = ft_vector_sum(in->p, ft_vector_kmult(0.001, reflect));
	in->ray.dir = ft_vector_normalized(reflect);
	return (1);
}

static	int	ft_refract_light(t_intersect *in)
{
	t_vector	refract;

	refract = ft_refract1(in->ray.dir, in->n, 0.6);
	if (ft_vector_dot(refract, in->n) < 0)
	{
		in->ray.start = ft_vector_sum(in->p, ft_vector_kmult(0.001, refract));
		in->ray.dir = ft_vector_normalized(refract);
		return (1);
	}
		in->ray.start = ft_vector_sum(in->p, ft_vector_kmult(-0.001, refract));
		in->ray.dir = ft_vector_normalized(refract);
	return (1);
}

static void		ft_floor_object(t_material *m, t_vector pos)
{
	int		square;

	square = 0;
	if (m->chess)
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

static t_color	ft_light(t_scene *s, t_intersect *in, t_color c)
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
		ft_floor_object(&s->curr_material, in->p);
		if (!ft_scene_intersectl(s, in))
			c = ft_color_sum(c, ft_trace(in, s->curr_material, p));
		p = p->next;
	}
	return (c);
}

t_color			ft_ray_trace(t_scene *s, t_intersect *in, int depth)
{
	t_color		c;
	t_material	*m;

//	c = (t_color){.red = 0.235294f, .green = 0.67471f, .blue = 0.84313137f};
	c = (t_color){.red = 0.01f, .green = 0.01f, .blue = 0.01f};
	in->t = 20000.0f;
	if (depth > MAX_DEPTH)
		return (c);
	if (!ft_scene_intersect(s, in))
		return (c);
	m = &in->current->material;
	s->curr_material = *m;
		c = ft_light(s, in, c);//m->diffuse;
	if (depth < MAX_DEPTH && m->reflection > 0.0)
	{
		ft_reflect_light(in);
		c = ft_color_sum(c, ft_color_kmult(m->reflection, ft_ray_trace(s, in, depth + 1)));
	}
	if (depth < MAX_DEPTH && m->refraction > 0.0)
	{
		if (ft_refract_light(in));
		c = ft_color_kmult(m->refraction, ft_ray_trace(s, in, depth + 1));
	}
	return (c);
}
