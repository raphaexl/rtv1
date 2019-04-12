/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 12:55:55 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/08 16:14:29 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/matrix.h"

float		ft_cotangent(float angle)
{
	return (1.0 / (tan(angle)));
}

float		ft_degre_to_radian(float angle)
{
	return ((angle / 180.0)* M_PI);
}

float		ft_radian_to_degre(float angle)
{
	return ((angle * 180.0) / M_PI);
}

t_mat4		ft_mat4_identity(void)
{
	int		i;
	t_mat4	m;

	i = 16;
	while (--i >= 0)
	{
		if (i % 5)
			m.m[i] = 0.0;
		else
			m.m[i] = 1.0;
	}
	return (m);
}

t_mat4		ft_mat4_raz(void)
{
	int		i;
	t_mat4	m;

	i = 16;
	while (--i >= 0)
			m.m[i] = 0.0;
	return (m);
}

t_mat4		ft_mat4_mult_mat4(t_mat4 *a, t_mat4 *b)
{
	int		i;
	int		j;
	t_mat4	res;

	i = -1;
	res = ft_mat4_identity();
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			res.m[i * 4 + j] = a->m[i * 4 + 0] * b->m[j + 0] + a->m[i * 4 + 1] * b->m[j + 4]
				+ a->m[i * 4 + 2] * b->m[j + 8] + a->m[i * 4 + 3] * b->m[j + 12];
		}
	}
	return (res);
}


t_mat4		ft_mat4_mult_vec3(t_mat4	*m, t_vector v)
{
	t_mat4	b;

	b = ft_mat4_identity();
	b.m[0] = v.x;
	b.m[5] = v.y;
	b.m[10] = v.z;
	b.m[15] = 0;
	return (ft_mat4_mult_mat4(m, &b));
}

t_mat4		ft_mat4_mult(t_mat4	*m, float x, float y, float z)
{
	t_mat4	b;

	b = ft_mat4_identity();
	b.m[0] = x;
	b.m[5] = y;
	b.m[10] = z;
	b.m[15] = 0;
	return (ft_mat4_mult_mat4(m, &b));
}

t_mat4		ft_mat4_scale_vec3(t_mat4	*m, t_vector v)
{
	t_mat4	b;

	b = ft_mat4_identity();
	b.m[0] = v.x;
	b.m[5] = v.y;
	b.m[10] = v.z;
	return (ft_mat4_mult_mat4(m, &b));
}

t_mat4		ft_mat4_scale(t_mat4	*m, float x, float y, float z)
{
	t_mat4	b;

	b = ft_mat4_identity();
	b.m[0] = x;
	b.m[5] = y;
	b.m[10] = z;
	return (ft_mat4_mult_mat4(m, &b));
}

t_mat4		ft_mat4_translate_vec3(t_mat4	*m, t_vector v)
{
	t_mat4	b;

	b = ft_mat4_identity();
	b.m[3] = v.x;
	b.m[7] = v.y;
	b.m[11] = v.z;
	return (ft_mat4_mult_mat4(m, &b));
}

t_mat4		ft_mat4_translate(t_mat4	*m, float x, float y, float z)
{
	t_mat4	b;

	b = ft_mat4_identity();
	b.m[3] = x;
	b.m[7] = y;
	b.m[11] = z;
	return (ft_mat4_mult_mat4(m, &b));
}

t_mat4		ft_mat4_rotate_vx(t_mat4	*m, t_vector v)
{
	t_mat4	b;
	float	cosangle;
	float	sinangle;

	cosangle = cos(v.x);
	sinangle = sin(v.x);
	b = ft_mat4_identity();
	b.m[5] = cosangle;
	b.m[6] = -sinangle;
	b.m[9] = sinangle;
	b.m[10] = cosangle;
	return (ft_mat4_mult_mat4(m, &b));
}

t_mat4		ft_mat4_rotate_x(t_mat4	*m, float angle)
{
	t_mat4	b;
	float	cosangle;
	float	sinangle;

	cosangle = cos(angle);
	sinangle = sin(angle);
	b = ft_mat4_identity();
	b.m[5] = cosangle;
	b.m[6] = -sinangle;
	b.m[9] = sinangle;
	b.m[10] = cosangle;
	return (ft_mat4_mult_mat4(m, &b));
}

t_mat4		ft_mat4_rotate_vy(t_mat4	*m, t_vector v)
{
	t_mat4	b;
	float	cosangle;
	float	sinangle;

	cosangle = cos(v.y);
	sinangle = sin(v.y);
	b = ft_mat4_identity();
	b.m[0] = cosangle;
	b.m[2] = sinangle;
	b.m[8] = -sinangle;
	b.m[10] = cosangle;
	return (ft_mat4_mult_mat4(m, &b));
}

t_mat4		ft_mat4_rotate_y(t_mat4	*m, float angle)
{
	t_mat4	b;
	float	cosangle;
	float	sinangle;

	cosangle = cos(angle);
	sinangle = sin(angle);
	b = ft_mat4_identity();
	b.m[0] = cosangle;
	b.m[2] = sinangle;
	b.m[8] = -sinangle;
	b.m[10] = cosangle;
	return (ft_mat4_mult_mat4(m, &b));
}

t_mat4		ft_mat4_rotate_vz(t_mat4	*m, t_vector v)
{
	t_mat4	b;
	float	cosangle;
	float	sinangle;

	cosangle = cos(v.z);
	sinangle = sin(v.z);
	b = ft_mat4_identity();
	b.m[0] = cosangle;
	b.m[1] = -sinangle;
	b.m[4] = sinangle;
	b.m[5] = cosangle;
	return (ft_mat4_mult_mat4(m, &b));
}

t_mat4		ft_mat4_rotate_z(t_mat4	*m, float angle)
{
	t_mat4	b;
	float	cosangle;
	float	sinangle;

	cosangle = cos(angle);
	sinangle = sin(angle);
	b = ft_mat4_identity();
	b.m[0] = cosangle;
	b.m[1] = -sinangle;
	b.m[4] = sinangle;
	b.m[5] = cosangle;
	return (ft_mat4_mult_mat4(m, &b));
}

t_vector	ft_get_mat4_vec3(t_mat4 m)
{
	return (ft_vector(m.m[0], m.m[5], m.m[10]));
}

void	ft_print_mat4(t_mat4 m)
{
	int		i = -1;
	
	while (++i < 16)
	{
		if (i && !(i % 4))
			puts("");
			printf("%.2lf\t", m.m[i]);
	}
}

void	ft_print_vec3(t_vector v)
{
	printf("x = %.2lf\ty = %.2lf\t z = %.2lf\n", v.x, v.y, v.z);
}

