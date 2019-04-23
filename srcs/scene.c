/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 08:14:04 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/23 22:24:29 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

static	t_object	ft_scene_random1(t_scene *s)
{
	t_object sphere;

	sphere.pos = (t_vector){0, -1000, 0.0};
	sphere.type = SPHERE;
	sphere.material = (t_material){{0.1, 0.2, 0.5}, 0.1};
	sphere.radius = 1000.0;
	sphere.angle = 0.0;
	sphere.normal = (t_vector){.0, 0.0, 0.0};
	sphere.translate = (t_vector){.0, 0.0, 0.0};
	sphere.rotate = (t_vector){.0, 0.0, 0.0};
	ft_object_push_back(&s->obj, ft_object_new(SPHERE, &sphere));
	sphere.pos = (t_vector){0, 1, 0.0};
	sphere.material = (t_material){{0.5, 0.5, 0.5}, 1.5};
	sphere.radius = 1.0;
	ft_object_push_back(&s->obj, ft_object_new(SPHERE, &sphere));
	sphere.pos = (t_vector){-4.0, 1.0, 0.0};
	sphere.material = (t_material){{0.4, 0.2, 0.1}, 0.0};
	sphere.radius = 1.0;
	ft_object_push_back(&s->obj, ft_object_new(SPHERE, &sphere));
	sphere.pos = (t_vector){4.0, 1.0, 0.0};
	sphere.material = (t_material){{0.7, 0.6, 0.5}, 0.0};
	sphere.radius = 1.0;
	ft_object_push_back(&s->obj, ft_object_new(SPHERE, &sphere));
	return (sphere);
}

static	void		ft_scene_random2(t_scene *s, t_object sp, int a, int b)
{
	float		prob;
	t_vector	c;

	while (++a < RAND_N)
	{
		b = -RAND_N - 1;
		while (++b < RAND_N)
		{
			prob = ft_rand48();
			c = (t_vector){a + 0.9 * ft_rand48(), 0.2, b + 0.9 * ft_rand48()};
			if (ft_vector_norm(ft_vector_sub(c, ft_vector(4, 0.2, 0))) < 0.9)
				continue ;
			sp.pos = c;
			sp.radius = 0.2;
			sp.material = (t_material){{0.5, 0.5, 0.5}, 1.5};
			if (prob < 0.8)
				sp.material = (t_material){{ft_rand48() * ft_rand48(),
					ft_rand48() * ft_rand48(), ft_rand48() * ft_rand48()}, 0.2};
			else if (prob < 0.95)
				sp.material = (t_material){{0.5 * (1.0 + ft_rand48()), 0.5 *
					(1.0 + ft_rand48()), 0.5 * (1.0 + ft_rand48())},
					0.5 * ft_rand48()};
			ft_object_push_back(&s->obj, ft_object_new(SPHERE, &sp));
		}
	}
}

static	void		ft_scene_random(t_scene *s)
{
	t_iterm		l;

	ft_scene_random2(s, ft_scene_random1(s), -RAND_N - 1, 0);
	s->curr_material = (t_material){{0.0, 0.0, 0.0}, 0.0};
	s->cam = ft_camera_new(ft_vector(0.0f, 0.0f, 0.0f),
			ft_vector(0.0f, 0.0f, 0.0f), ft_vector(0.0f, 0.0f, 0.0f),
			M_PI / 2.0);
	l = (t_iterm){{13.0, 100.0, 100.0}, {1.0, 1.0, 1.0}};
	ft_light_push_back(&s->light, ft_light_new(l.pos, l.color));
	l = (t_iterm) {{100.0, 0.0, 100.0}, {1.0, 1.0, 1.0}};
	ft_light_push_back(&s->light, ft_light_new(l.pos, l.color));
}

void				ft_scene_init(t_scene *s, char *const input_file)
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
			s->cam = ft_camera_new(ft_vector(0.0f, 0.0f, 0.0f),
					ft_vector(0.0f, 0.0f, 0.0f), ft_vector(0.0f, 0.0f, 0.0f),
					M_PI / 4.0);
			if (!s->obj || !s->light)
				ft_print_error("missing Light or objects :)");
			s->curr_material = (t_material){{0.0, 0.0, 0.0}, 0.0};
			close(fd);
		}
		else
			ft_error();
	}
}

void				ft_scene_clear(t_scene *s)
{
	ft_object_clean(&s->obj);
	s->obj = NULL;
	ft_light_clean(&s->light);
	s->light = NULL;
	s = NULL;
}
