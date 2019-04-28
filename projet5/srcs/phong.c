/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 21:53:16 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/28 21:59:54 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

static t_color	ft_ambient_light(t_color diffuse)
{
	float		ambiant;
	t_color		c;

	ambiant = 0.02;
	c.red = ambiant * diffuse.red;
	c.green = ambiant * diffuse.green;
	c.blue = ambiant * diffuse.blue;
	return (c);
}

static t_color	ft_diffuse_light(t_color intens, t_color diffuse, float lamb)
{
	t_color	c;

	c.red = lamb * intens.red * diffuse.red;
	c.green = lamb * intens.green * diffuse.green;
	c.blue = lamb * intens.blue * diffuse.blue;
	return (c);
}

static t_color	ft_phong_shading(t_intersect *in, t_material m, t_color intens)
{
	float		reflect;
	t_vector	tp;
	t_vector	phong_dir;
	float		phong_term;

	reflect = 2.0f * ft_vector_dot(in->ray_light.dir, in->n);
	tp = ft_vector_kmult(reflect, in->n);
	phong_dir = ft_vector_sub(in->ray_light.dir, tp);
	phong_term = fmax(ft_vector_dot(phong_dir, in->ray.dir), 0.0f);
	phong_term = pow(phong_term, m.spec_pow);
	return (ft_color_mult(intens, ft_color_kmult(phong_term,
					ft_color_mult(m.diffuse, m.specular))));
}

t_color			ft_trace(t_intersect *in, t_material m, t_light *l)
{
	t_color		intensity;
	float		lambert;
	t_color		c;

	c = (t_color){0.0, 0.0, 0.0};
	intensity = l->intensity;
	c = ft_ambient_light(m.diffuse);
	lambert = ft_vector_dot(in->ray_light.dir, in->n);
	c = ft_color_sum(c, ft_diffuse_light(intensity, m.diffuse, lambert));
	return (ft_color_sum(c, ft_phong_shading(in, m, intensity)));
}
