/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 10:47:27 by ebatchas          #+#    #+#             */
/*   Updated: 2019/04/23 10:10:51 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACE_H
# define RAYTRACE_H

# include "vector.h"
# include "color.h"
# include "defines.h"

typedef enum	e_type
{
	NONE = 0, SPHERE, PLANE, CYLINDRE, CONE
}				t_type;

typedef struct	s_ray
{
	t_vector	start;
	t_vector	dir;
}				t_ray;

typedef	struct	s_camera
{
	t_vector	pos;
	t_vector	rot;
	t_vector	trans;
	t_vector	look_at;
	t_vector	dir;
	t_vector	up;
	t_vector	u;
	t_vector	v;
	t_vector	horiz;
	t_vector	vert;
	t_vector	low_left;
	float		ratio;
	float		fov;
	float		h;
	float		w;
}				t_camera;

typedef	struct	s_l
{
	t_vector	pos;
	t_color		intensity;
	struct s_l	*next;
}				t_light;

typedef struct	s_material
{
	t_color		diffuse;
	float		reflection;
}				t_material;

typedef	struct	s_o
{
	t_type		type;
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
	t_ray		ray;
	t_ray		ray_light;
	float		t;
	t_vector	n;
	t_vector	p;
	t_object	*current;
}				t_intersect;

typedef	struct	s_scene
{
	t_material	curr_material;
	t_type		type;
	t_object	*obj;
	t_light		*light;
	t_camera	cam;
}				t_scene;
#endif
