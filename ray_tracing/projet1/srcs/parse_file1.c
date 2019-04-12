/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 17:44:48 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/08 15:32:23 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void	ft_parse_file(t_scene *s, int	fd)
{
	char		*line;

	while (ft_get_next_line(fd, &line) && line)
	{
		if (!ft_strcmp(line, "sphere"))
			ft_object_push_back(&s->obj, ft_sphere_read(fd));
		else if (!ft_strcmp(line, "cylindre"))
			ft_object_push_back(&s->obj, ft_cylindre_read(fd));
		else if (!ft_strcmp(line, "cone"))
			ft_object_push_back(&s->obj, ft_cone_read(fd));
		else if (!ft_strcmp(line, "plane"))
			ft_object_push_back(&s->obj, ft_plane_read(fd));
		else if (!ft_strcmp(line, "light"))
			ft_light_push_back(&s->light, ft_light_read(fd));
		else 
			ft_error();
	}
	if (!s->obj)
		ft_error();
}
