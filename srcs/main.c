/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 18:54:55 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/22 15:25:10 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

static void	ft_env_draw(t_env *e)
{
	int		i;

	SDL_SetRenderDrawColor(e->ptr.renderer, 0x20, 0x20, 0x20, 255);
	SDL_RenderClear(e->ptr.renderer);
	i = NB_OPTIONS;
	while (--i >= 0)
		SDL_RenderCopy(e->ptr.renderer, e->menu.img[i], NULL, &e->menu.pos[i]);
	ft_env_display_text(e->ptr.renderer,
			e->selected ? e->selected->name : "NONE");
	if (e->optimize)
		ft_draw(e);
	else
		ft_render(&e->s, e->pixels);
	ft_update_renderer(&e->ptr, e->pixels);
	SDL_RenderPresent(e->ptr.renderer);
}

int			main(int argc, char *argv[])
{
	t_input	in;
	t_env	e;

	if (argc <= 3)
		ft_env_init(&e, argc, argv);
	else
		ft_error();
	ft_memset(&in, SDL_FALSE, sizeof(t_input));
	while (!in.quit)
	{
		ft_update_event(&in);
		if (ft_process_event(&e, &in))
			ft_env_draw(&e);
		SDL_Delay(16);
	}
	ft_env_quit(&e);
	return (0);
}
