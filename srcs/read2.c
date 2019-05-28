/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 11:27:51 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/22 16:16:16 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_object		*ft_box_read(int fd)
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

t_object		*ft_torus_read(int fd)
{
	t_object	item;
	char		*line;

	item.name = "TORUS";
	item.pos = ft_vector_read(fd);
	item.translate = ft_vector_read(fd);
	item.translate = ft_translate_vec3(item.translate, item.pos, 0);
	item.pos = ft_vector(0.0, 0.0, 0.0);
	item.rotate = ft_vector_read(fd);
	if (ft_get_next_line(fd, &line) == 1 && line)
		item.radius = ft_atof(line);
	else
		ft_print_error("torus Radius :)");
	if (ft_get_next_line(fd, &line) == 1 && line)
		item.angle = ft_atof(line);
	else
		ft_print_error("torus radius :)");
	item.normal = (t_vector){0.0, 0.0, 0.0};
	item.material = ft_material_read(fd);
	return (ft_object_new(TORUS, &item));
}

t_object		*ft_cube_read(int fd)
{
	t_object	item;
	char		*line;

	item.name = "CUBE";
	item.pos = ft_vector_read(fd);
	item.normal = (t_vector){0.0, 0.0, 0.0};
	item.translate = ft_vector_read(fd);
	item.translate = ft_translate_vec3(item.translate, item.pos, 0);
	item.pos = ft_vector(0.0, 0.0, 0.0);
	item.rotate = ft_vector_read(fd);
	if (ft_get_next_line(fd, &line) == 1 && line)
		item.radius = ft_atof(line);
	else
		item.radius = 11.8;
	item.angle = 0.0;
	item.material = ft_material_read(fd);
	return (ft_object_new(CUBE, &item));
}

t_light			*ft_light_read(int fd)
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
