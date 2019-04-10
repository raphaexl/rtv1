/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 08:53:45 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/08 15:43:16 by ebatchas         ###   ########.fr       */
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
		tab = ft_strsplit(line, ' ');
		vect.x = atof(tab[0]);
		vect.y = atof(tab[1]);
		vect.z = atof(tab[2]);
		while (++i < 3)
			free(tab[i]), tab[i] = NULL;
		free(tab);
		tab = NULL;
	}
	return (vect);
}

t_color		ft_color_read(int fd)
{
	char		*line;
	char		**tab;
	t_color		color;
	int			i;

	i = -1;
	color.red = 0.5;
	if (ft_get_next_line(fd, &line) == 1 && line)
	{
		tab = ft_strsplit(line, ' ');
		color.red = atof(tab[0]);
		color.green = atof(tab[1]);
		color.blue = atof(tab[2]);
		while (++i < 3)
			free(tab[i]), tab[i] = NULL;
		free(tab);
		tab = NULL;
	}
	return (color);
}


t_material	ft_material_read(int fd)
{
	char		*line;
	t_material	material;
	char		**tab;
	int			i;

	i = -1;
	material.diffuse.blue = 1.0;
	if (ft_get_next_line(fd, &line) == 1 && line)
	{
		tab = ft_strsplit(line, ' ');
		material.diffuse.red = atof(tab[0]);
		material.diffuse.green = atof(tab[1]);
		material.diffuse.blue = atof(tab[2]);
		material.reflection = atof(tab[3]);
		while (++i < 4)
			free(tab[i]), tab[i] = NULL;
		free(tab);
		tab = NULL;
		return (material);
	}
	else
		ft_error();
	return (material);
}

t_object	*ft_sphere_read(int fd)
{
	char		*line;
	t_object 	iterm;;

	iterm.angle = 0.0;
	iterm.pos = ft_vector_read(fd);
	iterm.translate = ft_vector_read(fd);
	iterm.rotate = ft_vector_read(fd);
	iterm.normal = ft_vector(0.0, 0.0, 0.0);
	if (ft_get_next_line(fd, &line) == 1 && line)
		iterm.radius = atof(line);
	iterm.material = ft_material_read(fd);
	return (ft_object_new(SPHERE, &iterm));
}

t_object	*ft_cone_read(int fd)
{
	char		*line;
	t_object 	iterm;;

	iterm.pos = ft_vector_read(fd);
	iterm.translate = ft_vector_read(fd);
	iterm.rotate = ft_vector_read(fd);
	iterm.normal = ft_vector(0.0, 0.0, 0.0);
	if (ft_get_next_line(fd, &line) == 1 && line)
		iterm.angle = atof(line);
	iterm.material = ft_material_read(fd);
	return (ft_object_new(CONE, &iterm));
}

t_object	*ft_cylindre_read(int fd)
{
	char		*line;
	t_object 	iterm;;

	iterm.angle = 0.0;
	iterm.pos = ft_vector_read(fd);
	iterm.translate = ft_vector_read(fd);
	iterm.rotate = ft_vector_read(fd);
	iterm.normal = ft_vector(0.0, 0.0, 0.0);
	if (ft_get_next_line(fd, &line) == 1 && line)
		iterm.radius = atof(line);
	iterm.material = ft_material_read(fd);
	return (ft_object_new(CYLINDRE, &iterm));
}

t_object	*ft_plane_read(int fd)
{
	t_object 	iterm;

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
	t_iterm 	iterm;
	int			i;

	if (ft_get_next_line(fd, &line) == 1 && line)
	{
		tab = ft_strsplit(line, ' ');
		iterm.pos.x = atof(tab[0]);
		iterm.pos.y = atof(tab[1]);
		iterm.pos.z = atof(tab[2]);
		iterm.color.red = atof(tab[3]);
		iterm.color.green = atof(tab[4]);
		iterm.color.blue = atof(tab[4]);
		i = -1;
		while (++i < 6)
			free(tab[i]), tab[i] = NULL;
		free(tab);
		tab = NULL;
	}
	else
		ft_error();
	return (ft_light_new(iterm.pos, iterm.color));
}
