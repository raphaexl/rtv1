/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 20:12:31 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/08 16:09:13 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/vector.h"

t_vector	ft_vector(float x, float y, float z)
{
	t_vector res;

	res.x = x;
	res.y = y;
	res.z = z;
	return (res);
}

void	ft_vector_print(t_vector v)
{
	(void) v;
	//ft_printf("(%.2lf, %.2lf, %.2lf)\n", v.x, v.y, v.z);
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

t_vector	ft_vector_div(t_vector a, float k)
{
	t_vector res;

	k = 1.0 / k;
	res.x = a.x * k;
	res.y = a.y * k;
	res.z = a.z * k;
	return (res);
}

t_vector	ft_vector_mult(t_vector a, t_vector b)
{
	t_vector res;

	res.x = a.x * b.x;
	res.y = a.y * b.y;
	res.z = a.z * b.z;
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

t_vector	ft_vector_cross(t_vector a, t_vector b)
{
	t_vector res;

	res.x = a.y * b.z - a.z * b.y;
	res.y = a.z * b.x - a.x * b.z;
	res.z = a.x * b.y - a.y * b.z;
	return (res);
}


t_vector	ft_vector_normalized(t_vector a)
{	t_vector 	res;
	float	 k;

	k = sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
	k = 1.0 / k;
	res.x = a.x * k;
	res.y = a.y * k;
	res.z = a.z * k;
	return (res);
}

float	ft_vector_norm2(t_vector a)
{
	return (a.x * a.x + a.y * a.y + a.z * a.z);
}

float	ft_vector_norm(t_vector a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

float	ft_vector_dot(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}
