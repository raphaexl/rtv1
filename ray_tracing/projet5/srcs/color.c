/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 16:01:31 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/08 15:35:21 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_color		ft_color(float r, float g, float b)
{
	t_color	color;

	color.red = r;
	color.green = g;
	color.blue = b;
	return (color);
}

t_color	ft_color_sum(t_color a, t_color b)
{
	t_color res;

	res.red = a.red + b.red;
	res.green = a.green + b.green;
	res.blue = a.blue + b.blue;
	return (res);
}

t_color	ft_color_sub(t_color a, t_color b)
{
	t_color res;

	res.red = a.red - b.red;
	res.green = a.green - b.green;
	res.blue = a.blue - b.blue;

	return (res);
}

t_color	ft_color_div(t_color a, float k)
{
	t_color res;

	res.red = a.red / k;
	res.green = a.green / k;
	res.blue = a.blue / k;
	return (res);
}

t_color	ft_color_mult(t_color a, t_color b)
{
	t_color res;

	res.red = a.red * b.red;
	res.green = a.green * b.green;
	res.blue = a.blue * b.blue;
	return (res);
}

t_color	ft_color_kmult(float k, t_color a)
{
	t_color res;

	res.red = k * a.red;
	res.green = k * a.green;
	res.blue = k * a.blue;
	return (res);
}

t_color	ft_color_multk(t_color a, float k)
{
	t_color res;

	res.red = k * a.red;
	res.green = k * a.green;
	res.blue = k * a.blue;
	return (res);
}

t_color		ft_background_color(t_ray *r)
{
	t_vector	dir;
	t_color		color;
	float		t;

	dir = ft_vector_normalized(r->dir);
	t = 0.5 * (dir.y + 1.0);
	dir = ft_vector_sum(ft_vector_kmult(1.0 - t, ft_vector(1.0, 1.0, 1.0)), ft_vector_kmult(t, ft_vector(0.5, 0.7, 1.0)));
	color.red = dir.x;
	color.green = dir.y;
	color.blue = dir.z;
	return (color);
}
