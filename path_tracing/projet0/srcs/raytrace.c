/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 20:09:53 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/08 20:33:28 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

float	ft_clamp(float x)
{
	return (x < 0 ? 0 : x > 1 ? 1 : x);
}

int		ft_roundint(float x)
{
	return ((int) pow(ft_clamp(x), 1 / 2.2) * 255 + .5);
}

t_ray	ft_ray(t_vector start, t_vector dir)
{
	t_ray res;

	res.start = start;
	res.dir = dir;
	return (res);
}

static void		ft_floor_plane(t_object *p, t_material *m, t_vector pos)
{
	int square;

	square = 0;
	if (p->type == PLANE && m->reflection > 0.5)
	{
		square = floor(pos.x)+ floor(pos.z);
		if (square % 2)
		{
			m->diffuse.red = 0.0;
			m->diffuse.green = 0.0;
			m->diffuse.blue = 0.0;
		}
		else
		{
			/*m->diffuse.red = 1.0;
			  m->diffuse.green = 1.0;
			  m->diffuse.blue = 1.0;*/
		}
	}
}

t_color		ft_cast_ray1(t_scene	*s, t_intersect *in, t_menu *m)
{
	t_color	c;
	int level;
	float coef;
	int in_shadow;

	level = -1;
	in_shadow = 0;
	coef = 1.0;
	c = (t_color){.red = 0.04f, .green = 0.01f, .blue = 0.01f};
	while (coef > 0.0f && ++level < 10)
	{
		in->t = 20000.0f;
		if (!ft_scene_intersect(s, in))
			break;
		s->curr_material = in->current->material;
		t_light	*p = s->light;
		while (p)
		{
			t_vector dist = ft_vector_sub(p->pos, in->p);
			if (ft_vector_dot(in->n, dist) <= 0.0f)
			{
				p = p->next;
				continue;
			}
			float t = sqrt(ft_vector_dot(dist, dist));
			if (t <= 0.0f)
				continue;
			in->ray_light = ft_ray(in->p, ft_vector_kmult(1.0 / t, dist));
			in->t = t;
			ft_floor_plane(in->current, &s->curr_material, in->p);
			if (m->keys[SHADOW])
				in_shadow = ft_scene_intersectl(s, in);
			if (!in_shadow)
				c = ft_trace(c, in, s->curr_material, p, &coef, m);
			p = p->next;
		}
	}
	return (c);
}

t_color		ft_cast_ray2(t_scene	*s, t_intersect *in, t_menu *m)
{
	t_color	c = {0.0f, 0.0f, 0.0f};

	(void)m;
	in->t = 20000.0f;
	if (ft_scene_intersect(s, in))
		c = in->current->material.diffuse;
	//	c = {.red = 0.0, .green = 0.0, .blue = 0.0};//ft_background_color(&in->ray);
	return (c);
}
