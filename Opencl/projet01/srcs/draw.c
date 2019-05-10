/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 22:21:00 by ebatchas          #+#    #+#             */
/*   Updated: 2019/03/19 14:48:50 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/prototypes.h"

t_color		ft_trace_v1(t_scene	*s, t_intersect *in)
{
	t_color	c = {0.0f, 0.0f, 0.0f};
	int level = 0;
	double coef = 1.0;
	int			id = -1;
	while (coef > 0.0f && level < 15)
	{
		id = -1;
		in->t = 20000.0f;
		if (ft_scene_intersect(s, in))
			id = in->id;
		if (id == -1 || s->obj == NONE)
			break;
		double    temp = ft_vector_dot(in->n, in->n);
		if (temp == 0)
			break;
		temp = 1.0 / sqrt(temp);
		in->n = ft_vector_kmult(temp, in->n);
		t_material curr_material;
		if (s->obj == SPHERE)
			curr_material = s->materials[s->spheres[id].material];
		if (s->obj == PLANE)
			{
				curr_material = s->materials[s->planes[id].material];
			}
		int j = -1;
		while (++j < s->nb_lights)
		{
			t_light curr_light = s->lights[j];
			t_vector dist = ft_vector_sub(curr_light.pos, in->p);
			if (ft_vector_dot(in->n, dist) <= 0.0f)
			{
				continue;
			}
			double t = sqrt(ft_vector_dot(dist, dist));
			if (t <= 0.0f)
				continue;
			in->ray_light = ft_ray(in->p, ft_vector_kmult(1 / t, dist));
			in->t = t;
			int in_shadow = ft_scene_intersectl(s, in);
			if (!in_shadow)
			{
				double lambert = ft_vector_dot(in->ray_light.dir, in->n) * coef;
				c.red += lambert * curr_light.intensity.red * curr_material.diffuse.red;
				c.green += lambert * curr_light.intensity.green * curr_material.diffuse.green;
				c.blue += lambert * curr_light.intensity.blue * curr_material.diffuse.blue;
			}
		}
		coef *= curr_material.reflection;
		in->ray.start = in->p;
		double reflected = 2.0f * ft_vector_dot(in->ray.dir, in->n);
		t_vector tmp = ft_vector_kmult(reflected, in->n);
		in->ray.dir = ft_vector_sub(in->ray.dir, tmp);
		level++;
	}
	return (c);
}

void	ft_draw(t_scene *s, Uint32 *pixels)
{

	t_intersect	inter;
	int 		y = -1;
	int 		x = -1;
	t_color		c;
	while (++y < s->scr_height)
	{
		x = -1;
		while (++x < s->scr_width)
		{
			/*inter.ray = ft_camera_ray(ft_vector((2.0f * x) / s->scr_width - 1.0f,
			  (-2.0f * y) / s->scr_height + 1.0f, 1.0), s->cam);*/
			inter.ray.start.x = x;
			inter.ray.start.y = y;
			inter.ray.start.z = -10000;
			inter.ray.dir.x = 0.0000002;
			inter.ray.dir.y = 0;
			inter.ray.dir.z = 1;
			c = ft_trace_v1(s, &inter);
			pixels[x +  (s->scr_height - y - 1) * s->scr_width] = ft_rgb_color((unsigned char)fmin(c.red * 255.0, 255.0), 
					(unsigned char)fmin(c.green * 255.0, 255.0), (unsigned char)fmin(c.blue * 255.0, 255.0));
		}
	}
}	
