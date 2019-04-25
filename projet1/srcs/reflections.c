/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 13:33:34 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/25 15:24:01 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vector.h"
/*
t_vector		ft_reflect(t_vector i, t_vector n)
{
	float		reflected;
	t_vector	tmp;

	reflected = 2.0f * ft_vector_dot(i, n);
	tmp = ft_vector_kmult(reflected, n);
	return (ft_vector_sub(i, tmp));
}
*/
t_vector	  ft_refract1(t_vector i, t_vector n, float eta)
{
	float cosi = -ft_vector_dot(n, i);
	float cost = 1 - eta * eta * (1 - cosi * cosi);
	return (ft_vector_sum(ft_vector_kmult(eta, i) ,ft_vector_kmult(eta * cosi - sqrtf(cost), n)));
}
/*
t_vector	  ft_refract(t_vector i, t_vector n, float ior)
{
	float cosi = ft_clamp(-1, 1, ft_vector_dot(i, n));
	float etai = 1, etat = ior;
	t_vector tmp = n;
	if (cosi < 0)
		cosi = -cosi; 
	else {
		float swap = etai;
		etai = etat;
		etat = swap;
	   	tmp = ft_vector_kmult(-1.0, n); 
	}
	float eta = etai / etat;
	float k = 1 - eta * eta * (1 - cosi * cosi);
	if (k < 0)
		return (ft_vector(0.0, 0.0, 0.0));
	return (ft_vector_sum(ft_vector_kmult(eta, i) ,ft_vector_kmult(eta * cosi - sqrtf(k), tmp)));
}
*/

void fresnel(t_vector i, t_vector n, float ior, float *kr)
{
	float cosi = ft_clamp(-1, 1, ft_vector_dot(i, n));
	float etai = 1, etat = ior;
	if (cosi > 0) {  float swap = etai;
		etai = etat;
		etat = swap; }
	float sint = etai / etat * sqrtf(fmax(0.f, 1 - cosi * cosi));
	if (sint >= 1) {
		*kr = 1;
	}
	else {
		float cost = sqrtf(fmax(0.f, 1 - sint * sint));
		cosi = fabsf(cosi);
		float Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
		float Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
		*kr = (Rs * Rs + Rp * Rp) / 2;
	}
} 
