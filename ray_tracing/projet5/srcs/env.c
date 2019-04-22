/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 17:43:15 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/21 20:48:19 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* **************************************************************************n */

#include "../includes/rtv1.h"

int		ft_env_load_all(t_env *e)
{
	ft_env_load_images(e);
	e->menu.pos[0] = (SDL_Rect){.x = 5, .y = 5};
	e->menu.pos[1] = (SDL_Rect){.x = 10, .y = (SCR_HEIGHT / 2 - 10) };
	e->menu.pos[2] = (SDL_Rect){.x = 200 + (SCR_WIDTH - W_W) / 2, .y = END_Y + 20};
	e->menu.pos[3] = (SDL_Rect){.x = 440 + (SCR_WIDTH - W_W) / 2, .y = END_Y + 20};
	e->menu.pos[4] = (SDL_Rect){.x = 640 + (SCR_WIDTH - W_W) / 2, .y = END_Y + 20};
	e->menu.pos[5] = (SDL_Rect){.x = 200 + (SCR_WIDTH - W_W) / 2, .y = 25};
	e->menu.pos[6] = (SDL_Rect){.x = 5 + (SCR_WIDTH - W_W) / 2 + 400 + 10, .y = 25};
	e->menu.pos[7] = (SDL_Rect){.x = 5 +  (SCR_WIDTH - W_W) / 2 + 620 + 20, .y = 25};
	for (int i = 0; i < NB_OPTIONS; ++i)
		SDL_QueryTexture(e->menu.img[i], NULL, NULL, &e->menu.pos[i].w, &e->menu.pos[i].h);
	printf("%d\t %d\n", e->menu.pos[1].w, e->menu.pos[2].h);
	for (int i = 0; i < NB_OPTIONS; ++i)
		e->menu.keys[i] = NNE;
	for (int i = 0; i < 6; ++i)
		e->menu.keys[i] = 0;
	e->selected = NULL;
	return (0);
}

int		ft_env_init(t_env *e, char *file_name)
{
	ft_scene_init(&e->s, file_name);	
	if (ft_sdl_init(&e->ptr, SCR_WIDTH, SCR_HEIGHT, "42"))
		ft_print_error("Error SDL_Init()");
	if (!(e->pixels = (Uint32 *)malloc(sizeof(Uint32) * W_W * W_H)))
		ft_print_error("Error Malloc pixels");
	memset(e->pixels, 0, sizeof(Uint32) * W_W * W_H);
	ft_env_load_all(e);
	return (1);
}

static void		ft_env_display_text(SDL_Renderer *r, char *mes)
{
	SDL_Texture 	*text;
	SDL_Color		c;
	SDL_Rect		pos;

	c = (SDL_Color){.r = 0x0F, .g = 0x00, .b = 0x12, .a = 0xFF};
	pos = (SDL_Rect){.x = 0, .y = 7};
	text = ft_get_render_text(r, ft_font(mes,  "data/fonts/angelina.TTF", 42), c);
	SDL_QueryTexture(text, NULL, NULL, &pos.w, &pos.h);
	pos.x = 233 / 2 - pos.w / 2;
	SDL_RenderCopy(r, text, NULL, &pos);
}

int		ft_env_draw(t_env *e)
{
	SDL_SetRenderDrawColor(e->ptr.renderer, 255, 162, 51, 255);
	SDL_RenderClear(e->ptr.renderer);
	for (int i = 0; i < NB_OPTIONS; ++i)
		SDL_RenderCopy(e->ptr.renderer, e->menu.img[i], NULL, &e->menu.pos[i]);
	ft_env_display_text(e->ptr.renderer, e->selected ? e->selected->name : "NONE");
	ft_update_renderer(&e->ptr, e->pixels);
	SDL_RenderPresent(e->ptr.renderer);
	return (0);
}


void	ft_env_quit(t_env *e)
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
