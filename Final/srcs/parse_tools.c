/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 13:09:08 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/30 19:19:16 by ebatchas         ###   ########.fr       */
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

t_color			ft_color_read(int fd)
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
	else
		ft_error();
	if (ft_get_next_line(fd, &line) != 1 && (!line))
		ft_print_error("material properties :)");
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
