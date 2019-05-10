/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 18:53:54 by ebatchas          #+#    #+#             */
/*   Updated: 2018/12/21 23:33:13 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPLEX_H
# define COMPLEX_H

# include <math.h>

typedef struct	s_complex
{
	double		x;
	double		y;
}				t_complex;

double			ft_module(t_complex *c);
double			ft_pow(double base, int puiss);
void			ft_complex(t_complex *z, double x, double y);
void			ft_compute(t_complex *z, t_complex *c, int n);

#endif
