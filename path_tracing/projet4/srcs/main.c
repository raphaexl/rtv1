/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 18:54:55 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/08 16:20:14 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void	ft_print_options(t_env *e, t_input *in)
{
	if (in->keys[SDL_SCANCODE_SPACE])
		ft_putnbr(e->menu.keys[DIFFUSE]);
}

int		main(int argc, char *argv[])
{
	t_input	in;
	t_env	e;

	if (argc == 2)
		ft_env_init(&e, argv[1]);
	else
		ft_error();
	ft_draw(&e.s, e.pixels, &e.menu);
	memset(&in, SDL_FALSE, sizeof(t_input));
	while (!in.quit)
	{
		ft_update_event(&in);
		/*ft_process_event(&e, &in);
		ft_print_options(&e, &in);*/
		ft_env_draw(&e);
	}
	ft_env_quit(&e);
	return (0);
}
