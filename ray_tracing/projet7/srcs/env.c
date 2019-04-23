/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 21:20:26 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/23 11:43:48 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

static void	ft_env_display_text(SDL_Renderer *r, char *m)
{
	SDL_Texture		*text;
	SDL_Color		c;
	SDL_Rect		pos;

	c = (SDL_Color){.r = 0x0F, .g = 0x00, .b = 0x12, .a = 0xFF};
	pos = (SDL_Rect){.x = 0, .y = 7};
	text = ft_get_render_text(r, ft_font(m, "data/fonts/angelina.TTF", 42), c);
	SDL_QueryTexture(text, NULL, NULL, &pos.w, &pos.h);
	pos.x = 233 / 2 - pos.w / 2;
	SDL_RenderCopy(r, text, NULL, &pos);
}

void		ft_env_load_all(t_env *e)
{
	int		i;

	ft_env_load_images(e);
	e->menu.pos[0] = (SDL_Rect){.x = 5, .y = 5};
	e->menu.pos[1] = (SDL_Rect){.x = 10, .y = (SCR_HEIGHT / 2 - 10)};
	e->menu.pos[2] = (SDL_Rect){.x = 200 + START_X, .y = END_Y + 20};
	e->menu.pos[3] = (SDL_Rect){.x = 440 + START_X, .y = END_Y + 20};
	e->menu.pos[4] = (SDL_Rect){.x = 640 + START_X, .y = END_Y + 20};
	e->menu.pos[5] = (SDL_Rect){.x = 200 + START_X, .y = 25};
	e->menu.pos[6] = (SDL_Rect){.x = 5 + START_X + 400 + 10, .y = 25};
	e->menu.pos[7] = (SDL_Rect){.x = 5 + START_X + 620 + 20, .y = 25};
	i = NB_OPTIONS;
	while (--i >= 0)
	{
		SDL_QueryTexture(e->menu.img[i], NULL, NULL, &e->menu.pos[i].w,
				&e->menu.pos[i].h);
		e->menu.keys[i] = 0;
	}
}

void		ft_env_init(t_env *e, char *file_name)
{
	int		w;
	int		h;

	h = W_H;
	w = W_W;
	ft_scene_init(&e->s, file_name);
	if (ft_sdl_init(&e->ptr, "42 rtv1"))
		ft_print_error("Error SDL_Init()");
	if (!(e->pixels = (Uint32 *)malloc(sizeof(Uint32) * w * h)))
		ft_print_error("error malloc pixels");
	ft_memset(e->pixels, 0, sizeof(Uint32) * w * h);
	ft_env_load_all(e);
}

void		ft_env_draw(t_env *e)
{
	int		i;

	SDL_SetRenderDrawColor(e->ptr.renderer, 255, 162, 51, 255);
	SDL_RenderClear(e->ptr.renderer);
	i = NB_OPTIONS;
	while (--i >= 0)
		SDL_RenderCopy(e->ptr.renderer, e->menu.img[i], NULL, &e->menu.pos[i]);
	ft_env_display_text(e->ptr.renderer, "NONE");
	ft_update_renderer(&e->ptr, e->pixels);
	SDL_RenderPresent(e->ptr.renderer);
}

void		ft_env_quit(t_env *e)
{
	int		i;

	i = NB_OPTIONS;
	while (--i >= 0)
	{
		if (e->menu.img[i])
			SDL_DestroyTexture(e->menu.img[i]);
		e->menu.img[i] = NULL;
	}
	if (e->pixels)
		free(e->pixels);
	e->pixels = NULL;
	ft_scene_clear(&e->s);
	ft_sdl_quit(&e->ptr);
	e = NULL;
}
