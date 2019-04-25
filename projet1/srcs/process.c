/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:57:28 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/25 20:57:03 by ebatchas         ###   ########.fr       */
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

void		ft_env_update_camera(t_camera *cam, t_menu m, float rev)
{
	if (m.keys[MOVE_X])
		cam->trans.x += (rev * 0.5);
	else if (m.keys[MOVE_Y])
		cam->trans.y += (rev * 0.5);
	else if (m.keys[MOVE_Z])
		cam->trans.z += (rev * 0.5);
	else if (m.keys[ROTATE_X])
		cam->rot.x += (4.5 * rev);
	else if (m.keys[ROTATE_Y])
		cam->rot.y += (3.5 * rev);
	else if (m.keys[ROTATE_Z])
		cam->rot.z += (5.5 * rev);
	else if (m.keys[ZOOM])
		cam->fov += (0.5 * rev);
}

int			ft_process_event(t_env *e, t_input *in)
{
	static	int		initialized = 0;

	if (!initialized && (initialized = 1))
		return (1);
	if (in->mouse[SDL_BUTTON_RIGHT])
	{
		if (ft_update_options(&e->menu, in, 1))
		{
			ft_env_update_camera(&e->s.cam, e->menu, -1.0);
			return (1);
		}
	}
	else if (in->mouse[SDL_BUTTON_LEFT])
	{
		if (ft_update_options(&e->menu, in, 1))
		{
			ft_env_update_camera(&e->s.cam, e->menu, 1.0);
			return (1);
		}
	}
	ft_update_options(&e->menu, in, 0);
	if (e->s.mode == PATH_TRACE)
		e->s.ft_rtv1 = ft_path_trace;
	else
		e->s.ft_rtv1 = ft_ray_trace;
	return (0);
}
