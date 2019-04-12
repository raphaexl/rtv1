/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 22:21:00 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/08 20:33:54 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

static void	ft_render(t_env *e)
{
	t_intersect	inter;
	int 		y;
	int 		x;
	int		a;
	t_color		c;

	y = e->start - 1;
	while (++y < e->end)
	{
		x = -1;
		while (++x < W_W)
		{
			inter.ray.x = x;
			inter.ray.y = y;
			a = -1;
			while (++a < 10)
			{
				inter.ray.start = e->s.cam.pos;	
				inter.ray.dir = ft_camera_dir(e->s.cam, x, y);
				c = ft_color_sum(c, ft_ray_trace1(&e->s, &inter, &e->menu));

			}
			c.red = (c.red * 0.1);
			c.green = (c.green * 0.1);
			c.blue = (c.blue * 0.1);				e->pixels[x + y * W_W] = ft_rgb_color((unsigned char)fmin(c.red * 255.0, 255.0), 
					(unsigned char)fmin(c.green * 255.0, 255.0), (unsigned char)fmin(c.blue * 255.0, 255.0));

		}
	}
}

void	ft_draw(t_env *e)
{
	int		i;
	SDL_Thread	*th[NB_THREADS];
	t_env		tenv[NB_THREADS];

	i = -1;
	while (++i < NB_THREADS)
	{
	tenv[i] = *e;
	tenv[i].start = i * W_H / NB_THREADS;
	tenv[i].end = (i + 1) * W_H / NB_THREADS;
	th[i] = SDL_CreateThread((int(*)())ft_render, "ft_render", &tenv[i]);
	}
	while (--i >= 0)
	 SDL_WaitThread(th[i], NULL);

}


