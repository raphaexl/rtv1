/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 10:47:27 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/08 15:36:59 by ebatchas         ###   ########.fr       */
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

typedef enum	e_type
{
	NONE = 0, SPHERE, PLANE, CYLINDRE, CONE
}				t_type;


typedef	struct	s_light
{
	t_vector		pos;
	t_color 		intensity;
	struct	s_light	*next;
}		t_light;

typedef struct	s_material
{
	t_color	diffuse;
	float	reflection;
}				t_material;

typedef struct	s_sphere
{
	t_vector	pos;
	t_vector	rotation;
	t_vector	translate;
	float		radius;
	t_material	material;
}				t_sphere;

typedef struct	s_cone
{
	t_vector	pos;
	t_vector	rotation;
	t_vector	translate;
	float		angle;
	t_material	material;
}				t_cone;

typedef struct	s_plane
{
	t_vector	pos;
	t_vector	rotation;
	t_vector	translate;
	t_vector	normal;
	t_material	material;
}				t_plane;

typedef	struct	s_npt
{
	t_vector	n;
	t_vector	p;
	float		t;
}				t_npt;

typedef struct	s_delta
{
	float a;
	float b;
	float c;
	float delta;
}				t_delta;

typedef	struct	s_object
{
	t_type		type;
	float		radius;
	float		angle;
	int			id;
	char		*name;
	t_vector	pos;
	t_vector	translate;
	t_vector	rotate;
	t_vector	normal;
	t_material	material;
	struct	s_object	*next;
}				t_object;

typedef struct	s_iterm
{
	t_vector	pos;
	t_color		color;

}				t_iterm;

typedef struct	s_intersect
{
	t_ray		ray;
	t_ray		ray_light;
	float		tmax;;
	float		t;
	t_vector	n;
	t_vector	p;
	t_color		color;
	t_object	*current;
}				t_intersect;

typedef	struct	s_scene
{
	t_material	curr_material;
	t_type		type;
	t_object	*obj;
	t_light 	*light;
	t_camera	cam;
}				t_scene;

void		ft_vector_print(t_vector v);
t_ray		ft_ray(t_vector start, t_vector dir);
t_plane		ft_plane(t_vector pos, t_vector norm, t_material material);
t_sphere	ft_sphere(float radius, t_vector pos, t_material material);
int			ft_scene_intersect(t_scene *s, t_intersect *i);
int			ft_scene_intersectl(t_scene *s, t_intersect *i);
int			ft_sphere_intersect(t_object *s, t_ray *r, float *t);
int			ft_cone_intersect(t_object *s, t_ray *r, float *t);
int			ft_cylindre_intersect(t_object *plane, t_ray *r, float *t);
int			ft_plane_intersect(t_object *plane, t_ray *r, float *t);
void		ft_scene_init(t_scene *s, char *const input_file);
void		ft_parse_file(t_scene *s, int	fd);
void		ft_scene_clear(t_scene *s);
void		ft_scene_print(t_scene *s);
#endif
