/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 11:29:07 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/24 17:15:53 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_ray	ft_transform_ray(t_object *p, t_ray *ro, int invert)
{
	t_ray	r;

	r.start = ft_rotate_vec3(ro->start, p->rotate, invert);
	r.dir = ft_rotate_vec3(ro->dir, p->rotate, invert);
	r.start = ft_translate_vec3(r.start, p->translate, invert);
	return (r);
}

int		ft_scene_intersect(t_scene *s, t_intersect *in)
{
	t_object	*p;
	int			hit;

	hit = 0;
	p = s->obj;
	in->current = NULL;
	while (p)
	{
		if (p->type == SPHERE && ft_sphere_compute(p, in))
			hit = 1;
		else if (p->type == CONE && ft_cone_compute(p, in))
			hit = 1;
		else if (p->type == CYLINDRE && ft_cylindre_compute(p, in))
			hit = 1;
		else if (p->type == PLANE && ft_plane_compute(p, in))
			hit = 1;
		p = p->next;
	}
	return (hit);
}

int		ft_scene_intersectl(t_scene *s, t_intersect *in)
{
	t_object	*p;
	t_ray		r;

	p = s->obj;
	while (p)
	{
		r = ft_transform_ray(p, &in->ray_light, 1);
		if (p->type == SPHERE && ft_sphere_intersect(p, &r, &in->t))
			return (1);
		else if (p->type == CONE && ft_cone_intersect(p, &r, &in->t))
			return (1);
		else if (p->type == PLANE && ft_plane_intersect(p, &r, &in->t))
			return (1);
		else if (p->type == CYLINDRE && ft_cylindre_intersect(p, &r, &in->t))
			return (1);
		p = p->next;
	}
	return (0);
}
