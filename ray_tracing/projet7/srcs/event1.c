/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 11:42:21 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/22 20:06:03 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void		ft_debug(void)
{
	write(1, "debug!\n", 7);
	exit(0);
}

void	ft_env_update_camera(t_env *e, float rev)
{
	if (e->menu.keys[MOVE_X])
		e->s.cam.trans.x += (rev * 0.1);
	else if (e->menu.keys[MOVE_Y])
		e->s.cam.trans.y += (rev * 0.1);
	else if (e->menu.keys[MOVE_Z])
		e->s.cam.trans.z += (rev * 0.1);
	else if (e->menu.keys[ROTATE_X])
		e->s.cam.rot.x += (2.5 * rev);
	else if (e->menu.keys[ROTATE_Y])
		e->s.cam.rot.y += (2.5 * rev);
	else if (e->menu.keys[ROTATE_Z])
		e->s.cam.rot.z += (2.5 * rev);
	else if (e->menu.keys[ZOOM])
		e->s.cam.fov += (0.5 * rev);
	e->s.cam.h = tan(e->s.cam.fov / 2.0);
	e->s.cam.w = e->s.cam.ratio * e->s.cam.h;
	e->s.cam.dir = ft_vector_normalized(ft_vector_sub(e->s.cam.look_at,
				e->s.cam.pos));
	e->s.cam.u = ft_vector_normalized(ft_vector_cross(e->s.cam.dir, e->s.cam.up));
	e->s.cam.v = ft_vector_cross(e->s.cam.u, e->s.cam.dir);
	e->s.cam.low_left = ft_vector_sub(e->s.cam.pos, 
			ft_vector_sum(ft_vector_kmult(e->s.cam.h,
					e->s.cam.v), ft_vector_kmult(e->s.cam.w, e->s.cam.u)));
	e->s.cam.low_left = ft_vector_sum(e->s.cam.low_left, e->s.cam.dir);
	e->s.cam.horiz = ft_vector_kmult(2.0 * e->s.cam.w, e->s.cam.u);
	e->s.cam.vert = ft_vector_kmult(2.0 * e->s.cam.h, e->s.cam.v);
}
