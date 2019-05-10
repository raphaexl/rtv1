/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 06:39:09 by ebatchas          #+#    #+#             */
/*   Updated: 2019/03/06 11:33:27 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/prototypes.h"

t_plane		ft_plane(t_vector pos, t_vector norm, int material)
{
	t_plane		plane;

	plane.pos = pos;
	plane.normal = norm;
	plane.material = material;
	return (plane);
}

int			ft_plane_intersect(t_plane *plane, t_ray *r, double *t)
{
	double		ddn;
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
