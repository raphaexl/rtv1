/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 18:54:55 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/22 21:39:19 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int		main(int argc, char *argv[])
{
	t_input	in;
	t_env	e;

	if (argc <= 2)
		ft_env_init(&e, argc == 2 ? argv[1] : NULL);
	else
		ft_error();
	memset(&in, SDL_FALSE, sizeof(t_input));
	while (!in.quit)
	{
		ft_update_event(&in);
		ft_process_event(&e, &in);
		ft_render(&e.s, e.pixels);
		ft_env_draw(&e);
	}
	ft_env_quit(&e);
	return (0);
}
