/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 10:47:27 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/28 21:49:49 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACE_H
# define RAYTRACE_H

# include "camera.h"
# include "color.h"
# include "defines.h"

typedef enum	e_type
{
	NONE = 0, SPHERE, PLANE, CYLINDRE, CONE
}				t_type;

typedef enum	e_material_type
{
	DIFFUSE_AND_GLOSSY, REFLECTION_AND_REFRACTION, REFLECTION
}				t_material_type;

typedef	struct	s_scene	t_scene;

typedef struct	s_ray
{
	t_vector	start;
	t_vector	dir;
}				t_ray;

typedef	struct	s_l
{
	int		directional;
	t_vector	pos;
	t_vector	dir;
	t_color		intensity;
	struct s_l	*next;
}				t_light;

typedef struct	s_material
{
	t_color		diffuse;
	t_color		specular;
	float		spec_pow;
	float		reflection;
	float		refraction;
	int			chess;
}				t_material;

typedef	struct	s_o
{
	t_type		type;
	char		*name;
	int			id;
	float		radius;
	float		angle;
	t_vector	pos;
	t_vector	translate;
	t_vector	rotate;
	t_vector	normal;
	t_material	material;
	struct s_o	*next;
}				t_object;

typedef struct	s_iterm
{
	t_vector	pos;
	t_color		color;

}				t_iterm;

typedef struct	s_intersect
{
	float		t;
	t_vector	n;
	t_vector	p;
	t_ray		ray;
	t_ray		ray_light;
	t_material	*mat_ptr;
	t_object	*current;
}				t_intersect;

typedef	struct	s_scene
{
	int		nb_samples;
	t_mode		mode;
	t_color		background;
	t_color		ambiant;
	t_camera	cam;
	t_object	*obj;
	t_light		*light;
	t_color		(*ft_rtv1)(t_scene *, t_intersect *, int);
}				t_scene;
#endif
