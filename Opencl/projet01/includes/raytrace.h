/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 10:47:27 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/10 14:02:40 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef RAYTRACE_H
# define RAYTRACE_H

# define NB_SPHERES 3 
# define RAY_T_MIN 0.0001
# define RAY_T_MAX 1.0e30

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
	double		red;
	double		green;
	double 		blue;
}				t_color;

typedef	struct	s_light
{
	t_vector	pos;
	t_color 	intensity;
}		t_light;

typedef struct	s_material
{
	t_color	diffuse;
	double	reflection;
}				t_material;

typedef struct	s_sphere
{
	t_vector	pos;
	double		radius;
	int			material;
}				t_sphere;

typedef struct	s_plane
{
	t_vector	pos;
	t_vector	normal;
	int			material;
}				t_plane;

typedef	struct	s_npt
{
	t_vector	n;
	t_vector	p;
	double		t;
}				t_npt;

typedef struct	s_delta
{
	double a;
	double b;
	double c;
	double delta;
}				t_delta;

typedef	struct	s_scene
{
	int			scr_width;
	int			scr_height;
	int			nb_objects;
	int			nb_spheres;
	int			nb_planes;
	int			nb_lights;
	int			nb_materials;
	t_object	obj;
	t_camera	cam;
	t_sphere	*spheres;
	t_plane		*planes;
	t_light		*lights;
	t_material	*materials;
}				t_scene;

void		ft_vector_print(t_vector v);
t_ray		ft_ray(t_vector start, t_vector dir);
t_plane		ft_plane(t_vector pos, t_vector norm, int material);
t_sphere	ft_sphere(double radius, t_vector pos, int material);
int			ft_scene_intersect(t_scene *s, t_intersect *i);
int			ft_scene_intersectl(t_scene *s, t_intersect *i);
int			ft_sphere_intersect(t_sphere *s, t_ray *r, double *t);
int			ft_plane_intersect(t_plane *plane, t_ray *r, double *t);
void		ft_scene_init(t_scene *s, char *const input_file);
void		ft_scene_init_default(t_scene *s);
void		ft_scene_clear(t_scene *s, Uint32 **pixels);
void		ft_scene_print(t_scene *s);
void		ft_scene_read(t_scene *s, int fd);
void		ft_material_read(t_scene *s, int fd, int nb_materials);
void		ft_sphere_read(t_scene *s, int fd, int nb_spheres);
void		ft_light_read(t_scene *l, int fd, int nb_lights);
#endif
