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
	int		a;
	t_color		c;

	y = s->scr_height + 1;
	while (--y >= 0)
	{
		x = -1;
		while (++x < s->scr_width)
		{
			inter.ray.x = x;
			inter.ray.y = y;
			a = -1;
			while (++a < 10)
{
			inter.ray.start = s->cam.pos;	
			inter.ray.dir = ft_camera_dir(s->cam, x, y);
			c = ft_color_sum(c, ft_path_trace(s, &inter, m));

}
  c.red = c.red * 0.1;
c.green = c.green * 0.1;
c.blue = c.blue * 0.1;				pixels[x +  (y) * s->scr_width] = ft_rgb_color((unsigned char)fmin(c.red * 255.0, 255.0), 
					(unsigned char)fmin(c.green * 255.0, 255.0), (unsigned char)fmin(c.blue * 255.0, 255.0));
			 
	}
		}
}

void	ft_draw(t_scene *s, Uint32 *pixels, t_menu *m)
{
	ft_render(s, pixels, m);
}
