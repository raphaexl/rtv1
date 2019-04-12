/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 11:42:21 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/08 20:18:12 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"


void		ft_debug(void)
{
	write(1, "debug!\n", 7);
	exit(0);
}

void	ft_env_update_camera(t_env *e, t_input *in)
{
	if (in->keys[SDL_SCANCODE_W])
		e->s.cam.trans.y += 0.5;
	if (in->keys[SDL_SCANCODE_S])
		e->s.cam.trans.y -= 0.5;
	if (in->keys[SDL_SCANCODE_A])
		e->s.cam.trans.x += 0.5;
	if (in->keys[SDL_SCANCODE_D])
		e->s.cam.trans.x -= 0.5;
	if (in->keys[SDL_SCANCODE_KP_MINUS])
		e->s.cam.trans.z -= 0.5;
	if (in->keys[SDL_SCANCODE_KP_PLUS])
		e->s.cam.trans.z += 0.5;
	if (in->keys[SDL_SCANCODE_LEFT])
		e->s.cam.rot.y += 5.5;
	if (in->keys[SDL_SCANCODE_RIGHT])
		e->s.cam.rot.y -= 5.5;
	if (in->keys[SDL_SCANCODE_UP])
		e->s.cam.rot.x += 5.212;
	if (in->keys[SDL_SCANCODE_DOWN])
		e->s.cam.rot.x -= 5.214;
	if (e->menu.keys[ZOOM_IN])
		e->s.cam.pos.z -= 0.5;
	if (e->menu.keys[ZOOM_OUT])
		e->s.cam.pos.z += 0.5;
}

static void	ft_env_update_object(t_menu *menu, t_vector *r, t_vector *t)
{
	if (menu->keys[ROTATE_X])
	{
		r->x += DELTA_ANGLE % 180;
		//menu->keys[ROTATE_Z] = NNE;
	//	menu->keys[ROTATE_X] = NNE;
	}
	if (menu->keys[ROTATE_Y])
	{
		r->y += DELTA_ANGLE % 180;
	//	menu->keys[ROTATE_Y] = NNE;
	}
	if (menu->keys[ROTATE_Z])
	{
		r->z += DELTA_ANGLE % 180;
	}
	if (menu->keys[MOVE_DOWN])
		t->y -= 0.1;
	if (menu->keys[MOVE_UP])
		t->y += 0.1;
	if (menu->keys[MOVE_LEFT])
		t->x -= 0.1;
	if (menu->keys[MOVE_RIGHT])
		t->x += 0.1;
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
		{
			ft_env_update_object(&e->menu, &(*q)->rotate, &(*q)->translate);
			e->selected = p;
		}
	}
}
