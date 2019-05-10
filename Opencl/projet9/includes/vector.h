/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 10:47:40 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/10 17:48:12 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include "defines.h"

typedef struct	s_vector
{
	cl_float	x;
	cl_float	y;
	cl_float	z;
}				t_vector;

t_vector		ft_vector(cl_float x, cl_float y, cl_float z);
t_vector		ft_vector_sum(t_vector a, t_vector b);
t_vector		ft_vector_sub(t_vector a, t_vector b);
t_vector		ft_vector_mult(t_vector a, t_vector b);
t_vector		ft_vector_cross(t_vector a, t_vector b);
t_vector		ft_vector_kmult(cl_float k, t_vector b);
t_vector		ft_vector_normalized(t_vector a);
cl_float			ft_vector_norm(t_vector a);
cl_float			ft_vector_dot(t_vector a, t_vector b);
t_vector		ft_reflect(t_vector v, t_vector n);
int				ft_refract(t_vector v, t_vector n, cl_float ior, t_vector *r);
#endif
