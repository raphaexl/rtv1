/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 10:47:27 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/10 20:23:47 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef RAYTRACE_H
# define RAYTRACE_H


# include <SDL2/SDL.h>
# include "camera.h"

typedef enum	e_reflection
{
	DIFF, REF, GRASS
}				t_reflection;

typedef enum	e_object
{
	NONE = 0, SPHERE, PLANE, TRIANGLE, CONE
}				t_object;

typedef struct	s_color
{
	cl_float		red;
	cl_float		green;
	cl_float 		blue;
}				t_color;

typedef	struct	s_light
{
	t_vector	pos;
	t_color 	intensity;
}		t_light;

typedef struct	s_material
{
	cl_float	reflection;
	t_color	diffuse;
}				t_material;

typedef struct	s_sphere
{
	cl_int			material;
	cl_float		radius;
	t_vector	pos;
}				t_sphere;

typedef struct	s_plane
{
	cl_int			material;
	t_vector	pos;
	t_vector	normal;
}				t_plane;

typedef	struct	s_npt
{
	cl_float		t;
	t_vector	n;
	t_vector	p;
}				t_npt;

typedef struct	s_delta
{
	cl_float a;
	cl_float b;
	cl_float c;
	cl_float delta;
}				t_delta;

typedef	struct	s_scene
{
	cl_int			scr_width;
	cl_int			scr_height;
	cl_int			nb_objects;
	cl_int			nb_spheres;
	cl_int			nb_planes;
	cl_int			nb_lights;
	cl_int			nb_materials;
	t_object	obj;
	t_camera	cam;
	t_sphere	spheres[N_MAX];
	t_plane		planes[N_MAX];
	t_light		lights[N_MAX];
	t_material	materials[N_MAX];
}				t_scene;

void		ft_vector_print(t_vector v);
t_ray		ft_ray(t_vector start, t_vector dir);
t_plane		ft_plane(t_vector pos, t_vector norm, cl_int material);
t_sphere	ft_sphere(cl_float radius, t_vector pos, cl_int material);
cl_int			ft_scene_intersect(t_scene *s, t_intersect *i);
cl_int			ft_scene_intersectl(t_scene *s, t_intersect *i);
cl_int			ft_sphere_intersect(t_sphere *s, t_ray *r, cl_float *t);
cl_int			ft_plane_intersect(t_plane *plane, t_ray *r, cl_float *t);
void		ft_scene_init(t_scene *s, char *const input_file);
void		ft_scene_init_default(t_scene *s);
void		ft_scene_clear(t_scene *s, cl_uint **pixels);
void		ft_scene_print(t_scene *s);
void		ft_scene_read(t_scene *s, cl_int fd);
void		ft_material_read(t_scene *s, cl_int fd, cl_int nb_materials);
void		ft_sphere_read(t_scene *s, cl_int fd, cl_int nb_spheres);
void		ft_light_read(t_scene *l, cl_int fd, cl_int nb_lights);
#endif
