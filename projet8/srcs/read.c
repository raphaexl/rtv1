/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 08:53:45 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/05 15:51:52 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_object		*ft_sphere_read(int fd)
{
	char		*line;
	t_object	iterm;

	iterm.angle = 0.0;
	iterm.pos = ft_vector_read(fd);
	iterm.translate = ft_vector_read(fd);
	iterm.rotate = ft_vector_read(fd);
	iterm.normal = ft_vector(0.0, 0.0, 0.0);
	if (ft_get_next_line(fd, &line) == 1 && line)
		iterm.radius = atof(line);
	else
		ft_print_error("sphere radius :)");
	iterm.material = ft_material_read(fd);
	return (ft_object_new(SPHERE, &iterm));
}

t_object		*ft_cone_read(int fd)
{
	char		*line;
	t_object	iterm;

	iterm.pos = ft_vector_read(fd);
	iterm.translate = ft_vector_read(fd);
	iterm.rotate = ft_vector_read(fd);
	iterm.normal = ft_vector(0.0, 0.0, 0.0);
	if (ft_get_next_line(fd, &line) == 1 && line)
		iterm.angle = DEG_TO_RAD(ft_clamp(1.0, 189.0, atof(line)));
	else
		ft_print_error("cone angle :)");
	iterm.material = ft_material_read(fd);
	return (ft_object_new(CONE, &iterm));
}

t_object		*ft_cylindre_read(int fd)
{
	char		*line;
	t_object	iterm;

	iterm.angle = 0.0;
	iterm.pos = ft_vector_read(fd);
	iterm.translate = ft_vector_read(fd);
	iterm.rotate = ft_vector_read(fd);
	iterm.normal = ft_vector(0.0, 0.0, 0.0);
	if (ft_get_next_line(fd, &line) == 1 && line)
		iterm.radius = atof(line);
	else
		ft_print_error("cylinder radius :)");
	iterm.material = ft_material_read(fd);
	return (ft_object_new(CYLINDRE, &iterm));
}

t_object		*ft_plane_read(int fd)
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

t_light			*ft_light_read(int fd)
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
		ft_print_error("light invalid :)");
	return (ft_light_new(iterm.pos, iterm.color));
}
