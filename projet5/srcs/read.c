/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 08:53:45 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/28 22:00:25 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_vector		ft_vector_read(int fd)
{
	char		*line;
	char		**tab;
	t_vector	vect;
	int			i;

	i = -1;
	vect.x = 0;
	if (ft_get_next_line(fd, &line) == 1 && line)
	{
		if ((tab = ft_strsplit(line, ' ')) && ft_tab_len(tab) != 3)
			ft_error();
		vect.x = atof(tab[0]);
		vect.y = atof(tab[1]);
		vect.z = atof(tab[2]);
		while (++i < 3)
			free(tab[i]);
		free(tab);
		tab = NULL;
	}
	return (vect);
}

t_color		ft_color_read(int fd)
{
	t_color		c;
	char		*line;
	char		**tab;
	int			i;

	i = -1;
	c.red = 0;
	if (ft_get_next_line(fd, &line) == 1 && line)
	{
		if ((tab = ft_strsplit(line, ' ')) && ft_tab_len(tab) != 3)
			ft_error();
		c.red = atof(tab[0]);
		c.green = atof(tab[1]);
		c.blue = atof(tab[2]);
		while (++i < 3)
			free(tab[i]);
		free(tab);
		tab = NULL;
	}
	return (c);
}

t_material		ft_material_read(int fd)
{
	char		*line;
	t_material	material;
	char		**tab;
	int			i;

	i = -1;
	material.diffuse.blue = 1.0;
	material.diffuse = ft_color_read(fd);
	material.specular = ft_color_read(fd);
	if (ft_get_next_line(fd, &line) == 1 && line)
		material.spec_pow = atof(line);
	if (ft_get_next_line(fd, &line) == 1 && line)
	{
		if ((tab = ft_strsplit(line, ' ')) && ft_tab_len(tab) != 3)
			ft_error();
		material.reflection = atof(tab[0]);
		material.refraction = atof(tab[1]);
		material.chess = atoi(tab[2]);
		while (++i < 3)
			free(tab[i]);
		free(tab);
		tab = NULL;
		return (material);
	}
	else
		ft_error();
	return (material);
}

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
		ft_error();
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
		iterm.angle = DEG_TO_RAD(ft_clamp(1.0, 89.0, atof(line)));
	else
		ft_error();
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
		ft_error();
	iterm.material = ft_material_read(fd);
	return (ft_object_new(CYLINDRE, &iterm));
}
