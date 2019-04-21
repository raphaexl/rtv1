/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 19:38:59 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/21 17:46:24 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

static	int		ft_env_load_img1(t_env *e)
{
	SDL_Surface		*s;

	if (!(s = IMG_Load("data/imgs/bouton_enfonce.bmp")))
		ft_sdl_error();
	if (!(e->menu.img[0] = SDL_CreateTextureFromSurface(e->ptr.renderer, s)))
		ft_sdl_error();
	if (!(s = IMG_Load("data/imgs/bouton_diffuse.png")))
		ft_sdl_error();
	if (!(e->menu.img[1] = SDL_CreateTextureFromSurface(e->ptr.renderer, s)))
		ft_sdl_error();
	if (!(s = IMG_Load("data/imgs/bouton_specular.png")))
		ft_sdl_error();
	if (!(e->menu.img[2] = SDL_CreateTextureFromSurface(e->ptr.renderer, s)))
		ft_sdl_error();
	if (!(s = IMG_Load("data/imgs/bouton_ambiant.png")))
		ft_sdl_error();
	if (!(e->menu.img[3] = SDL_CreateTextureFromSurface(e->ptr.renderer, s)))
		ft_sdl_error();
	if (!(s = IMG_Load("data/imgs/bouton_reflection.png")))
		ft_sdl_error();
	if (!(e->menu.img[4] = SDL_CreateTextureFromSurface(e->ptr.renderer, s)))
		ft_sdl_error();
	SDL_FreeSurface(s);
	s = NULL;
	return (0);
}

static	int		ft_env_load_img2(t_env *e)
{
	SDL_Surface		*s;

	if (!(s = IMG_Load("data/imgs/bouton_refraction.png")))
		ft_sdl_error();
	if (!(e->menu.img[5] = SDL_CreateTextureFromSurface(e->ptr.renderer, s)))
		ft_sdl_error();
	if (!(s = IMG_Load("data/imgs/bouton_shadow.png")))
		ft_sdl_error();
	if (!(e->menu.img[6] = SDL_CreateTextureFromSurface(e->ptr.renderer, s)))
		ft_sdl_error();
	if (!(s = IMG_Load("data/imgs/bouton_raytrace.png")))
		ft_sdl_error();
	if (!(e->menu.img[7] = SDL_CreateTextureFromSurface(e->ptr.renderer, s)))
		ft_sdl_error();
	if (!(s = IMG_Load("data/imgs/bouton_clear.png")))
		ft_sdl_error();
	if (!(e->menu.img[8] = SDL_CreateTextureFromSurface(e->ptr.renderer, s)))
		ft_sdl_error();
	if (!(s = IMG_Load("data/imgs/bouton_zoom-in.png")))
		ft_sdl_error();
	if (!(e->menu.img[9] = SDL_CreateTextureFromSurface(e->ptr.renderer, s)))
		ft_sdl_error();
	SDL_FreeSurface(s);
	s = NULL;
	return (0);
}

static	int		ft_env_load_img3(t_env *e)
{
	SDL_Surface		*s;

	if (!(s = IMG_Load("data/imgs/bouton_zoom-out.png")))
		ft_sdl_error();
	if (!(e->menu.img[10] = SDL_CreateTextureFromSurface(e->ptr.renderer, s)))
		ft_sdl_error();
	if (!(s = IMG_Load("data/imgs/bouton_move-left.png")))
		ft_sdl_error();
	if (!(e->menu.img[11] = SDL_CreateTextureFromSurface(e->ptr.renderer, s)))
		ft_sdl_error();
	if (!(s = IMG_Load("data/imgs/bouton_move-right.png")))
		ft_sdl_error();
	if (!(e->menu.img[12] = SDL_CreateTextureFromSurface(e->ptr.renderer, s)))
		ft_sdl_error();
	if (!(s = IMG_Load("data/imgs/bouton_move-up.png")))
		ft_sdl_error();
	if (!(e->menu.img[13] = SDL_CreateTextureFromSurface(e->ptr.renderer, s)))
		ft_sdl_error();
	s = NULL;
	return (0);
}

static	int		ft_env_load_img4(t_env *e)
{
	SDL_Surface		*s;

	if (!(s = IMG_Load("data/imgs/bouton_move-down.png")))
		ft_sdl_error();
	if (!(e->menu.img[14] = SDL_CreateTextureFromSurface(e->ptr.renderer, s)))
		ft_sdl_error();
	if (!(s = IMG_Load("data/imgs/bouton_rotate-x.png")))
		ft_sdl_error();
	if (!(e->menu.img[15] = SDL_CreateTextureFromSurface(e->ptr.renderer, s)))
		ft_sdl_error();
	if (!(s = IMG_Load("data/imgs/bouton_rotate-y.png")))
		ft_sdl_error();
	if (!(e->menu.img[16] = SDL_CreateTextureFromSurface(e->ptr.renderer, s)))
		ft_sdl_error();
	if (!(s = IMG_Load("data/imgs/bouton_rotate-z.png")))
		ft_sdl_error();
	if (!(e->menu.img[17] = SDL_CreateTextureFromSurface(e->ptr.renderer, s)))
		ft_sdl_error();
	s = NULL;
	return (0);
}

int		ft_env_load_images(t_env *env)
{
	ft_env_load_img1(env);
	ft_env_load_img2(env);
	ft_env_load_img3(env);
	ft_env_load_img4(env);
	return (0);
}
