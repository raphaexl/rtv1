/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 06:39:09 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/10 18:12:34 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_plane		ft_plane(t_vector pos, t_vector norm, cl_int material)
{
	t_plane		plane;

	plane.pos = pos;
	plane.normal = norm;
	plane.material = material;
	return (plane);
}

cl_int		ft_plane_intersect(t_plane *plane, t_ray *r, cl_float *t)
{
	cl_float	ddn;
	t_vector	h1;

	ddn = ft_vector_dot(r->dir, plane->normal);
	if (ddn == 0.0)
		return (0);
	h1 = ft_vector_sub(plane->pos, r->start);
	*t = ft_vector_dot(h1, plane->normal) / ddn;
	if (*t <= RAY_T_MIN || *t >= RAY_T_MAX)
		return (0);
	return (1);
}
