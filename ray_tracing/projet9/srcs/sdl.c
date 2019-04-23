/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 20:29:41 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/23 09:51:42 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int		ft_sdl_init(t_ptr *ptr, const char *title)
{
	ERR_CHECK(SDL_Init(SDL_INIT_EVERYTHING) == 0);
	ERR_CHECK(TTF_Init() == 0);
	ERR_CHECK(IMG_Init(IMG_INIT_PNG) != 0);
	ERR_CHECK(ptr->window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED, SCR_WIDTH, SCR_HEIGHT,
				SDL_WINDOW_SHOWN));
	ERR_CHECK(ptr->renderer = SDL_CreateRenderer(ptr->window, -1,\
				SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
	ERR_CHECK(ptr->texture = SDL_CreateTexture(ptr->renderer, \
				SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, W_W, W_H));
	return (0);
}

void	ft_clear_pixels(Uint32 *pixels)
{
	int		i;

	i = -1;
	while (++i < W_W * W_H)
		pixels[i] = 0x000000;
}

int		ft_update_renderer(t_ptr *ptr, Uint32 *pixels)
{
	SDL_Rect	d;

	d = (SDL_Rect){.x = (SCR_WIDTH - W_W) / 2, .y = (SCR_HEIGHT - W_H) / 2,
		.w = W_W, .h = W_H};
	SDL_UpdateTexture(ptr->texture, NULL, pixels, W_W * sizeof(Uint32));
	SDL_RenderCopy(ptr->renderer, ptr->texture, NULL, &d);
	return (0);
}

void	ft_sdl_quit(t_ptr *ptr)
{
	if (ptr->texture)
		SDL_DestroyTexture(ptr->texture);
	ptr->texture = NULL;
	if (ptr->renderer)
		SDL_DestroyRenderer(ptr->renderer);
	ptr->renderer = NULL;
	if (ptr->window)
		SDL_DestroyWindow(ptr->window);
	ptr->window = NULL;
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}
