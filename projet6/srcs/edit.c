/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 14:28:04 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/30 19:36:02 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_color		ft_edit_trace(t_scene *s, t_intersect *in, int depth)
{
	in->t = INFINITY;
	(void)depth;
	if (ft_scene_intersect(s, in))
		return (in->current->material.diffuse);
	return (s->bg_color);
}
