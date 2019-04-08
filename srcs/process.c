/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:57:28 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/04 21:01:34 by ebatchas         ###   ########.fr       */
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

void		ft_update_options(t_menu *m, t_input *in, int k)
{
	int		i;

	i = 0;
	while (++i < NB_OPTIONS)
	{
		if (ft_mouse_inside(in->mousex, in->mousey, &m->pos[i]))
		{
			m->keys[i] =  (NNE + i) * k;
			m->option[i] =  k;
		}
	}
	if (m->keys[CLEAR] && m->keys[RAYTRACE])
		m->keys[CLEAR] = 0;
}

void		ft_process_event(t_env *e, t_input *in)
{
	static int		mouse_cliked = 0;

	if (in->mouse[SDL_BUTTON_LEFT] && !mouse_cliked)
	{
		mouse_cliked = 1;
		ft_update_options(&e->menu, in, 1);
	}
	else 
	{
		mouse_cliked = 0;
		if (in->mouse[SDL_BUTTON_LEFT])
			ft_update_options(&e->menu, in, 0);
	}
	ft_env_update_camera(e, in);
	if (in->mouse[SDL_BUTTON_RIGHT] && !mouse_cliked)
		ft_env_select_object(e, in->mousex, in->mousey);
	return;
}
