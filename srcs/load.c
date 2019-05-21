/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 19:38:59 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/21 15:27:43 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

static void		ft_env_load_img1(t_env *e)
{
	SDL_Surface		*s;

	if (!(s = IMG_Load("data/imgs/bouton_enfonce.bmp")))
		ft_sdl_error();
	if (!(e->menu.img[0] = SDL_CreateTextureFromSurface(e->ptr.renderer, s)))
		ft_sdl_error();
	if (!(s = IMG_Load("data/imgs/bouton_new-sphere.png")))
		ft_sdl_error();
	if (!(e->menu.img[1] = SDL_CreateTextureFromSurface(e->ptr.renderer, s)))
		ft_sdl_error();
	if (!(s = IMG_Load("data/imgs/bouton_new-cone.png")))
		ft_sdl_error();
	if (!(e->menu.img[2] = SDL_CreateTextureFromSurface(e->ptr.renderer, s)))
		ft_sdl_error();
	if (!(s = IMG_Load("data/imgs/bouton_new-cylinder.png")))
		ft_sdl_error();
	if (!(e->menu.img[3] = SDL_CreateTextureFromSurface(e->ptr.renderer, s)))
		ft_sdl_error();
	if (!(s = IMG_Load("data/imgs/bouton_new-cube.png")))
		ft_sdl_error();
	if (!(e->menu.img[4] = SDL_CreateTextureFromSurface(e->ptr.renderer, s)))
		ft_sdl_error();
	SDL_FreeSurface(s);
	s = NULL;
}

static void		ft_env_load_img2(t_env *e)
{
	SDL_Surface		*s;

	if (!(s = IMG_Load("data/imgs/bouton_new-plane.png")))
		ft_sdl_error();
	if (!(e->menu.img[5] = SDL_CreateTextureFromSurface(e->ptr.renderer, s)))
		ft_sdl_error();
	if (!(s = IMG_Load("data/imgs/bouton_new-disk.png")))
		ft_sdl_error();
	if (!(e->menu.img[6] = SDL_CreateTextureFromSurface(e->ptr.renderer, s)))
		ft_sdl_error();
	if (!(s = IMG_Load("data/imgs/bouton_edit.png")))
		ft_sdl_error();
	if (!(e->menu.img[7] = SDL_CreateTextureFromSurface(e->ptr.renderer, s)))
		ft_sdl_error();
	if (!(s = IMG_Load("data/imgs/bouton_raytrace.png")))
		ft_sdl_error();
	if (!(e->menu.img[8] = SDL_CreateTextureFromSurface(e->ptr.renderer, s)))
		ft_sdl_error();
	if (!(s = IMG_Load("data/imgs/bouton_pathtrace.png")))
		ft_sdl_error();
	if (!(e->menu.img[9] = SDL_CreateTextureFromSurface(e->ptr.renderer, s)))
		ft_sdl_error();
	SDL_FreeSurface(s);
	s = NULL;
}

static void		ft_env_load_img3(t_env *e)
{
	SDL_Surface		*s;

	if (!(s = IMG_Load("data/imgs/bouton_zoom.png")))
		ft_sdl_error();
	if (!(e->menu.img[10] = SDL_CreateTextureFromSurface(e->ptr.renderer, s)))
		ft_sdl_error();
	if (!(s = IMG_Load("data/imgs/bouton_move-x.png")))
		ft_sdl_error();
	if (!(e->menu.img[11] = SDL_CreateTextureFromSurface(e->ptr.renderer, s)))
		ft_sdl_error();
	if (!(s = IMG_Load("data/imgs/bouton_move-z.png")))
		ft_sdl_error();
	if (!(e->menu.img[12] = SDL_CreateTextureFromSurface(e->ptr.renderer, s)))
		ft_sdl_error();
	if (!(s = IMG_Load("data/imgs/bouton_move-y.png")))
		ft_sdl_error();
	if (!(e->menu.img[13] = SDL_CreateTextureFromSurface(e->ptr.renderer, s)))
		ft_sdl_error();
	if (!(s = IMG_Load("data/imgs/bouton_rotate-x.png")))
		ft_sdl_error();
	if (!(e->menu.img[14] = SDL_CreateTextureFromSurface(e->ptr.renderer, s)))
		ft_sdl_error();
	SDL_FreeSurface(s);
	s = NULL;
}

static void		ft_env_load_img4(t_env *e)
{
	SDL_Surface		*s;

	if (!(s = IMG_Load("data/imgs/bouton_rotate-z.png")))
		ft_sdl_error();
	if (!(e->menu.img[15] = SDL_CreateTextureFromSurface(e->ptr.renderer, s)))
		ft_sdl_error();
	if (!(s = IMG_Load("data/imgs/bouton_rotate-y.png")))
		ft_sdl_error();
	if (!(e->menu.img[16] = SDL_CreateTextureFromSurface(e->ptr.renderer, s)))
		ft_sdl_error();
	if (!(s = IMG_Load("data/imgs/bouton_scale.png")))
		ft_sdl_error();
	if (!(e->menu.img[17] = SDL_CreateTextureFromSurface(e->ptr.renderer, s)))
		ft_sdl_error();
	if (!(s = IMG_Load("data/imgs/bouton_save.png")))
		ft_sdl_error();
	if (!(e->menu.img[18] = SDL_CreateTextureFromSurface(e->ptr.renderer, s)))
		ft_sdl_error();
	if (!(s = IMG_Load("data/imgs/bouton_delete.png")))
		ft_sdl_error();
	if (!(e->menu.img[19] = SDL_CreateTextureFromSurface(e->ptr.renderer, s)))
		ft_sdl_error();
	SDL_FreeSurface(s);
	s = NULL;
}

void			ft_env_load_images(t_env *env)
{
	ft_env_load_img1(env);
	ft_env_load_img2(env);
	ft_env_load_img3(env);
	ft_env_load_img4(env);
	env->menu.pos[0] = (SDL_Rect){.x = 5, .y = 5};
	env->menu.pos[1] = (SDL_Rect){.x = 10, .y = 70};
	env->menu.pos[2] = (SDL_Rect){.x = 10, .y = 120};
	env->menu.pos[3] = (SDL_Rect){.x = 10, .y = 170};
	env->menu.pos[4] = (SDL_Rect){.x = 10, .y = 220};
	env->menu.pos[5] = (SDL_Rect){.x = 10, .y = 270};
	env->menu.pos[6] = (SDL_Rect){.x = 10, .y = 320};
	env->menu.pos[7] = (SDL_Rect){.x = 10, .y = 420};
	env->menu.pos[8] = (SDL_Rect){.x = 10, .y = 480};
	env->menu.pos[9] = (SDL_Rect){.x = 10, .y = 540};
	env->menu.pos[10] = (SDL_Rect){.x = 10, .y = 680};
	env->menu.pos[11] = (SDL_Rect){.x = 100 + START_X, .y = END_Y + 20};
	env->menu.pos[12] = (SDL_Rect){.x = 410 + START_X, .y = END_Y + 20};
	env->menu.pos[13] = (SDL_Rect){.x = 675 + START_X, .y = END_Y + 20};
	env->menu.pos[14] = (SDL_Rect){.x = 200 + START_X, .y = 20};
	env->menu.pos[15] = (SDL_Rect){.x = 5 + START_X + 400 + 10, .y = 20};
	env->menu.pos[16] = (SDL_Rect){.x = 5 + START_X + 620 + 20, .y = 20};
	env->menu.pos[17] = (SDL_Rect){.x = START_X + 400 + 10, .y = END_Y + 60};
	env->menu.pos[18] = (SDL_Rect){.x = 10, .y = END_Y - 40};
	env->menu.pos[19] = (SDL_Rect){.x = END_X - 100, .y = END_Y + 50};
}
