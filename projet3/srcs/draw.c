/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 22:21:00 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/26 15:27:04 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

static Uint32	ft_cclamp(float red, float green, float blue)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	r = (unsigned char)fmin(red * 255.0, 255.0);
	g = (unsigned char)fmin(green * 255.0, 255.0);
	b = (unsigned char)fmin(blue * 255.0, 255.0);
	return (b + (g << 8) + (r << 16));
}

void			ft_render(t_scene *s, Uint32 *pixels)
{
	t_intersect	inter;
	int			y;
	int			x;
	t_color		c;

	x = W_W;
	while (--x >= 0)
	{
		y = W_H;
		while (--y >= 0)
		{
			inter.ray = ft_camera_ray(&s->cam, x, y);
			c = s->ft_rtv1(s, &inter, 0);
			pixels[x + (W_H - y - 1) * W_W] = ft_cclamp(c.red, c.green, c.blue);
		}
	}
}

static	int		ft_rend(void *ptr)
{
	t_intersect	inter;
	t_arg		*g;
	int			y;
	int			x;
	t_color		c;

	g = (t_arg *)ptr;
	x = (g->k + 1) * W_W / NB_THREADS + 1;
	while (--x >= g->start)
	{
		y = W_H;
		while (--y >= 0)
		{
			inter.ray = ft_camera_ray(&g->e.s.cam, x, y);
			c = g->e.s.ft_rtv1(&g->e.s, &inter, 0);
			g->e.pixels[x + (W_H - 1 - y) * W_W] = ft_cclamp(c.red, c.green,
					c.blue);
		}
	}
	return (0);
}

void			ft_draw(t_env *e)
{
	int				k;
	t_arg			arg[NB_THREADS];
	SDL_Thread		*t[NB_THREADS];

	k = -1;
	while (++k < NB_THREADS)
	{
		arg[k].k = k;
		arg[k].start = k * W_W / NB_THREADS;
		arg[k].e = *e;
		t[k] = SDL_CreateThread(ft_rend, "ft_rend", (void *)&arg[k]);
	}
	k = NB_THREADS;
	while (--k >= 0)
		SDL_WaitThread(t[k], NULL);
}
