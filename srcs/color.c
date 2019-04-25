/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 16:01:31 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/23 11:43:08 by ebatchas         ###   ########.fr       */
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

t_color		ft_color_sum(t_color a, t_color b)
{
	t_color res;

	res.red = a.red + b.red;
	res.green = a.green + b.green;
	res.blue = a.blue + b.blue;
	return (res);
}

t_color		ft_color_kmult(float k, t_color b)
{
	t_color res;

	res.red = k * b.red;
	res.green = k * b.green;
	res.blue = k * b.blue;
	return (res);
}
