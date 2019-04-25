/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 20:09:53 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/24 18:19:19 by ebatchas         ###   ########.fr       */
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

static t_vector		ft_reflect(t_vector i, t_vector n)
{
	float		reflected;
	t_vector	tmp;

	reflected = 2.0f * ft_vector_dot(i, in->n);
	tmp = ft_vector_kmult(reflected, in->n);
	return (ft_vector_sub(i, tmp));
}

static t_vector	  ft_refract_light(t_vector i, t_vector n, float ior)
{
	float cosi = ft_clamp(-1, 1, ft_vector_dot(i, n);
	float etai = 1, etat = ior;
t_vector tmp = N;
if (cosi < 0)
cosi = -cosi; 
else {
 float swap = etai;
etai = etat;
 etat = swap; tmp= -ft_vector_kmult(-1.0, n); 
}
float eta = etai / etat;
float k = 1 - eta * eta * (1 - cosi * cosi);
if (k < 0)
return (ft_vector(0.0, 0.0, 0.0);
return ft_vector_sum(ft_vector_kmult(eta, i) ,ft_vector_kmult(eta * cosi - sqrtf(k), tmp))
}

void fresnel(t_vector i, t_vector n, float ior, float *kr)
{
float cosi = ft_clamp(-1, 1, ft_vector_dot(i, n);;
float etai = 1, etat = ior;
if (cosi > 0) {  float swap = etai;
etai = etat;
 etat = swap; }
float sint = etai / etat * sqrtf(fmax(0.f, 1 - cosi * cosi));
if (sint >= 1) {
kr = 1;
}
else {
float cost = sqrtf(fmax(0.f, 1 - sint * sint));
cosi = fabsf(cosi);
float Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
float Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
kr = (Rs * Rs + Rp * Rp) / 2;
}
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

		if (!ft_scene_intersectl(s, in))
			c = ft_color_sum(c, ft_trace(in, s->curr_material, p, coef));
		p = p->next;
	}
	return (c);
}

t_color			ft_ray_trace(t_scene *s, t_intersect *in, int depth)
{
	t_color		c;
	t_material	*m;
	int			level;

	level = -1;
	c = (t_color){.red = 0.235294f, .green = 0.67471f, .blue = 0.84313137f};
	in->t = 20000.0f;
	if (depth > MAX_DEPTH)
		return (c);
	if (!ft_scene_intersect(s, in))
		return (c);
	m = &in->current->material;
	s->curr_material = *m;
	ft_floor_object(m, in->p);
	if (depth < MAX_DEPTH && m->reflection > 0.0)
	{
		ft_reflect_light(in);
		c = ft_color_sum(c, ft_color_kmult(m->reflection, ft_ray_trace(s, in, depth + 1)));
	}
	if (depth < MAX_DEPTH && m->reflection > 0.0)
	{
		if (ft_refract_light(in, 0.6))
			c = ft_color_kmult(m->refraction, ft_ray_trace(s, in, depth + 1));
	}
	c = ft_light(s, in, c, 1.0);//m->diffuse;

	return (c);
}
