/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 22:21:00 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/20 19:03:13 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

static void	ft_render(t_scene *s, Uint32 *pixels, t_menu *m)
{
	t_intersect	inter;
	int 		y;
	int 		x;
	t_color		c;

	y = -1;
	while (++y < W_H)
	{
		x = -1;
		while (++x < W_W)
		{
			inter.ray.x = x;
			inter.ray.y = y;
			inter.ray.start = s->cam.pos;	
			inter.ray.dir = ft_camera_dir(s->cam, x, y);
			c = ft_ray_trace2(s, &inter, m);
			pixels[x + y * W_W] = ft_rgb_color((unsigned char)fmin(c.red * 255.0, 255.0), 
					(unsigned char)fmin(c.green * 255.0, 255.0), (unsigned char)fmin(c.blue * 255.0, 255.0));

		}
	}
}

/*static void	ft_render(t_scene *s, Uint32 *pixels, t_menu *m)
{
	t_intersect	inter;
	int 		y;
	int 		x;
	t_color		c;
	float		currentX, planeX1 = -8, planeX2 = 8, planeY1 = 5, planeY2 = -5;
	float			currentY = 5, deltaX = (planeX2 - planeX1) / W_W, deltaY = (planeY2 - planeY1) / W_H;
	y = -1;
	while (++y < W_H)
	{
		x = -1;
		currentX = planeX1;
		while (++x < W_W)
		{
			inter.ray.start = (t_vector){.x = x, .y = y, .z = -10000};	
			inter.ray.dir = (t_vector){.x = 0, 0, 1};
			inter.ray.x = x;
			inter.ray.y = y;
			inter.ray.start = ft_vector(0.0, 0.0, -10);	
			inter.ray.dir = ft_vector_sub(ft_vector(currentX, currentY, 0), ft_vector(0.0, 0.0, -10));
			inter.ray.dir = ft_vector_normalized(inter.ray.dir);
			c = ft_ray_trace2(s, &inter, m);
			pixels[x + y * W_W] = ft_rgb_color((unsigned char)fmin(c.red * 255.0, 255.0), 
					(unsigned char)fmin(c.green * 255.0, 255.0), (unsigned char)fmin(c.blue * 255.0, 255.0));
			currentX += deltaX;
		}
		currentY += deltaY;
	}
}
*/
void	ft_draw(t_scene *s, Uint32 *pixels, t_menu *m)
{
	ft_render(s, pixels, m);


}
