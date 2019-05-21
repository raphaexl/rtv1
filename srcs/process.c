/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:57:28 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/21 17:47:15 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

static int	ft_add_objects(t_env *e, t_menu *menu)
{
	int		ret;
	int		i;

	ret = 0;
	i = -1;
	while (++i < 6)
	{
		if (menu->keys[NEW_SPHERE + i] && (ret = 1))
		{
			if (e->s.ft_rtv1 != ft_edit_trace)
				e->s.ft_rtv1 = ft_edit_trace;
			ft_object_add_back(&e->s.obj, NEW_SPHERE + i);
			break ;
		}
	}
	return (ret);
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

	ret = ft_add_objects(e, menu);
	if (menu->keys[EDIT_TRACE] && (e->s.ft_rtv1 != ft_edit_trace) && (ret = 1))
		e->s.ft_rtv1 = ft_edit_trace;
	if (menu->keys[PATH_TRACE] && (e->s.ft_rtv1 != ft_path_trace) && (ret = 1))
		e->s.ft_rtv1 = ft_path_trace;
	if (menu->keys[RAY_TRACE] && (e->s.ft_rtv1 != ft_ray_trace) && (ret = 1))
		e->s.ft_rtv1 = ft_ray_trace;
	if (menu->keys[SAVE])
		ft_save_pixels(e->pixels, W_W, W_H);
	if (menu->keys[ZOOM] && (ret = 1))
	{
		e->s.cam.fov = ft_clamp(0.0, 179.0, e->s.cam.fov + rev * DELTA_ANGLE);
		e->s.cam.h = tan((e->s.cam.fov * M_PI * (1.0 / 180.0)) / 2.0);
		e->s.cam.w = e->s.cam.ratio * e->s.cam.h;
	}
	if (e->selected && menu->keys[DELETE] && (ret = 1))
	{
		ft_object_remove(&e->s.obj, e->selected->id);
		e->selected = NULL;
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
		(*s)->translate.z += (DELTA_TRANS * rev);
	if (menu->keys[SCALE])
		ft_object_resize(&e->selected, rev < 0 ? 0.5 : 1.5);
	(*s)->rotate.x = ft_clamp(-180.0, 180.0, (*s)->rotate.x);
	(*s)->rotate.y = ft_clamp(-180.0, 180.0, (*s)->rotate.y);
	(*s)->rotate.z = ft_clamp(-180.0, 180.0, (*s)->rotate.z);
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
