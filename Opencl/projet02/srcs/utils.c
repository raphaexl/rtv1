/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 20:20:10 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/10 18:23:29 by ebatchas         ###   ########.fr       */
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

int		ft_color1( int n, int imax)
{
	int		tab[3];
	int		nn;
	double	t;

	t = (double) n / (double) imax;
	n = (int) (t * (16777216.0)); //256*256*256
	tab[2] = n / (65536); // 256 * 256
	nn = n - tab[2] * 65536;
	tab[0] = nn / 256;
	tab[1] = nn - tab[0] * 256;
	return (ft_rgb_color(tab[0], tab[1], tab[2]));
}

int		ft_color2(int	n, int k)
{
	int		x;

	x = (n / (k / 6));
	if (x == 0)
		return (ft_rgb_color(255, (n % (k / 6)) * (255 / (k / 6)), 0));
	if (x == 1)
		return (ft_rgb_color(255 - (n % (k / 6)) * (255 / (k / 6)), 255, 0));
	if (x == 2)
		return (ft_rgb_color(0, 255, (n % (k / 6)) * (255 / (k / 6))));
	if (x == 3)
		return (ft_rgb_color(0, 255 - (n % (k / 6)) * (255 / (k / 6)), 0));
	if (x == 4)
		return (ft_rgb_color((n % (k / 6)) * (255 / (k / 6)), 0, 255));
	if (x == 5)
		return (ft_rgb_color(255, 0, 255 - (n % (k / 6)) * (255 / (k / 6))));
	return (ft_rgb_color(0, 0, 0));
}

t_point	ft_point(int x, int y)
{
	t_point		p;

	p.x = x;
	p.y = y;
	return (p);
}

void	ft_sdl_error(void)
{
	perror(SDL_GetError());
}
