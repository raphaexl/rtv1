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

t_color  ft_path_trace(t_scene *s, t_intersect *in, t_menu *m)
{
t_color c;
t_vector target;

	(void)m;
	in->t = 20000.0f;
	if (ft_scene_intersect(s, in))
{
      in->ray.start = in->p;
      target = ft_vector_sum(ft_vector_sum(in->p, in->n), ft_random_unit());
      in->ray.dir = ft_vector_sub(target, in->p);
	return (ft_color_kmult(0.5, ft_path_trace(s, in, m)));
}
else
	return (ft_background_color(&in->ray));
}
