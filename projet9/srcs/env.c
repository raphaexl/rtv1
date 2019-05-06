/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 21:20:26 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/05 15:36:04 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

static void	ft_env_display_text(SDL_Renderer *r, char *m)
{
	SDL_Texture		*t;
	SDL_Color		c;
	SDL_Rect		pos;
	static	int		initialized = 0;

	if (!initialized)
	{
		c = (SDL_Color){.r = 0xFF, .g = 0xD0, .b = 0x12, .a = 0xFF};
		pos = (SDL_Rect){.x = 0, .y = SCR_HEIGHT / 2 - 5};
		t = ft_get_render_text(r, ft_font(m, "data/fonts/angelina.TTF", 64), c);
		SDL_QueryTexture(t, NULL, NULL, &pos.w, &pos.h);
		pos.x = SCR_WIDTH / 2 - pos.w / 2;
		initialized = 1;
	}
	else
	{
		c = (SDL_Color){.r = 0x0F, .g = 0x00, .b = 0x12, .a = 0xFF};
		pos = (SDL_Rect){.x = 0, .y = 7};
		t = ft_get_render_text(r, ft_font(m, "data/fonts/angelina.TTF", 42), c);
		SDL_QueryTexture(t, NULL, NULL, &pos.w, &pos.h);
		pos.x = 233 / 2 - pos.w / 2;
	}
	SDL_RenderCopy(r, t, NULL, &pos);
	SDL_DestroyTexture(t);
}

void		ft_env_load_all(t_env *e)
{
	int		i;

	ft_env_load_images(e);
	e->menu.pos[0] = (SDL_Rect){.x = 5, .y = 5};
	e->menu.pos[1] = (SDL_Rect){.x = 10, .y = 160};
	e->menu.pos[2] = (SDL_Rect){.x = 10, .y = 310};
	e->menu.pos[3] = (SDL_Rect){.x = 10, .y = 410};
	e->menu.pos[4] = (SDL_Rect){.x = 10, .y = 510};
	e->menu.pos[5] = (SDL_Rect){.x = 10, .y = 680};
	e->menu.pos[6] = (SDL_Rect){.x = 200 + START_X, .y = END_Y + 20};
	e->menu.pos[7] = (SDL_Rect){.x = 440 + START_X, .y = END_Y + 20};
	e->menu.pos[8] = (SDL_Rect){.x = 640 + START_X, .y = END_Y + 20};
	e->menu.pos[9] = (SDL_Rect){.x = 200 + START_X, .y = 25};
	e->menu.pos[10] = (SDL_Rect){.x = 5 + START_X + 400 + 10, .y = 25};
	e->menu.pos[11] = (SDL_Rect){.x = 5 + START_X + 620 + 20, .y = 25};
	i = NB_OPTIONS;
	while (--i >= 0)
	{
		SDL_QueryTexture(e->menu.img[i], NULL, NULL, &e->menu.pos[i].w,
				&e->menu.pos[i].h);
		e->menu.keys[i] = 0;
	}
}

void		ft_env_init(t_env *e, int argc, char **argv)
{
	int		w;
	int		h;

	h = 0;
	w = W_W;
	while (--argc)
	{
		if (!ft_strcmp(argv[argc], "-o"))
			e->optimize = 1;
		else
			h = argc;
	}
	ft_scene_init(&e->s, h ? argv[h] : NULL);
	e->selected = NULL;
	h = W_H;
	ft_sdl_init(&e->ptr, "42 rtv1");
	if (!(e->pixels = (Uint32 *)malloc(sizeof(Uint32) * w * h)))
		ft_print_error("error malloc pixels");
	ft_memset(e->pixels, 0, sizeof(Uint32) * w * h);
	ft_env_load_all(e);
	SDL_SetRenderDrawColor(e->ptr.renderer, 5, 2, 51, 5);
	SDL_RenderClear(e->ptr.renderer);
	ft_env_display_text(e->ptr.renderer,
			"Loading can Take Long :seconds, minutes, hours, days...");
	SDL_RenderPresent(e->ptr.renderer);
}

void		ft_env_draw(t_env *e)
{
	int		i;

	SDL_SetRenderDrawColor(e->ptr.renderer, 255, 162, 51, 255);
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
