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

static void	ft_render(t_scene *s, Uint32 *pixels, t_menu *m)
{
	t_intersect	inter;
	int 		y;
	int 		x;
	t_color		c;

	y = s->scr_height + 1;
	while (--y >= 0)
	{
		x = s->scr_width + 1;
		while (--x >= 0)
		{
			inter.ray.x = x;
			inter.ray.y = y;
			inter.ray.start = s->cam.pos;	
			inter.ray.dir = ft_camera_dir(s->cam, x, y);
					c = ft_cast_ray1(s, &inter, m);
			pixels[x +  y * s->scr_width] = ft_rgb_color((unsigned char)fmin(c.red * 255.0, 255.0), 
					(unsigned char)fmin(c.green * 255.0, 255.0), (unsigned char)fmin(c.blue * 255.0, 255.0));
		}
	}
}

void	ft_draw(t_scene *s, Uint32 *pixels, t_menu *m)
{
	ft_render(s, pixels, m);
}
