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
}

void		ft_process_event(t_env *e, t_input *in)
{
	if (in->mouse[SDL_BUTTON_RIGHT] )
	{
		ft_update_options(&e->menu, in, 1);
		ft_env_update_camera(e, -1.0);
	}
	else if (in->mouse[SDL_BUTTON_LEFT])
	{
		ft_update_options(&e->menu, in, 1);
		ft_env_update_camera(e, 1.0);
	}
	return;
}
