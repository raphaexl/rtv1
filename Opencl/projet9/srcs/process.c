/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:57:28 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/10 12:28:35 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int			ft_prev_update(t_env *e, t_input *in)
{
	int		r;

	r = 0;
	if (in->mouse[SDL_BUTTON_RIGHT] && in->keys[SDL_SCANCODE_LCTRL] && (r = 1))
		ft_env_select_object(e, in->mousex, in->mousey);
	if (in->keys[SDL_SCANCODE_R] && in->keys[SDL_SCANCODE_KP_MINUS] && (r = 1))
		e->selected->material.diffuse.red -= 0.1;
	else if (in->keys[SDL_SCANCODE_G] && in->keys[86] && (r = 1))
		e->selected->material.diffuse.green -= 0.1;
	else if (in->keys[SDL_SCANCODE_B] && in->keys[86] && (r = 1))
		e->selected->material.diffuse.blue -= 0.1;
	else if (in->keys[SDL_SCANCODE_R] && in->keys[87] && (r = 1))
		e->selected->material.diffuse.red += 0.1;
	else if (in->keys[SDL_SCANCODE_G] && in->keys[87] && (r = 1))
		e->selected->material.diffuse.green += 0.1;
	else if (in->keys[SDL_SCANCODE_B] && in->keys[87] && (r = 1))
		e->selected->material.diffuse.blue += 0.1;
	else if (in->keys[SDL_SCANCODE_KP_MINUS] && (r = 1))
		e->s.nb_samples -= 10;
	else if (in->keys[SDL_SCANCODE_KP_PLUS] && (r = 1))
		e->s.nb_samples += 10;
	else if (in->keys[SDL_SCANCODE_O] && (r = 1))
		e->optimize = !(e->optimize);
	e->s.nb_samples = (int)ft_clamp(1.0, 100.0, (float)e->s.nb_samples);
	return (r);
}

int			ft_update_options(t_menu *m, t_input *in, int k)
{
	int		i;
	int		is_inside;

	i = 0;
	is_inside = 0;
	while (++i < NB_OPTIONS)
	{
		if (in->mousex < m->pos[i].x || in->mousex > m->pos[i].x + m->pos[i].w)
			is_inside = 0;
		else if (in->mousey < m->pos[i].y || in->mousey > m->pos[i].y
				+ m->pos[i].h)
			is_inside = 0;
		else
			is_inside = 1;
		if (is_inside)
		{
			m->keys[i] = i * k;
			return (1);
		}
		else
			m->keys[i] = 0;
	}
	return (0);
}

static int	ft_env_update_menu(t_env *e, t_menu *menu, float rev)
{
	int		ret;

	ret = 0;
/*	if (menu->keys[EDIT_TRACE] && (e->s.ft_rtv1 != ft_edit_trace) && (ret = 1))
		e->s.ft_rtv1 = ft_edit_trace;
	if (menu->keys[PATH_TRACE] && (e->s.ft_rtv1 != ft_path_trace) && (ret = 1))
		e->s.ft_rtv1 = ft_path_trace;
	if (menu->keys[RAY_TRACE] && (e->s.ft_rtv1 != ft_ray_trace) && (ret = 1))
		e->s.ft_rtv1 = ft_ray_trace;
	if (menu->keys[NEW] && e->selected && (ret = 1))
	{
		if (e->s.ft_rtv1 != ft_edit_trace)
			e->s.ft_rtv1 = ft_edit_trace;
		ft_object_add_back(&e->s.obj, e->selected->type);
	}*/
	if (menu->keys[ZOOM] && (ret = 1))
	{
		e->s.cam.fov = (e->s.cam.fov + rev * DELTA_ANGLE);
		e->s.cam.fov = ft_clamp(0.0, 179.0, e->s.cam.fov);
	}
	return (ret);
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
		(*s)->translate.z +=  (DELTA_TRANS * rev);
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
	if (ft_prev_update(e, in))
		return (1);
	if (ft_env_update_camera(&e->s.cam, in))
		return (1);
	else if (in->mouse[SDL_BUTTON_RIGHT] && ft_update_options(&e->menu, in, 1))
	{
		if (ft_env_update_menu(e, &e->menu, 1.0))
			return (1);
		return (ft_env_update_object(e, &e->menu, -1.0));
	}
	else if (in->mouse[SDL_BUTTON_LEFT] && ft_update_options(&e->menu, in, 1))
	{
		if (ft_env_update_menu(e, &e->menu, -1.0))
			return (1);
		return (ft_env_update_object(e, &e->menu, 1.0));
	}
	ft_update_options(&e->menu, in, 0);
	return (0);
}
