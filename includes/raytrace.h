/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 10:47:27 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/22 18:16:34 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACE_H
# define RAYTRACE_H

# include "camera.h"
# include "color.h"
# include "defines.h"

typedef enum	e_type
{
	NONE = 0, SPHERE, CONE, CYLINDRE, BOX, PLANE, DISK, TORUS, CUBE
}				t_type;

typedef struct	s_ray
{
	t_vector	start;
	t_vector	dir;
}				t_ray;

typedef	struct	s_l
{
	t_vector	pos;
	t_vector	dir;
	t_color		intensity;
	struct s_l	*next;
}				t_light;

typedef struct	s_texture
{
	int		w;
	int		h;
	Uint32	*data;
}				t_texture;

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
	t_material	material;
	t_vector	pos;
	t_vector	translate;
	t_vector	rotate;
	t_vector	scale;
	t_vector	normal;
	float		radius;
	float		angle;
	int			id;
	t_type		type;
	char		*name;
	struct s_o	*next;
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
	t_vector	n;
	t_vector	p;
	float		t;
	t_object	*current;
}				t_intersect;

typedef	struct	s_scene
{
	t_camera	cam;
	t_color		c;
	t_color		bg_color;
	t_color		ambiant;
	int			nb_samples;
	int			a;
	t_object	*obj;
	t_light		*light;
	t_texture	*earth;
	t_color		(*ft_rtv1)(struct s_scene *, t_intersect *, int);
}				t_scene;
#endif
