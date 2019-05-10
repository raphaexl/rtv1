/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 11:29:07 by ebatchas          #+#    #+#             */
/*   Updated: 2019/03/21 20:26:59 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/prototypes.h"

int		ft_scene_intersect(t_scene *s, t_intersect *in)
{
	int		i;
	int		hit;
	
	i = -1;
	hit = 0;
	while (++i < s->nb_objects)
	{
		if (i < s->nb_spheres && ft_sphere_intersect(&s->spheres[i], &in->ray, &in->t))
		{
			in->id = i;
			s->obj = SPHERE;
			hit = 1;
			in->p = ft_vector_sum(in->ray.start, ft_vector_kmult(in->t, in->ray.dir));
			in->n = ft_vector_sub(in->p, s->spheres[i].pos);
			break ;
		}
		else if (i < s->nb_planes && ft_plane_intersect(&s->planes[i], &in->ray, &in->t))
		{
			s->obj = PLANE;
			in->id = i;
			hit = 1;
			in->p = ft_vector_sum(in->ray.start, ft_vector_kmult(in->t, in->ray.dir));
			in->n = ft_vector_sub(in->p, s->planes[i].pos);
		}
	}
	return (hit);
}

int		ft_scene_intersectl(t_scene *s, t_intersect *in)
{
	int		i;
	int		hit;
	
	i = -1;
	hit = 0;
	while (++i < s->nb_objects)
	{
		if (i < s->nb_spheres && ft_sphere_intersect(&s->spheres[i], &in->ray_light, &in->t))
		{
			s->obj = SPHERE;
			hit = 1;
			break ;
		}
		else if (i < s->nb_planes && ft_plane_intersect(&s->planes[i], &in->ray_light, &in->t))
		{
		//	write(1, "Right\n", 6);
		//	s->obj = PLANE;
			//hit = 1;
			break ;
		}
	}
	return (hit);
}

