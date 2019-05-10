/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 10:47:40 by ebatchas          #+#    #+#             */
/*   Updated: 2019/03/06 07:49:37 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H
# include <math.h>

typedef struct 	s_vector
{
 	double x;
	double y;
	double z;
}		t_vector;

t_vector	ft_vector(double x, double y, double z);
t_vector	ft_vector_sum(t_vector a, t_vector b);
t_vector	ft_vector_sub(t_vector a, t_vector b);
t_vector	ft_vector_mult(t_vector a, t_vector b);
t_vector	ft_vector_cross(t_vector a, t_vector b);
t_vector	ft_vector_kmult(double k, t_vector b);
t_vector	ft_vector_multk(t_vector a, double k);
t_vector	ft_vector_div(t_vector a, double k);
t_vector	ft_vector_normalized(t_vector a);
double		ft_vector_norm2(t_vector a);
double		ft_vector_norm(t_vector a);
double		ft_vector_dot(t_vector a, t_vector b);

# endif 
