/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 18:08:32 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/22 18:11:13 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vector.h"

t_vector	ft_vector(float x, float y, float z)
{
	t_vector res;

	res.x = x;
	res.y = y;
	res.z = z;
	return (res);
}

t_vector	ft_vector_sum(t_vector a, t_vector b)
{
	t_vector res;

	res.x = a.x + b.x;
	res.y = a.y + b.y;
	res.z = a.z + b.z;
	return (res);
}

t_vector	ft_vector_sub(t_vector a, t_vector b)
{
	t_vector res;

	res.x = a.x - b.x;
	res.y = a.y - b.y;
	res.z = a.z - b.z;
	return (res);
}

t_vector	ft_vector_kmult(float k, t_vector a)
{
	t_vector res;

	res.x = k * a.x;
	res.y = k * a.y;
	res.z = k * a.z;
	return (res);
}

t_vector	ft_vector_multk(t_vector a, float k)
{
	t_vector res;

	res.x = k * a.x;
	res.y = k * a.y;
	res.z = k * a.z;
	return (res);
}
