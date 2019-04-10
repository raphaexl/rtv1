/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 15:26:04 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/03 20:10:39 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_color		ft_get_light(t_intersect *in, t_light *light)
{
	double		angle;
	t_vector	light_vect;

	light_vect = ft_vector_normalized(ft_vector_sub(in->p, light->pos));
	angle = ft_vector_dot(in->n, light_vect);
	if (angle <= 0.0)
		return (ft_color(0.0, 0.0, 0.0));
	return (ft_color_kmult(angle, ft_color_mult(in->current->material.diffuse, light->intensity)));
}
