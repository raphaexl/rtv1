/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 11:33:09 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/20 19:06:47 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_vector ft_normal_sphere(t_object *s, t_vector p)
{
	(void)s;
	return (ft_vector_normalized(ft_vector_sub(p, s->pos)));
}

t_vector ft_normal_plane(t_object *plane, t_vector p)
{
	(void)plane;
	(void)p;
	return (ft_vector(0, 0, 1.0));
}

t_vector ft_normal_cone(t_object *cone, t_vector p)
{
	t_vector	res;

	if (p.x > 0)
		res.x = -sqrt(p.z * p.z + p.x * p.x) * tan(cone->angle);
	else
		res.x = sqrt(p.z * p.z + p.x * p.x) * tan(cone->angle);
	res.y = p.y;
	res.z = p.z;
	return (ft_vector_normalized(res));
}

t_vector ft_normal_cylindre(t_object *cylindre, t_vector p)
{
	(void)cylindre;
//	return (ft_vector_normalized(ft_vector(0, 2 * p.y, 2 * p.z - 1.0)));
	return (ft_vector_normalized(ft_vector(p.x,  p.y,  p.z)));
	//return (ft_vector_normalized(ft_vector(2 * p.y, 0, 2 * p.z - 1.0)));
//	return (ft_vector_normalized(ft_vector(0,  p.y,  p.z)));
}
