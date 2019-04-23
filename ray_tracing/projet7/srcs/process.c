/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:57:28 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/21 19:30:14 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/rtv1.h"

int			ft_mouse_inside(int mousex, int mousey, SDL_Rect *r)
{
	if (mousex < r->x || mousex > r->x + r->w)
		return (0);
	else if (mousey < r->y || mousey > r->y + r->h)
		return (0);
	else
		return (1);
}

int		ft_update_options(t_menu *m, t_input *in, int k)
{
	int		i;

	i = 0;
	while (++i < NB_OPTIONS)
	{
		if (ft_mouse_inside(in->mousex, in->mousey, &m->pos[i]))
		{
			m->keys[i] =  (NNE + i) * k;
			return (1);
		}
	}
	return (0);
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

int		ft_process_event(t_env *e, t_input *in)
{
	static	int		initialized = 0;

	if (!initialized && (initialized = 1))
		return (1);
	if (in->mouse[SDL_BUTTON_RIGHT] )
	{
		if (ft_update_options(&e->menu, in, 1))
		{
		ft_env_update_camera(e, -1.0);
		write(1, "Yes\n", 4);
		return (1);
		}
	}
	else if (in->mouse[SDL_BUTTON_LEFT])
	{
		if (ft_update_options(&e->menu, in, 1))
		{
		ft_env_update_camera(e, 1.0);
		return (1);
		}
	}
	return (0);
}
