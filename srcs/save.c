/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 17:49:14 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/19 18:45:55 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void	ft_put_pixels(SDL_Surface *s, int x, int y, Uint32 pixel)
{
	int		bpp;
	Uint8	*p;

	bpp = s->format->BytesPerPixel;
	p = (Uint8 *)s->pixels + y * s->pitch + x * bpp;
	if (bpp == 1)
		*p = pixel;
	else if (bpp == 3)
	{
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
		{
			p[0] = (pixel >> 16) & 0xFF;
			p[1] = (pixel >> 8) & 0xFF;
			p[2] = (pixel & 0xFF);
		}
		else
		{
			p[0] = pixel & 0xFF;
			p[1] = (pixel >> 8) & 0xFF;
			p[2] = (pixel >> 16) & 0xFF;
		}
	}
	else
		*(Uint32 *)p = pixel;
}

void	ft_save_pixels(Uint32 *pixels, int w, int h)
{
	SDL_Surface		*s;
	int				x;
	int				y;

	if (!(s = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0)))
		ft_sdl_error();
	SDL_LockSurface(s);
	y = -1;
	while ((++y < h) && (x = -1))
		while (++x < w)
			ft_put_pixels(s, x, y, pixels[y * w + x]);
	SDL_UnlockSurface(s);
	SDL_SaveBMP(s, "out.bmp");
	SDL_FreeSurface(s);
	s = NULL;
}
