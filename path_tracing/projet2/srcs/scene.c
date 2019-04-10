/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 08:14:04 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/08 20:46:25 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void	ft_scene_init(t_scene *s, char *const input_file)
{
	int		fd;

	s->obj = NULL;
	s->light = NULL;
	if ((fd = open(input_file, O_RDONLY)) && fd > 0)
	{
		ft_parse_file(s, fd);
		s->cam = ft_camera_new(ft_vector(0.0f, 0.0f, 0.0f), 
				ft_vector(0.0f, 0.0f, 0.0f)	,ft_vector(0.0f, 0.0f, 0.0f));	
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

void	ft_scene_clear(t_scene *s)
{
	ft_object_clean(&s->obj);
	s->obj = NULL;
	ft_light_clean(&s->light);
	s->light = NULL;
	s = NULL;
}
