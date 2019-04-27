/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:57:28 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/27 21:14:46 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int			ft_mouse_inside(int mousex, int mousey, SDL_Rect *r)
{
	if (mousex < r->x || mousex > r->x + r->w)
		return (0);
	else if (mousey < r->y || mousey > r->y + r->h)
		return (0);
	else
		return (1);
}

int			ft_update_options(t_menu *m, t_input *in, int k)
{
	int		i;

	i = 0;
	while (++i < NB_OPTIONS)
	{
		if (ft_mouse_inside(in->mousex, in->mousey, &m->pos[i]))
		{
			m->keys[i] = i * k;
			return (1);
		}
		else
			m->keys[i] = 0;
	}
	return (0);
}

static int	ft_env_update_object(t_env *e, t_menu *menu, float rev)
{
	t_object **s;

	s = &e->selected;
	if (!*s)
		return (0);
	if (menu->keys[ROTATE_X])
		(*s)->rotate.x += (DELTA_ANGLE * rev);
	if (menu->keys[ROTATE_Y])
		(*s)->rotate.y += (DELTA_ANGLE * rev);
	if (menu->keys[ROTATE_Z])
		(*s)->rotate.z += (DELTA_ANGLE * rev);
	if (menu->keys[MOVE_X])
		(*s)->translate.x += (DELTA_TRANS * rev);
	if (menu->keys[MOVE_Y])
		(*s)->translate.y += (DELTA_TRANS * rev);
	if (menu->keys[MOVE_Z])
		(*s)->translate.z += (DELTA_TRANS * rev);
	if (menu->keys[ZOOM])
		ft_object_add_back(&e->s.obj, e->selected->type);
	 (*s)->rotate.x = ft_clamp(0.0, 179.0, (*s)->rotate.x);
	 (*s)->rotate.y = ft_clamp(0.0, 179.0, (*s)->rotate.y);
	 (*s)->rotate.z = ft_clamp(0.0, 179.0, (*s)->rotate.z);
	 return (1);
}

int			ft_process_event(t_env *e, t_input *in)
{
	static	int		initialized = 0;

	if (!initialized && (initialized = 1))
		return (1);
	if (ft_env_update_camera(&e->s.cam, in))
		return  (1);
	if (in->mouse[SDL_BUTTON_RIGHT] && in->keys[SDL_SCANCODE_LCTRL])
		ft_env_select_object(e, in->mousex, in->mousey);
	else if (in->mouse[SDL_BUTTON_RIGHT])
	{
		if (ft_update_options(&e->menu, in, 1))
			return (ft_env_update_object(e, &e->menu, -1.0));
	}
	else if (in->mouse[SDL_BUTTON_LEFT])
	{
		if (ft_update_options(&e->menu, in, 1))
			return (ft_env_update_object(e, &e->menu, 1.0));
	}
	ft_update_options(&e->menu, in, 0);
	if (in->keys[SDL_SCANCODE_LSHIFT])
	{
	//	e->s.mode = ++(e->s.mode % 3);
		if (e->s.mode == PATH_TRACE)
	  		e->s.ft_rtv1 = ft_path_trace;
	  	else
	  		e->s.ft_rtv1 = ft_ray_trace;
	}
	return (0);
}
