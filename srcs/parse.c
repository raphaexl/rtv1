/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 21:09:23 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/20 17:07:51 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_camera	ft_camera_read(int fd)
{
	char		*line;
	char		**tab;
	t_camera	cam;
	int			i;

	cam.pos = ft_vector_read(fd);
	cam.pos.z += 0.0001;
	cam.rot = ft_vector_read(fd);
	if (ft_get_next_line(fd, &line) == 1 && line)
	{
		if ((tab = ft_strsplit(line, ' ')) && ft_tab_len(tab) != 1)
			ft_print_error("invalid fov paramter");
		cam.fov = ft_atof(tab[0]);
		i = -1;
		while (++i < 1)
			free(tab[i]);
		free(tab);
		tab = NULL;
	}
	else
		ft_print_error("camera settings :)");
	return (ft_camera_new(cam.pos, cam.rot, ft_vector(0.0, 1.0, 0.0), cam.fov));
}

t_object	*ft_box_read(int fd)
{
	t_object	item;

	item.name = "BOX";
	item.pos = ft_vector_read(fd);
	item.translate = ft_vector_read(fd);
	item.rotate = ft_vector_read(fd);
	item.translate = ft_translate_vec3(item.translate, item.pos, 0);
	item.pos = ft_vector(-1.0, -1.0, -1.0);
	item.normal = ft_vector(1.0, 1.0, 1.0);
	item.radius = 0.0;
	item.angle = 0.0;
	item.material = ft_material_read(fd);
	return (ft_object_new(BOX, &item));
}

t_light		*ft_light_read(int fd)
{
	char		*line;
	char		**tab;
	t_iterm		item;
	int			i;

	if (ft_get_next_line(fd, &line) == 1 && line)
	{
		if ((tab = ft_strsplit(line, ' ')) && ft_tab_len(tab) != 6)
			ft_print_error("invalid light paramters");
		item.pos.x = ft_atof(tab[0]);
		item.pos.y = ft_atof(tab[1]);
		item.pos.z = ft_atof(tab[2]);
		item.color.red = ft_atof(tab[3]);
		item.color.green = ft_atof(tab[4]);
		item.color.blue = ft_atof(tab[5]);
		i = -1;
		while (++i < 6)
			free(tab[i]);
		free(tab);
		tab = NULL;
	}
	else
		ft_print_error("light invalid :)");
	return (ft_light_new(item.pos, item.color));
}

void		ft_parse_file(t_scene *s, int fd)
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
		else if (!ft_strcmp(line, "disque"))
			ft_object_push_back(&s->obj, ft_disk_read(fd));
		else if (!ft_strcmp(line, "box"))
			ft_object_push_back(&s->obj, ft_box_read(fd));
		else if (!ft_strcmp(line, "light"))
			ft_light_push_back(&s->light, ft_light_read(fd));
		else if (!ft_strcmp(line, "camera"))
			s->cam = ft_camera_read(fd);
		else if (!ft_strcmp(line, "background"))
			s->bg_color = ft_color_read(fd);
		else
			ft_print_error(ft_strjoin("Unrecognized components name :)", line));
	}
}
