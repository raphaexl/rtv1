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

int  ft_refract(t_vector v, t_vector n, float ni_over_nt, t_vector *r)
{
	t_vector uv = ft_vector_normalized(v);
	t_vector tmp;
	float	dt = ft_vector_dot(uv, n);
	float	discr = 1.0 - ni_over_nt *  ni_over_nt * (1.0 - dt * dt);
  if(discr > 0.00001)
   {
tmp = ft_vector_kmult(ni_over_nt, ft_vector_sub(uv, ft_vector_kmult(dt, n)));
 *r = ft_vector_sub(tmp, ft_vector_kmult(sqrtf(discr), n));
return (1);
}
else
	return (0);
}

float	ft_schlick(float cosine, float ref_idx)
{
 float ro = (1.0 - ref_idx) / (1.0 + ref_idx);
ro = ro * ro;
return (ro + (1.0 - ro) * pow((1.0 - cosine), 5.0));
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

int	ft_dielectric_sc(t_intersect *in, t_color *att, float ref_idx)
{
 t_vector reflected;
 t_vector refracted;
 t_vector out_n;
 float ni_over_nt;
float  cosine;
float	reflect_prob;

*att = (t_color){1.0, 1.0, 1.0};
 in->ray.start = in->p;    
 reflected = ft_reflect(in->ray.dir, in->n);
 if ((in->ray.dir.x * in->n.x + in->ray.dir.y * in->n.y + in->ray.dir.z * in->n.z) > 0.001)
{
   out_n = (t_vector){-in->n.x, -in->n.y, -in->n.z};
  ni_over_nt = ref_idx;
 cosine = ref_idx * ft_vector_dot(in->ray.dir, in->n) * 1.0 / ft_vector_norm(in->ray.dir);
}
else
{
 out_n = (t_vector){in->n.x, in->n.y, in->n.z};
  ni_over_nt = 1.0 / ref_idx;
cosine = -ft_vector_dot(in->ray.dir, in->n) * 1.0 / ft_vector_norm(in->ray.dir);
}
if (ft_refract(in->ray.dir, out_n, ni_over_nt, &refracted))
{
reflect_prob = ft_schlick(cosine, ref_idx);
}
else
{
reflect_prob = 1.0;

}
if (ft_rand48() < reflect_prob)
 in->ray.dir = reflected;
else
 in->ray.dir = refracted;
  return (1);
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
  if (in->current->material.reflection > 1.0)
{
      if (ft_dielectric_sc(in, &c, in->current->material.reflection))
	return (ft_color_mult(c, ft_path_trace(s, in, m, depth + 1)));
	else
		return(ft_color(0.0, 0.0, 0.0));
}
      else if (in->current->material.reflection > 0.5)
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
