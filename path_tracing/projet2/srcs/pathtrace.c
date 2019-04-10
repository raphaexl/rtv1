#include "../includes/rtv1.h"

t_vector	ft_random_unit(void)
{
t_vector	p = {1.0, 1.0, 1.0};
	while (p.x * p.x + p.y * p.y + p.z * p.z >= 1.0)
	{
		p = ft_vector_sub(ft_vector_kmult(2.0, ft_vector(ft_rand48(),ft_rand48(),ft_rand48())), ft_vector(1.0, 1.0, 1.0));
	}
return (p);
}

t_vector ft_reflect(t_vector v, t_vector n)
{
	t_vector tmp;
    tmp = ft_vector_kmult(2.0 * ft_vector_dot(v, n), n);
   return (ft_vector_sub(v, tmp));
}

int	ft_lambertian_sc(t_intersect *in, t_color *att)
{
 t_vector target;
 in->ray.start = in->p;    
 target = ft_vector_sum(ft_vector_sum(in->p, in->n), ft_random_unit());
 *att = in->current->material.diffuse;
in->ray.dir = ft_vector_sub(target, in->p);
  return (1);
}

int	ft_metal_sc(t_intersect *in, t_color *att)
{
 t_vector reflected;
 in->ray.start = in->p;    
 reflected = ft_reflect(ft_vector_normalized(in->ray.dir), in->n);
 *att = in->current->material.diffuse;
in->ray.dir = reflected;
  return (ft_vector_dot(reflected, in->n) > 0);
}


t_color  ft_path_trace(t_scene *s, t_intersect *in, t_menu *m, int depth)
{
t_color c;


	(void)m;
	in->t = 20000.0f;
	if (ft_scene_intersect(s, in))
{
if (depth < 50)
{
      if (in->current->material.reflection > 0.5)
{
      if (ft_metal_sc(in, &c))
	return (ft_color_mult(c, ft_path_trace(s, in, m, depth + 1)));
	else
		return(ft_color(0.0, 0.0, 0.0));
}
     else if (ft_lambertian_sc(in, &c))
	return (ft_color_mult(c, ft_path_trace(s, in, m, depth + 1)));
	else
		return(ft_color(0.0, 0.0, 0.0));
}
}
else
	return (ft_background_color(&in->ray));
}
