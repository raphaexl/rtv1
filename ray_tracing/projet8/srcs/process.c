/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:57:28 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/23 19:43:56 by ebatchas         ###   ########.fr       */
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
	}
	return (0);
}

void		ft_env_update_camera(t_camera *cam, t_menu m, float rev)
{
	if (m.keys[MOVE_X])
		cam->trans.x += (rev * 0.1);
	else if (m.keys[MOVE_Y])
		cam->trans.y += (rev * 0.1);
	else if (m.keys[MOVE_Z])
		cam->trans.z += (rev * 0.1);
	else if (m.keys[ROTATE_X])
		cam->rot.x += (2.5 * rev);
	else if (m.keys[ROTATE_Y])
		cam->rot.y += (2.5 * rev);
	else if (m.keys[ROTATE_Z])
		cam->rot.z += (2.5 * rev);
	else if (m.keys[ZOOM])
		cam->fov += (0.5 * rev);
	cam->h = tan(cam->fov / 2.0);
	cam->w = cam->ratio * cam->h;
	cam->dir = ft_vector_normalized(ft_vector_sub(cam->look_at, cam->pos));
	cam->u = ft_vector_normalized(ft_vector_cross(cam->dir, cam->up));
	cam->v = ft_vector_cross(cam->u, cam->dir);
	cam->low_left = ft_vector_sub(cam->pos, ft_vector_sum(
				ft_vector_kmult(cam->h, cam->v), ft_vector_kmult(cam->w,
					cam->u)));
	cam->low_left = ft_vector_sum(cam->low_left, cam->dir);
	cam->horiz = ft_vector_kmult(2.0 * cam->w / (float)W_W, cam->u);
	cam->vert = ft_vector_kmult(2.0 * cam->h / (float)W_H, cam->v);
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
	return (0);
}
