/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 08:14:04 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/28 22:18:02 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void				ft_scene_init(t_scene *s, char *const input_file)
{
	int		fd;

	s->obj = NULL;
	s->light = NULL;
	if ((fd = open(input_file, O_RDONLY)) && fd > 0)
	{
		s->cam = ft_camera_new(ft_vector(0.0f, 0.0f, 0.0f),
				ft_vector(0.0f, 0.0f, -1.0f), ft_vector(0.0, 1.0, 0.0),
				60.0);
		ft_parse_file(s, fd);
		if (!s->light)
			s->mode = PATH_TRACE;
		close(fd);
	}
	else
		ft_error();
	s->nb_samples = 10.0;
	s->ft_rtv1 = ft_path_trace;
}

void				ft_scene_clear(t_scene *s)
{
	ft_object_clean(&s->obj);
	s->obj = NULL;
	ft_light_clean(&s->light);
	s->light = NULL;
	s = NULL;
}
