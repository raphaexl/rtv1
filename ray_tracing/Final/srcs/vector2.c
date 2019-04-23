/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 18:10:17 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/22 18:12:57 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vector.h"

t_vector	ft_vector_cross(t_vector a, t_vector b)
{
	t_vector res;

	res.x = a.y * b.z - a.z * b.y;
	res.y = a.z * b.x - a.x * b.z;
	res.z = a.x * b.y - a.y * b.z;
	return (res);
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

float		ft_vector_norm(t_vector a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

float		ft_vector_dot(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}
