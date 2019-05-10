/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 08:14:04 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/10 20:16:54 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void	ft_scene_init(t_scene *s, char *const input_file)
{
	char	*line;
	char	**tab;
	int		i;
	int		fd;

	fd = open(input_file, O_RDONLY);	
	if (ft_get_next_line(fd, &line) == 1 && line)
	{
		tab = ft_strsplit(line, ' ');
		s->scr_width = ft_atoi(tab[0]);
		s->scr_height = ft_atoi(tab[1]);
		i = -1;
		while (++i < 2)
			free(tab[i]), tab[i] = NULL;
		free(tab);
		tab = NULL;
		ft_scene_read(s, fd);
		ft_material_read(s, fd, s->nb_materials);
		ft_sphere_read(s, fd, s->nb_spheres);
		ft_light_read(s, fd, s->nb_lights);
		s->nb_objects = s->nb_spheres + s->nb_planes;
	}
	else
		ft_error();
}

void	ft_scene_init_default(t_scene *s)
{
	t_material materials[4];
	t_light lights[3];
	t_sphere spheres[3];
	t_plane planes[1];

	s->scr_width = 800;
	s->scr_height = 600;	
	materials[0].diffuse.red = 1;
	materials[0].diffuse.green = 0;
	materials[0].diffuse.blue = 0;
	materials[0].reflection = 0.2;

	materials[1].diffuse.red = 0;
	materials[1].diffuse.green = 1;
	materials[1].diffuse.blue = 0;
	materials[1].reflection = 0.5;

	materials[2].diffuse.red = 0;
	materials[2].diffuse.green = 0;
	materials[2].diffuse.blue = 1;
	materials[2].reflection = 0.9;

	materials[3].diffuse.red = 1;
	materials[3].diffuse.green = 0;
	materials[3].diffuse.blue = 1;
	materials[3].reflection = 0.5;

	spheres[0].pos.x = 200;
	spheres[0].pos.y = 300;
	spheres[0].pos.z = 0;
	spheres[0].radius = 100;
	spheres[0].material = 0;

	spheres[1].pos.x = 400;
	spheres[1].pos.y = 400;
	spheres[1].pos.z = 0;
	spheres[1].radius = 100;
	spheres[1].material = 1;

	spheres[2].pos.x = 500;
	spheres[2].pos.y = 140;
	spheres[2].pos.z = 0;
	spheres[2].radius = 100;
	spheres[2].material = 2;

	planes[0].pos.x = 0;
	planes[0].pos.y = 0;
	planes[0].pos.z = 0;
	planes[0].normal.x = 0;
	planes[0].normal.y = 0;
	planes[0].normal.z = 1;
	planes[0].material = 3;

	lights[0].pos.x = 512;
	lights[0].pos.y = 240;
	lights[0].pos.z = -100;
	lights[0].intensity.red = 1;
	lights[0].intensity.green = 1;
	lights[0].intensity.blue = 1;

	lights[1].pos.x = 3200;
	lights[1].pos.y = 3000;
	lights[1].pos.z = -1000;
	lights[1].intensity.red = 0.6;
	lights[1].intensity.green = 0.7;
	lights[1].intensity.blue = 1;

	lights[2].pos.x = 600;
	lights[2].pos.y = 0;
	lights[2].pos.z = -100;
	lights[2].intensity.red = 0.3;
	lights[2].intensity.green = 0.5;
	lights[2].intensity.blue = 1;

	s->nb_materials = 3;
	s->nb_spheres = 3;
	s->nb_lights = 3;
	s->nb_planes = 1;
	ft_memcpy(s->planes, planes, s->nb_planes * sizeof(t_plane));
	ft_memcpy(s->spheres, spheres, s->nb_spheres * sizeof(t_sphere));
	ft_memcpy(s->lights, lights, s->nb_lights * sizeof(t_light));
	ft_memcpy(s->materials, materials, s->nb_materials * sizeof(t_material));
	s->nb_objects = s->nb_spheres + s->nb_planes;
}

void	ft_scene_print(t_scene *s)
{
	printf("\n-----------------SCENES-----------\n");
	printf("%d\t%d\n", s->scr_width, s->scr_height);
	printf("%d\t%d\t%d\n", s->nb_materials, s->nb_spheres, s->nb_lights);
	for (int i = 0; i < s->nb_materials; i++)
		printf("%.1lf\t%.1f\t%.1f\t\t%.1f\n",s->materials[i].diffuse.red, s->materials[i].diffuse.green,
				s->materials[i].diffuse.blue, s->materials[i].reflection);
	for (int i = 0; i < s->nb_spheres; i++)
		printf("%.1lf\t%.1f\t%.1f\t\t%.1f\t\t%d\n",s->spheres[i].pos.x, s->spheres[i].pos.y, s->spheres[i].pos.z,
				s->spheres[i].radius, s->spheres[i].material);
	for (int i = 0; i < s->nb_lights; i++)
		printf("%.1lf\t%.1f\t%.1f\t\t%.1f\t\t%.1lf\t%.1f\n",s->lights[i].pos.x, s->lights[i].pos.y, s->lights[i].pos.z,
				s->lights[i].intensity.red,s->lights[i].intensity.green, s->lights[i].intensity.blue);
}

void	ft_scene_clear(t_scene *s, Uint32 **pixels)
{
	(void)s;
	free(*pixels);
	pixels = NULL;
}
