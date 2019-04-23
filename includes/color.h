/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 15:46:04 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/23 22:51:19 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

typedef struct	s_color
{
	float		red;
	float		green;
	float		blue;
}				t_color;

t_color			ft_color(float r, float g, float b);
t_color			ft_color_sum(t_color a, t_color b);
#endif
