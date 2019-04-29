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

static void		ft_floor_object(t_object *o, t_material *m, t_vector pos)
{
	int		square;

	square = 0;
	if (o->type != PLANE)
		return ;
	if ((m)->chess)
	{
		square = floor(pos.x) + floor(pos.z);
		if (square % 2)
		{
			(m)->diffuse.red = 0.0;
			(m)->diffuse.green = 0.0;
			(m)->diffuse.blue = 0.0;
		}
	}
}

static t_color	ft_light(t_scene *s, t_intersect *in, t_color c)
{
	t_light		*p;
	t_material      m;
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
		m = *(in->mat_ptr);
		ft_floor_object(in->current, &m, in->p);
		if (!ft_scene_intersectl(s, in))
			c = ft_color_sum(c, ft_trace(in, &m, p));
		p = p->next;
	}
	return (c);
}

t_color		ft_ray_trace(t_scene *s, t_intersect *in, int depth)
{
	t_color		c;

	c = (t_color){0.0, 0.0, 0.0};
	in->t = 20000.0f;
	if (ft_scene_intersect(s, in))
	{
		if (depth < MAX_DEPTH)
		{
			
			if (in->current->material.refraction > 0.0)
			{
				if (ft_dielectric_sc(in, &c, in->current->material.refraction))
					return (ft_color_mult(c, ft_ray_trace(s, in, depth + 1)));
			}
			else if (in->current->material.reflection > 0.0)
			{
				if (ft_metal_sc(in, &c))
					return (ft_color_mult(c, ft_ray_trace(s, in, depth + 1)));
			}
			else
			return (ft_light(s, in, c));

		}
		/*else
		{
		write(1, "What ?\n", 7);
		return(ft_color(0.0, 0.0, 0.0));
		}*/
	}
	/*else
		return (ft_background_color(&in->ray));*/
	return (c);
}


