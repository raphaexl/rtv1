/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 08:53:45 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/25 12:47:57 by ebatchas         ###   ########.fr       */
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

t_material		ft_material_read(int fd)
{
	char		*line;
	t_material	material;
	char		**tab;
	int			i;

	i = -1;
	material.diffuse.blue = 1.0;
	if (ft_get_next_line(fd, &line) == 1 && line)
	{
		if ((tab = ft_strsplit(line, ' ')) && ft_tab_len(tab) != 6)
			ft_error();
		material.diffuse.red = atof(tab[0]);
		material.diffuse.green = atof(tab[1]);
		material.diffuse.blue = atof(tab[2]);
		material.reflection = atof(tab[3]);
		material.refraction = atof(tab[4]);
		material.chess = atoi(tab[5]);
		while (++i < 6)
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
		iterm.angle = atof(line);
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
