/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 20:09:53 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/19 20:34:18 by ebatchas         ###   ########.fr       */
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

static void ft_reflect_light(t_intersect *in)
{
	float reflected;

	in->ray.start = in->p;
	reflected = 2.0f * ft_vector_dot(in->ray.dir, in->n);
	t_vector tmp = ft_vector_kmult(reflected, in->n);
	in->ray.dir = ft_vector_sub(in->ray.dir, tmp);
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

t_color		ft_ray_trace1(t_scene	*s, t_intersect *in, t_menu *m)
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
		float    temp = ft_vector_dot(in->n, in->n);
		if (temp == 0.01)
			break;
		temp = 1.0 / sqrt(temp);
		in->n = ft_vector_kmult(temp, in->n);
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
			{
				write(1, "Hi\n", 3);
				continue;
			}
			in->ray_light = ft_ray(in->p, ft_vector_kmult(1.0 / t, dist));
			in->t = t;
			ft_floor_plane(in->current, &s->curr_material, in->p);
			//if (m->keys[SHADOW])
				in_shadow = ft_scene_intersectl(s, in);
			if (!in_shadow)
				c = ft_trace(c, in, s->curr_material, p, &coef, m);
			p = p->next;
		}
		ft_reflect_light(in);
		coef *= s->curr_material.reflection;
	}
	return (c);
}

t_color		ft_ray_trace2(t_scene	*s, t_intersect *in, t_menu *m)
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
		float    temp = ft_vector_dot(in->n, in->n);
		if (temp == 0.01)
			break;
		temp = 1.0 / sqrt(temp);
		in->n = ft_vector_kmult(temp, in->n);
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
			if (t == 0.0f)
			{
				write(1, "Hi\n", 3);
				continue;
			}
			in->ray_light = ft_ray(in->p, ft_vector_kmult(1.0 / t, dist));
			float tp = in->t;
			in->t = t;
			ft_floor_plane(in->current, &s->curr_material, in->p);
			//if (m->keys[SHADOW])
				in_shadow = ft_scene_intersectl(s, in);
			if (!in_shadow)
				c = ft_trace(c, in, s->curr_material, p, &coef, m);
			in->t = tp;
			p = p->next;
		}
		ft_reflect_light(in);
		coef *= s->curr_material.reflection;
	}
	return (c);
}
