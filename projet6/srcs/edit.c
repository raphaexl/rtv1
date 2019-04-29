/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 14:03:14 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/29 15:03:27 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"
t_color			ft_edit_trace(t_scene *s, t_intersect *in, int depth)
{

	in->t = INFINITY;
	(void)depth;
	if (ft_scene_intersect(s, in))
	{
		if (s->mode == EDIT)
			return (in->mat_ptr->diffuse);
	}
	return (ft_color(0.0, 0.0, 0.0));
}
