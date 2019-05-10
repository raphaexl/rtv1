/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 08:53:45 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/10 18:37:09 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void	ft_error(void)
{
	write(1, "Error\n", 6);
	exit(EXIT_FAILURE);
}

void	ft_scene_read(t_scene *s, int fd)
{
	char	*line;
	char	**tab;
	int		i;

	if (ft_get_next_line(fd, &line) == 1 && line)
	{
		tab = ft_strsplit(line, ' ');
		s->nb_materials = ft_atoi(tab[0]);
		s->nb_spheres = ft_atoi(tab[1]);
		s->nb_lights = ft_atoi(tab[2]);
		i = -1;
		while (++i < 3)
			free(tab[i]), tab[i] = NULL;
		free(tab);
		tab = NULL;
	}
	else
		ft_error();
}

void	ft_material_read(t_scene *s, int fd, int nb_materials)
{
	char	*line;
	char	**tab;
	int		i;
	int		j;

	j = -1;
	while (++j < nb_materials)
	{
	if (ft_get_next_line(fd, &line) == 1 && line)
	{
		tab = ft_strsplit(line, ' ');
		s->materials[j].diffuse.red = atof(tab[0]);
		s->materials[j].diffuse.green = atof(tab[1]);
		s->materials[j].diffuse.blue = atof(tab[2]);
		s->materials[j].reflection = atof(tab[3]);
		i = -1;
		while (++i < 4)
			free(tab[i]), tab[i] = NULL;
		free(tab);
		tab = NULL;
	}
	else
		ft_error();
	}
}

void	ft_sphere_read(t_scene *s, int fd, int nb_spheres)
{
	char	*line;
	char	**tab;
	int		i;
	int		j;

	j = -1;
	while (++j < nb_spheres)
	{
	if (ft_get_next_line(fd, &line) == 1 && line)
	{
		tab = ft_strsplit(line, ' ');
		s->spheres[j].pos.x = atof(tab[0]);
		s->spheres[j].pos.y = atof(tab[1]);
		s->spheres[j].pos.z = atof(tab[2]);
		s->spheres[j].radius = atof(tab[3]);
		s->spheres[j].material = atoi(tab[4]);
		i = -1;
		while (++i < 5)
			free(tab[i]), tab[i] = NULL;
		free(tab);
		tab = NULL;
	}
	else
		ft_error();
	}
}

void	ft_light_read(t_scene *s, int fd, int nb_lights)
{	
	char	*line;
	char	**tab;
	int		i;
	int		j;

	j = -1;
	while (++j < nb_lights)
	{
	if (ft_get_next_line(fd, &line) == 1 && line)
	{
		tab = ft_strsplit(line, ' ');
		s->lights[j].pos.x = atof(tab[0]);
		s->lights[j].pos.y = atof(tab[1]);
		s->lights[j].pos.z = atof(tab[2]);
		s->lights[j].intensity.red = atof(tab[3]);
		s->lights[j].intensity.green = atof(tab[4]);
		s->lights[j].intensity.blue = atof(tab[4]);
		i = -1;
		while (++i < 6)
			free(tab[i]), tab[i] = NULL;
		free(tab);
		tab = NULL;
	}
	else
		ft_error();
	}
}

