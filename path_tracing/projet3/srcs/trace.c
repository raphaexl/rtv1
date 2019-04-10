/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 12:28:07 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/08 18:29:58 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

static t_color	ft_ambient_light(t_color c, t_material curr_material, int	apply)
{
	float 		ambiant;

	ambiant = 0.02;
	if (apply)
	{
		c.red += ambiant * curr_material.diffuse.red;
		c.green += ambiant * curr_material.diffuse.green;
		c.blue += ambiant * curr_material.diffuse.blue;
	}
	return (c);
}	

static t_color	ft_diffuse_light(t_color c, t_color intensity, t_material curr_material, float lambert)
{

	c.red += lambert * intensity.red * curr_material.diffuse.red;
	c.green += lambert * intensity.green * curr_material.diffuse.green;
	c.blue += lambert * intensity.blue * curr_material.diffuse.blue;
	return (c);
}

static void ft_reflect_light(t_intersect *in)
{
	float reflected;

	in->ray.start = in->p;
	reflected = 2.0f * ft_vector_dot(in->ray.dir, in->n);
	t_vector tmp = ft_vector_kmult(reflected, in->n);
	in->ray.dir = ft_vector_sub(in->ray.dir, tmp);
}	


static t_color ft_phong_shading(t_color c, t_intersect	*in, t_color intensity,  float coef)
{
	float		reflect;
	t_vector	tp;
	t_vector	phong_dir;
	float		phong_term;

	reflect = 2.0f * ft_vector_dot(in->ray_light.dir, in->n);
	tp = ft_vector_kmult(reflect, in->n);
	phong_dir = ft_vector_sub(in->ray_light.dir, tp);
	phong_term = fmax(ft_vector_dot(phong_dir, in->ray.dir),  0.0f);
	float spec = 0.2;
	phong_term = spec * ft_pow(phong_term, 60.0) * coef;
	c.red += phong_term * intensity.red;
	c.green += phong_term * intensity.green;
	c.blue += phong_term * intensity.blue;
	return (c);
}


t_color		ft_trace(t_color c, t_intersect	*in, t_material curr_material, t_light *l,  float *coef, t_menu *m)
{
	t_color		intensity;
	float		lambert;

	lambert = 0.0;
	intensity = l->intensity;
	c = ft_ambient_light(c, curr_material, m->keys[AMBIANT]);
	if (m->keys[DIFFUSE])
	{
		lambert  = ft_vector_dot(in->ray_light.dir, in->n) * (*coef);
		c = ft_diffuse_light(c, intensity, curr_material,  lambert);
	}
	if (m->keys[SPECULAR])
		c = ft_phong_shading(c, in, intensity, *coef);
	/*if (m->keys[REFLECTION])
	{*/
		ft_reflect_light(in);
		(*coef) *= curr_material.reflection;
	//}
	return (c);
}