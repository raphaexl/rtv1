/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 08:53:45 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/21 16:02:06 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_object		*ft_sphere_read(int fd)
{
	char		*line;
	t_object	item;

	item.angle = 0.0;
	item.name = "SPHERE";
	item.pos = ft_vector_read(fd);
	item.translate = ft_vector_read(fd);
	item.rotate = ft_vector_read(fd);
	item.translate = ft_translate_vec3(item.translate, item.pos, 0);
	item.pos = (t_vector){0.0, 0.0, 0.0};
	item.normal = ft_vector(0.0, 0.0, 0.0);
	if (ft_get_next_line(fd, &line) == 1 && line)
		item.radius = ft_atof(line);
	else
		ft_print_error("sphere radius :)");
	item.material = ft_material_read(fd);
	return (ft_object_new(SPHERE, &item));
}

t_object		*ft_cone_read(int fd)
{
	char		*line;
	t_object	item;

	item.pos = ft_vector_read(fd);
	item.name = "CONE";
	item.translate = ft_vector_read(fd);
	item.rotate = ft_vector_read(fd);
	item.translate = ft_translate_vec3(item.translate, item.pos, 0);
	item.pos = (t_vector){0.0, 0.0, 0.0};
	item.normal = ft_vector(0.0, 0.0, 0.0);
	if (ft_get_next_line(fd, &line) == 1 && line)
		item.angle = DEG_TO_RAD(ft_clamp(1.0, 79.0, ft_atof(line)));
	else
		ft_print_error("cone angle :)");
	item.material = ft_material_read(fd);
	return (ft_object_new(CONE, &item));
}

t_object		*ft_cylindre_read(int fd)
{
	char		*line;
	t_object	item;

	item.angle = 0.0;
	item.name = "CYLINDRE";
	item.pos = ft_vector_read(fd);
	item.translate = ft_vector_read(fd);
	item.rotate = ft_vector_read(fd);
	item.translate = ft_translate_vec3(item.translate, item.pos, 0);
	item.pos = (t_vector){0.0, 0.0, 0.0};
	item.normal = ft_vector(0.0, 0.0, 0.0);
	if (ft_get_next_line(fd, &line) == 1 && line)
		item.radius = ft_atof(line);
	else
		ft_print_error("cylinder radius :)");
	item.material = ft_material_read(fd);
	return (ft_object_new(CYLINDRE, &item));
}

t_object		*ft_plane_read(int fd)
{
	t_object	item;

	item.pos = ft_vector_read(fd);
	item.name = "PLANE";
	item.translate = ft_vector_read(fd);
	item.rotate = ft_vector_read(fd);
	item.translate = ft_translate_vec3(item.translate, item.pos, 0);
	item.pos = (t_vector){0.0, 0.0, 0.0};
	item.radius = 0.0;
	item.angle = 0.0;
	item.normal = ft_vector_read(fd);
	item.material = ft_material_read(fd);
	return (ft_object_new(PLANE, &item));
}

t_object		*ft_disk_read(int fd)
{
	t_object	item;
	char		*line;

	item.name = "DISQUE";
	item.pos = ft_vector_read(fd);
	item.translate = ft_vector_read(fd);
	item.translate = ft_translate_vec3(item.translate, item.pos, 0);
	item.pos = (t_vector){0.0, 0.0, 0.0};
	item.rotate = ft_vector_read(fd);
	if (ft_get_next_line(fd, &line) == 1 && line)
		item.radius = ft_atof(line);
	else
		ft_print_error("disk radius :)");
	item.angle = item.radius * item.radius;
	item.normal = ft_vector_read(fd);
	item.material = ft_material_read(fd);
	return (ft_object_new(DISK, &item));
}
