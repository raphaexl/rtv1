/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 22:21:00 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/22 19:53:40 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

static Uint32	ft_clamp(float red, float green, float blue)
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

	y = W_H;
	while (--y >= 0)
	{
		x = W_W;
		while (--x >= 0)
		{
			inter.ray.start = s->cam.pos;
			inter.ray.dir = ft_camera_dir(s->cam, x, y);
			c = ft_ray_trace(s, &inter);
			pixels[x + (W_H - 1 - y) * W_W] = ft_clamp(c.red, c.green, c.blue);
		}
	}
}
