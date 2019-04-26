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

t_vector	  ft_refract(t_vector i, t_vector n, float eta)
{
	float		cosi;
	float		cost;

	cosi = -ft_vector_dot(n, i);
	cost = 1.0 - eta * eta * (1.0 - cosi * cosi);
	return (ft_vector_sum(ft_vector_kmult(eta, i),
				ft_vector_kmult(eta * cosi - sqrtf(cost), n)));
}
