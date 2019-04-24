/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 20:20:10 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/24 16:15:22 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

float	ft_rand48(void)
{
	static int	initialized = 0;

	if (!initialized)
	{
		initialized = 1;
		srand(time(NULL));
	}
	return ((float)rand() / (float)RAND_MAX);
}

int		ft_tab_len(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	ft_print_error(char *str)
{
	ft_putendl(str);
	exit(EXIT_FAILURE);
}

void	ft_sdl_error(void)
{
	ft_putendl(SDL_GetError());
	exit(EXIT_FAILURE);
}

void	ft_error(void)
{
	ft_putendl("error");
	exit(EXIT_FAILURE);
}
