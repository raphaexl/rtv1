/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 14:03:14 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/28 22:02:50 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

static int		ft_reflect_light(t_intersect *in)
{
	t_vector	reflect;

	reflect = ft_reflect(in->ray.dir, in->n);
	in->ray.start = ft_vector_sub(in->p, reflect);//ft_vector_kmult(0.001, reflect));
	in->ray.dir = ft_vector_normalized(reflect);
	return (1);
}

static int		ft_refract_light(t_intersect *in, float ref_index)
{
	t_vector	refract;

	
	if (ft_refract(in->ray.dir, in->n, ref_index, &refract))
	{
		in->ray.start = ft_vector_sum(in->p, ft_vector_kmult(0.001, refract));
		in->ray.dir = ft_vector_normalized(refract);
		return (1);
	}
	return (0);
}

static void		ft_floor_object(t_object *o, t_material **m, t_vector pos)
{
	int		square;

	square = 0;
	if (o->type != PLANE)
		return ;
	if ((*m)->chess)
	{
		square = floor(pos.x) + floor(pos.z);
		if (square % 2)
		{
			(*m)->diffuse.red = 0.0;
			(*m)->diffuse.green = 0.0;
			(*m)->diffuse.blue = 0.0;
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
		if ((in->t = sqrt(ft_vector_dot(dist, dist))) && in->t <= 0.01)
		{
			p = p->next;
			continue;
		}
		in->ray_light = (t_ray){in->p,ft_vector_kmult(1.0 / in->t, dist)};
		ft_floor_object(in->current, &in->mat_ptr, in->p);
		if (!ft_scene_intersectl(s, in))//Here is your problem fucker
			c = ft_color_sum(c, ft_trace(in, in->mat_ptr, p));
		p = p->next;
	}
	return (c);
}

t_color			ft_ray_trace(t_scene *s, t_intersect *in, int depth)
{
	t_color		c;


	c = (t_color){.red = 0.0f, .green = 0.0f, .blue = 0.0f};
	in->t = INFINITY;
	if (depth > MAX_DEPTH)
		return (c);
	if (ft_scene_intersect(s, in))
	{
		c = ft_light(s, in, c);
		if (depth < MAX_DEPTH && in->mat_ptr->reflection > 0.0)
		{
			ft_reflect_light(in);
			c = ft_color_sum(c, ft_color_kmult(in->mat_ptr->reflection,
						ft_ray_trace(s, in, depth + 1)));
		}
		if (depth < MAX_DEPTH && in->mat_ptr->refraction > 0.0)
		{
			if (ft_refract_light(in, in->mat_ptr->refraction))
				c = ft_color_kmult(in->mat_ptr->refraction, ft_ray_trace(s, in, depth + 1));
		}
	}
	return (c);
}
