#include "../includes/rtv1.h"

t_color  ft_path_trace(t_scene *s, t_intersect *in, t_menu *m)
{
t_color c;

	(void)m;
	in->t = 20000.0f;
	if (ft_scene_intersect(s, in))
{
	c = ft_color_kmult(0.5, ft_color(in->n.x + 1.0, in->n.y + 1.0, in->n.z + 1.0));
return (c);
}
	//	c = {.red = 0.0, .green = 0.0, .blue = 0.0};//ft_background_color(&in->ray);
	return (ft_background_color(&in->ray));
}
