/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 21:09:23 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/27 17:22:03 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_object	*ft_plane_read(int fd)
{
	t_object	iterm;

	iterm.pos = ft_vector_read(fd);
	iterm.translate = ft_vector_read(fd);
	iterm.rotate = ft_vector_read(fd);
	iterm.radius = 0.0;
	iterm.angle = 0.0;
	iterm.normal = ft_vector_read(fd);
	iterm.material = ft_material_read(fd);
	return (ft_object_new(PLANE, &iterm));
}

t_light		*ft_light_read(int fd)
{
	char		*line;
	char		**tab;
	t_iterm		iterm;
	int			i;

	if (ft_get_next_line(fd, &line) == 1 && line)
	{
		if ((tab = ft_strsplit(line, ' ')) && ft_tab_len(tab) != 6)
			ft_print_error("invalid light paramters");
		iterm.pos.x = atof(tab[0]);
		iterm.pos.y = atof(tab[1]);
		iterm.pos.z = atof(tab[2]);
		iterm.color.red = atof(tab[3]);
		iterm.color.green = atof(tab[4]);
		iterm.color.blue = atof(tab[5]);
		i = -1;
		while (++i < 6)
			free(tab[i]);
		free(tab);
		tab = NULL;
	}
	else
		ft_error();
	return (ft_light_new(iterm.pos, iterm.color));
}

t_camera	ft_camera_read(int fd)
{
	char		*line;
	char		**tab;
	t_camera	cam;
	int			i;

	cam.pos = ft_vector_read(fd);
	cam.rot = ft_vector_read(fd);
	if (ft_get_next_line(fd, &line) == 1 && line)
	{
		if ((tab = ft_strsplit(line, ' ')) && ft_tab_len(tab) != 1)
			ft_print_error("invalid fov paramter");
		cam.fov = atof(tab[0]);
		i = -1;
		while (++i < 1)
			free(tab[i]);
		free(tab);
		tab = NULL;
	}
	else
		ft_error();
	return (ft_camera_new(cam.pos, cam.rot, ft_vector(0.0, 1.0, 0.0), cam.fov));
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
		else if (!ft_strcmp(line, "light"))
			ft_light_push_back(&s->light, ft_light_read(fd));
		else if (!ft_strcmp(line, "camera"))
			s->cam = ft_camera_read(fd);
		else
			ft_error();
	}
	if (!s->obj)
		ft_print_error("missing  objects :)");
}
