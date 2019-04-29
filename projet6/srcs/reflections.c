/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 13:33:34 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/26 15:12:17 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vector.h"

t_vector	ft_reflect(t_vector v, t_vector n)
{
	t_vector	tmp;

	tmp = ft_vector_kmult(2.0 * ft_vector_dot(v, n), n);
	return (ft_vector_sub(v, tmp));
}


int  ft_refract(t_vector v, t_vector n, float ni_over_nt, t_vector *r)
{
	t_vector uv = ft_vector_normalized(v);
	t_vector tmp;
	float	dt = ft_vector_dot(uv, n);
	float	discr = 1.0 - ni_over_nt *  ni_over_nt * (1.0 - dt * dt);
	if(discr > 0.00001)
	{
		tmp = ft_vector_kmult(ni_over_nt, ft_vector_sub(uv, ft_vector_kmult(dt, n)));
		*r = ft_vector_sub(tmp, ft_vector_kmult(sqrtf(discr), n));
		return (1);
	}
	else
		return (0);
}

float	ft_schlick(float cosine, float ref_idx)
{
	float ro = (1.0 - ref_idx) / (1.0 + ref_idx);
	ro = ro * ro;
	return (ro + (1.0 - ro) * pow((1.0 - cosine), 5.0));
}
