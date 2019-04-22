/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 11:42:21 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/21 20:53:54 by ebatchas         ###   ########.fr       */
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
}

void	ft_env_select_object(t_env *e, int x, int y)
{
	t_object	*p;
	t_object	**q;
	t_intersect	inter;

	p = NULL;
	e->selected = NULL;
	if (x < START_X || x > END_X)
		return ;
	if (y < START_Y || y > END_Y)
		return ;
	x = x - START_X;
	y = y - START_Y;
	inter.ray.start = e->s.cam.pos;
	inter.ray.dir = ft_camera_dir(e->s.cam, x, y);
	inter.t = 20000.0f;
	if (ft_scene_intersect(&e->s, &inter))
		p = inter.current;
	if (p)
	{
		p = e->s.obj;
		while (p && p->id != inter.current->id)
			p = p->next;
		if (p  && (q = &p))
			e->selected = p;
	}
}
