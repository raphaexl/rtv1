/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 08:14:04 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/20 11:50:09 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"


void	ft_scene_random(t_scene *s)
{
	t_object sphere;

	//sphere.pos = (t_vector){0, -1000, -1.0};
	sphere.pos = (t_vector){0.0, 0.0, -1.5};
	sphere.type = SPHERE;
	sphere.name = "sphere";
	sphere.material = (t_material){{0.1, 0.2, 0.5}, 0.1};
	sphere.radius = 0.5;
	sphere.angle = 0.0;
	sphere.normal = (t_vector){.0, 0.0, 0.0};
	sphere.translate = (t_vector){.0, 0.0, 0.0};
	sphere.rotate = (t_vector){.0, 0.0, 0.0};
	ft_object_push_back(&s->obj, ft_object_new(SPHERE, &sphere));
	for (int a = -11; a < 11; a++)
		for (int b = -11; b < 11; b++)
		{
			float prob = ft_rand48();
			t_vector c = (t_vector){a + 0.9 * ft_rand48(), 0.2, -(b + 0.9 * ft_rand48())};
			if (ft_vector_norm(ft_vector_sub(c, ft_vector(4, 0.2, 0))) > 0.9)
			{
				sphere.pos = c;
				sphere.radius = 0.2;
				if (prob < 0.8)
				{
					sphere.material = (t_material){{ft_rand48() * ft_rand48(),ft_rand48() * ft_rand48() ,ft_rand48() * ft_rand48()}, 0.0};
					ft_object_push_back(&s->obj, ft_object_new(SPHERE, &sphere));
				}
				else if (prob < 0.95)
				{
					sphere.material = (t_material){{0.5 * (1.0 + ft_rand48()), 0.5 * (1.0 + ft_rand48()) , 0.5 * (1.0 + ft_rand48())}, 0.5 * ft_rand48()};
					ft_object_push_back(&s->obj, ft_object_new(SPHERE, &sphere));
				}
				else
				{
					sphere.material = (t_material){{0.5, 0.5, 0.5}, 1.5};
					ft_object_push_back(&s->obj, ft_object_new(SPHERE, &sphere));
				}
			}
		}
	sphere.pos = (t_vector){0, 1, -1.5};
	sphere.material = (t_material){{0.5, 0.5, 0.5}, 1.5};
	sphere.radius = 0.5;
	ft_object_push_back(&s->obj, ft_object_new(SPHERE, &sphere));
	sphere.pos = (t_vector){-4.0, 1.0, -1.5};
	sphere.material = (t_material){{0.4, 0.2, 0.1}, 0.0};
	sphere.radius = 0.5;
	ft_object_push_back(&s->obj, ft_object_new(SPHERE, &sphere));
	sphere.pos = (t_vector){4.0, 1.0, -1.5};
	sphere.material = (t_material){{0.7, 0.6, 0.5}, 0.0};
	sphere.radius = 0.5;
	ft_object_push_back(&s->obj, ft_object_new(SPHERE, &sphere));
	if (!s->obj)
	{
		ft_putnbr(ft_object_length(s->obj));
		write(1, "\n", 1);
		ft_putnbr(ft_light_length(s->light));
		exit(0);
	}
	ft_object_set_id(&s->obj);
	s->curr_material = (t_material){{0.0, 0.0, 0.0}, 0.0};
	s->cam = ft_camera_new(ft_vector(0.0f, 0.0f, 0.0f), ft_vector(0.0f, 0.0f, 0.0f)	,ft_vector(0.0f, 0.0f, 0.0f), M_PI/2.0);
	write(1, "Ok\n", 3);
}

void	ft_scene_init(t_scene *s, char *const input_file)
{
	int		fd;

	s->obj = NULL;
	s->light = NULL;
	if (!input_file)
		ft_scene_random(s);
	else
	{
		if ((fd = open(input_file, O_RDONLY)) && fd > 0)
		{
			ft_parse_file(s, fd);
			s->cam = ft_camera_new(ft_vector(0.0f, 0.0f, 1.0f), 
					ft_vector(0.0f, 0.0f, 0.0f)	,ft_vector(0.0f, 0.0f, 0.0f), M_PI/4.0);	
			if (!s->obj)
			{
				ft_putnbr(ft_object_length(s->obj));
				write(1, "\n", 1);
				ft_putnbr(ft_light_length(s->light));
				exit(0);
			}
			ft_object_set_id(&s->obj);
			s->curr_material = (t_material){{0.0, 0.0, 0.0}, 0.0};
			close(fd);
		}
		else
			ft_error();
	}
}

void	ft_scene_clear(t_scene *s)
{
	ft_object_clean(&s->obj);
	s->obj = NULL;
	ft_light_clean(&s->light);
	s->light = NULL;
	s = NULL;
}
