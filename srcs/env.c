/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 21:20:26 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/22 18:17:43 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void		ft_env_display_text(SDL_Renderer *r, char *m)
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

void		ft_env_load_pos(t_env *env)
{
	env->menu.pos[0] = (SDL_Rect){.x = 5, .y = 5};
	env->menu.pos[1] = (SDL_Rect){.x = 10, .y = 60};
	env->menu.pos[2] = (SDL_Rect){.x = 10, .y = 100};
	env->menu.pos[3] = (SDL_Rect){.x = 10, .y = 140};
	env->menu.pos[4] = (SDL_Rect){.x = 10, .y = 180};
	env->menu.pos[5] = (SDL_Rect){.x = 10, .y = 220};
	env->menu.pos[6] = (SDL_Rect){.x = 10, .y = 260};
	env->menu.pos[7] = (SDL_Rect){.x = 10, .y = 300};
	env->menu.pos[8] = (SDL_Rect){.x = 10, .y = 340};
	env->menu.pos[9] = (SDL_Rect){.x = 10, .y = 420};
	env->menu.pos[10] = (SDL_Rect){.x = 10, .y = 480};
	env->menu.pos[11] = (SDL_Rect){.x = 10, .y = 540};
	env->menu.pos[12] = (SDL_Rect){.x = 10, .y = 680};
	env->menu.pos[13] = (SDL_Rect){.x = 100 + START_X, .y = END_Y + 15};
	env->menu.pos[14] = (SDL_Rect){.x = 410 + START_X, .y = END_Y + 15};
	env->menu.pos[15] = (SDL_Rect){.x = 675 + START_X, .y = END_Y + 15};
	env->menu.pos[16] = (SDL_Rect){.x = 200 + START_X, .y = 20};
	env->menu.pos[17] = (SDL_Rect){.x = 5 + START_X + 400 + 10, .y = 20};
	env->menu.pos[18] = (SDL_Rect){.x = 5 + START_X + 620 + 20, .y = 20};
	env->menu.pos[19] = (SDL_Rect){.x = 100 + START_X, .y = END_Y + 50};
	env->menu.pos[20] = (SDL_Rect){.x = 410 + START_X, .y = END_Y + 50};
	env->menu.pos[21] = (SDL_Rect){.x = 675 + START_X, .y = END_Y + 50};
	env->menu.pos[22] = (SDL_Rect){.x = START_X - 50, .y = END_Y + 30};
	env->menu.pos[23] = (SDL_Rect){.x = 10, .y = END_Y - 40};
	env->menu.pos[24] = (SDL_Rect){.x = END_X - 100, .y = END_Y + 30};
}

void		ft_env_load_all(t_env *e)
{
	int		i;

	ft_env_load_images(e);
	ft_env_load_pos(e);
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
	ft_sdl_init(&e->ptr, "42-1337 rtv1");
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
	e->selected = NULL;
	ft_scene_clear(&e->s);
	ft_sdl_quit(&e->ptr);
	e = NULL;
}
