/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 20:20:10 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/08 16:16:06 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void	ft_sdl_put_pixel(Uint32 *pixels, int x, int y, int color)
{
	if (y >= 0 && y < SCR_HEIGHT && x >= 0 && x < SCR_WIDTH)
		pixels[y * SCR_WIDTH + x] = color;
	else ;
}

int		ft_rgb_color(unsigned int r, unsigned int g, unsigned int b)
{
	return (b + (g << 8) + (r << 16));
}

t_point	ft_point(int x, int y)
{
	t_point		p;

	p.x = x;
	p.y = y;
	return (p);
}

t_vect2d	ft_vect2d(float x, float y)
{
	t_vect2d		p;

	p.x = x;
	p.y = y;
	return (p);
}

void	ft_sdl_error(void)
{
	perror(SDL_GetError());
	exit(EXIT_FAILURE);
}

void	ft_error(void)
{
	ft_putendl("error");
	exit(EXIT_FAILURE);
}

void	ft_print_error(char *str)
{
	ft_putendl(str);
	exit(EXIT_FAILURE);
}
