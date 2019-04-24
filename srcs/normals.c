/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 11:33:09 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/23 09:45:13 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_vector	ft_normal_sphere(t_object *s, t_vector p)
{
	p = ft_rotate_vec3(p, s->rotate, -1);
	p = ft_translate_vec3(p, s->translate, -1);
	return (ft_vector_normalized(p));
}

t_vector	ft_normal_plane(t_object *plane, t_vector p)
{
	(void)p;
	(void)plane;
	return (ft_vector(0, 0, 1.0));
}

t_vector	ft_normal_cone(t_object *cone, t_vector p)
{
	p = ft_rotate_vec3(p, cone->rotate, -1);
	p = ft_translate_vec3(p, cone->translate, -1);
	p.y = 0.01;
	return (ft_vector_normalized(p));
}

t_vector	ft_normal_cylindre(t_object *cylindre, t_vector p)
{
	p = ft_rotate_vec3(p, cylindre->rotate, -1);
	p = ft_translate_vec3(p, cylindre->translate, -1);
	return (ft_vector_normalized(ft_vector(p.x, 0.0, p.z)));
}
