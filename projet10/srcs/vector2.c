/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 18:10:17 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/30 19:09:43 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vector.h"

float		ft_vector_norm(t_vector a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

float		ft_vector_dot(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vector	ft_vector_normalized(t_vector a)
{
	t_vector	res;
	float		k;

	k = sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
	k = 1.0 / k;
	res.x = a.x * k;
	res.y = a.y * k;
	res.z = a.z * k;
	return (res);
}

t_vector	ft_reflect(t_vector v, t_vector n)
{
	t_vector	tmp;

	tmp = ft_vector_kmult(2.0 * ft_vector_dot(v, n), n);
	return (ft_vector_sub(v, tmp));
}

int			ft_refract(t_vector v, t_vector n, float ni_over_nt, t_vector *r)
{
	t_vector	uv;
	t_vector	tmp;
	float		dt;
	float		discr;

	uv = ft_vector_normalized(v);
	dt = ft_vector_dot(uv, n);
	discr = 1.0 - ni_over_nt * ni_over_nt * (1.0 - dt * dt);
	if (discr > 0.00001)
	{
		tmp = ft_vector_kmult(ni_over_nt, ft_vector_sub(uv,
					ft_vector_kmult(dt, n)));
		*r = ft_vector_sub(tmp, ft_vector_kmult(sqrtf(discr), n));
		return (1);
	}
	else
		return (0);
}
