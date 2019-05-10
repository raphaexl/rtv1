# define W_W  960
# define W_H  600
# define INFINITY 1e10
# define MAX_DEPTH 5
# define MAX_DISTANCE 1000.0f
# define NB_OPTIONS 12
# define RAND_N 3
# define DELTA_TRANS 0.5
# define DELTA_ANGLE 2
# define MAX_SOURCE_SIZE 0x1000000
# define DEG_TO_RAD(x) ((x) * (M_PI / 180.0))


typedef struct	s_delta
{
	float	a;
	float	b;
	float	c;
	float	delta;
}				t_delta;

typedef struct	s_vector
{
	float	x;
	float	y;
	float	z;
}				t_vector;

typedef struct	s_color
{
	float		red;
	float		green;
	float		blue;
}				t_color;

typedef	struct	s_camera
{
	float		ratio;
	float		fov;
	float		h;
	float		w;
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
}				t_camera;

typedef enum	e_type
{
	NONE = 0, SPHERE, PLANE, CYLINDRE, CONE
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

typedef struct	s_material
{
	int			chess;
	float		spec_cl_pow;
	float		reflection;
	float		refraction;
	t_color		diffuse;
	t_color		specular;
}				t_material;

typedef	struct	s_o
{
	float		radius;
	float		angle;
	int			id;
	t_type		type;
	char		*name;
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
	t_object	*current;
}				t_intersect;

typedef	struct	s_scene
{
	t_color		c;
	t_color		bg_color;
	t_color		ambiant;
	int			nb_samples;
	int			a;
	t_object	*obj;
	t_light		*light;
	t_camera	cam;
	//t_color		(*ft_rtv1)(global struct s_scene *, t_intersect *, int);
}				t_scene;

typedef uint32 Uint32;

t_vector		ft_vector(float x, float y, float z);
t_vector		ft_vector_sum(t_vector a, t_vector b);
t_vector		ft_vector_sub(t_vector a, t_vector b);
t_vector		ft_vector_mult(t_vector a, t_vector b);
t_vector		ft_vector_cross(t_vector a, t_vector b);
t_vector		ft_vector_kmult(float k, t_vector b);
t_vector		ft_vector_normalized(t_vector a);
float			ft_vector_norm(t_vector a);
float			ft_vector_dot(t_vector a, t_vector b);
t_vector	ft_rotate_x(t_vector r, float angle);
t_vector	ft_rotate_y(t_vector r, float angle);
t_vector	ft_rotate_z(t_vector r, float angle);
t_vector	ft_rotate_vec3(t_vector r, t_vector v, int invert);
t_vector	ft_translate_vec3(t_vector r, t_vector v, int invert);
t_vector		ft_reflect(t_vector v, t_vector n);
int				ft_refract(t_vector v, t_vector n, float ior, t_vector *r);
t_color			ft_color(float r, float g, float b);
t_color			ft_color_sum(t_color a, t_color b);
t_color			ft_color_mult(t_color a, t_color b);
t_color			ft_color_kmult(float k, t_color a);
float		ft_clamp(float min, float max, float val);
t_vector	ft_reflect(t_vector i, t_vector n);
int			ft_refract(t_vector i, t_vector n, float eta, t_vector *r);

float 		ft_rand48(void);
t_vector	ft_random_unit(void);
int			ft_lambertian_sc(t_intersect *in, t_color *att);
int			ft_metal_sc(t_intersect *in, t_color *att);
int			ft_dielectric_sc(t_intersect *in, t_color *att, float ref_idx);
t_color		ft_background_color(t_ray *r);
int			ft_reflect_light(t_intersect *in);
void		ft_floor_object(t_object *o, t_material *m, t_vector pos);
t_color		ft_light(global t_scene *s, t_intersect *in, t_material m, t_color c);

t_color		ft_trace(t_intersect *in, t_material *m, t_light *l, global t_color *a);
t_color		ft_ray_trace(global t_scene *s, t_intersect *in, int depth);
t_color			ft_edit_trace(global t_scene *s, t_intersect *in, int depth);
t_color		ft_path_trace(global t_scene *s, t_intersect *in, int depth);

int			ft_sphere_intersect(t_object *s, t_ray *r, float *t);
t_vector	ft_normal_sphere(t_object *s, t_vector p);
int			ft_sphere_compute(t_object *p, t_intersect *in);

int			ft_plane_intersect(t_object *plane, t_ray *r, float *t);
t_vector	ft_normal_plane(t_object *plane,   int ret);
int			ft_plane_compute(t_object *p, t_intersect *in);

t_vector	ft_normal_cone(t_object *cone, t_vector p);
int			ft_cone_intersect(t_object *s, t_ray *r, float *t);
int			ft_cone_compute(t_object *p, t_intersect *in);

t_vector	ft_normal_cylindre(t_object *cylindre, t_vector p);
int			ft_cylindre_intersect(t_object *plane, t_ray *r, float *t);
int			ft_cylindre_compute(t_object *p, t_intersect *in);

//t_ray		ft_camera_ray(global t_camera *cam, float x, float y);
t_ray	ft_camera_ray(int x, int  y, int w, int h);
void		ft_camera_transform(global t_camera *cam);
t_ray	ft_transform_ray(t_object *p, t_ray *ro, int invert);
uint	ft_clamp_gama(float red, float green, float blue, float factor);
int			ft_scene_intersect(global t_scene *s, t_intersect *in);
int			ft_scene_intersectl(global t_scene *s, t_intersect *in);

t_vector	ft_vector(float x, float y, float z)
{
	t_vector res;

	res.x = x;
	res.y = y;
	res.z = z;
	return (res);
}

t_vector	ft_vector_sum(t_vector a, t_vector b)
{
	t_vector res;

	res.x = a.x + b.x;
	res.y = a.y + b.y;
	res.z = a.z + b.z;
	return (res);
}

t_vector	ft_vector_sub(t_vector a, t_vector b)
{
	t_vector res;

	res.x = a.x - b.x;
	res.y = a.y - b.y;
	res.z = a.z - b.z;
	return (res);
}

t_vector	ft_vector_kmult(float k, t_vector a)
{
	t_vector res;

	res.x = k * a.x;
	res.y = k * a.y;
	res.z = k * a.z;
	return (res);
}

t_vector	ft_vector_cross(t_vector a, t_vector b)
{
	t_vector res;

	res.x = a.y * b.z - a.z * b.y;
	res.y = a.z * b.x - a.x * b.z;
	res.z = a.x * b.y - a.y * b.z;
	return (res);
}

float		ft_vector_norm(t_vector a)
{
	
	return ((float)a.x * a.x + a.y * a.y + a.z * a.z);
}

float		ft_vector_dot(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vector	ft_vector_normalized(t_vector a)
{
	t_vector	res;
	float		k;

	k = sqrtf((a.x * a.x + a.y * a.y + a.z * a.z));
	k = 1.0 / k;
	res.x = a.x * k;
	res.y = a.y * k;
	res.z = a.z * k;
	return (res);
}

t_vector	ft_reflect(t_vector v, t_vector n)
{
	t_vector	tmp;

	tmp = ft_vector_kmult(2.0 * ft_vector_dot(v, n), n);
	return (ft_vector_sub(v, tmp));
}

int			ft_refract(t_vector v, t_vector n, float ni_over_nt, t_vector *r)
{
	t_vector	uv;
	t_vector	tmp;
	float		dt;
	float		discr;

	uv = ft_vector_normalized(v);
	dt = ft_vector_dot(uv, n);
	discr = 1.0 - ni_over_nt * ni_over_nt * (1.0 - dt * dt);
	if (discr > 0.00001)
	{
		tmp = ft_vector_kmult(ni_over_nt, ft_vector_sub(uv,
					ft_vector_kmult(dt, n)));
		*r = ft_vector_sub(tmp, ft_vector_kmult(sqrt((float)discr), n));
		return (1);
	}
	else
		return (0);
}

t_vector	ft_rotate_x(t_vector r, float angle)
{
	t_vector res;

	res = (t_vector){0.0, 0.0, 0.0};
	res.x = r.x;
	res.y = r.y * cos((float)angle) - sin((float)angle) * r.z;
	res.z = r.y * sin((float)angle) + cos((float)angle) * r.z;
	return (res);
}

t_vector	ft_rotate_y(t_vector r, float angle)
{
	t_vector	res;

	res = (t_vector){0.0, 0.0, 0.0};
	res.x = r.x * cos((float)angle) + sin((float)angle) * r.z;
	res.y = r.y;
	res.z = -r.x * sin((float)angle) + cos((float)angle) * r.z;
	return (res);
}

t_vector	ft_rotate_z(t_vector r, float angle)
{
	t_vector	res;

	res = (t_vector){0.0, 0.0, 0.0};
	res.x = r.x * cos((float)angle) - sin((float)angle) * r.y;
	res.y = r.x * sin((float)angle) + cos((float)angle) * r.y;
	res.z = r.z;
	return (res);
}

t_vector	ft_rotate_vec3(t_vector r, t_vector v, int invert)
{
	if (invert)
	{
		r = ft_rotate_z(r, DEG_TO_RAD(-v.z));
		r = ft_rotate_y(r, DEG_TO_RAD(-v.y));
		r = ft_rotate_x(r, DEG_TO_RAD(-v.x));
	}
	else
	{
		r = ft_rotate_z(r, DEG_TO_RAD(v.z));
		r = ft_rotate_y(r, DEG_TO_RAD(v.y));
		r = ft_rotate_x(r, DEG_TO_RAD(v.x));
	}
	return (r);
}

t_vector	ft_translate_vec3(t_vector r, t_vector v, int invert)
{
	if (invert)
	{
		r.x -= v.x;
		r.y -= v.y;
		r.z -= v.z;
	}
	else
	{
		r.x += v.x;
		r.y += v.y;
		r.z += v.z;
	}
	return (r);
}

float	ft_clamp(float min, float max, float val)
{
	return (fmax((float)min, fmin((float)max, (float)val)));
}

float ft_rand48(void)
{
	unsigned int seed0;
	unsigned int seed1;
	seed0 = 1;
	seed1 = 3;
	seed0 = 36969 * ((seed0) & 65535) + ((seed0) >> 16);  
	seed1 = 18000 * ((seed1) & 65535) + ((seed1) >> 16);

	unsigned int ires = ((seed0) << 16) + (seed1);

	union {
		float f;
		unsigned int ui;
	} res;

	res.ui = (ires & 0x007fffff) | 0x40000000;
	return (res.f - 2.0f) / 2.0f;
}

t_color		ft_color(float r, float g, float b)
{
	t_color	color;

	color.red = r;
	color.green = g;
	color.blue = b;
	return (color);
}

t_color		ft_color_sum(t_color a, t_color b)
{
	t_color res;

	res.red = a.red + b.red;
	res.green = a.green + b.green;
	res.blue = a.blue + b.blue;
	return (res);
}

t_color		ft_color_mult(t_color a, t_color b)
{
	t_color res;

	res.red = a.red * b.red;
	res.green = a.green * b.green;
	res.blue = a.blue * b.blue;
	return (res);
}

t_color		ft_color_kmult(float k, t_color a)
{
	t_color res;

	res.red = k * a.red;
	res.green = k * a.green;
	res.blue = k * a.blue;
	return (res);
}

t_color		ft_background_color(t_ray *r)
{
	t_vector	dir;
	t_color		color;
	float		t;

	dir = ft_vector_normalized(r->dir);
	t = 0.5 * (dir.y + 1.0);
	dir = ft_vector_sum(ft_vector_kmult(1.0 - t, ft_vector(1.0, 1.0, 1.0)),
			ft_vector_kmult(t, ft_vector(0.5, 0.7, 1.0)));
	color.red = dir.x;
	color.green = dir.y;
	color.blue = dir.z;
	return (color);
}

uint	ft_clamp_gama(float red, float green, float blue, float factor)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	r = (unsigned char)fmin((float)(red * factor * 255.0), (float)255.0);
	g = (unsigned char)fmin((float)(green * factor * 255.0), (float)255.0);
	b = (unsigned char)fmin((float)(blue * factor * 255.0), (float)255.0);
	return (b + (g << 8) + (r << 16));
}

static int		ft_min_ray(float t1, float t2, float *t)
{
	if (((t1 < t2 || t2 < 0.001) && t1 > 0.1) && (t1 < *t))
	{
		*t = t1;
		return (1);
	}
	else if (((t2 < t1 || t1 < 0.001) && t2 > 0.1) && (t2 < *t))
	{
		*t = t2;
		return (1);
	}
	else
		return (0);
}

int				ft_cone_compute(t_object *p, t_intersect *in)
{
	t_ray	r;

	r = in->ray;
	r.start = ft_rotate_vec3(r.start, p->rotate, -1);
	r.dir = ft_rotate_vec3(r.dir, p->rotate, -1);
	r.start = ft_translate_vec3(r.start, p->translate, -1);
	if (!ft_cone_intersect(p, &r, &in->t))
		return (0);
	in->current = p;
	in->p = ft_vector_sum(in->ray.start, ft_vector_kmult(in->t, in->ray.dir));
	in->n = ft_normal_cone(p, ft_vector_sub(in->p, p->pos));
	return (1);
}

int				ft_cone_intersect(t_object *c, t_ray *r, float *t)
{
	t_delta		d;
	t_vector	dist;
	float		anglesin;
	float		anglecos;

	anglecos = pow((float)cos((float)c->angle), (float)2);
	anglesin = pow((float)sin((float)c->angle), (float)2);
	dist = ft_vector_sub(r->start, c->pos);
	d.a = anglecos * (r->dir.z * r->dir.z + r->dir.x * r->dir.x)
		- anglesin * (r->dir.y * r->dir.y);
	d.b = 2.0 * (anglecos * (dist.z * r->dir.z + dist.x * r->dir.x)
			- anglesin * (dist.y * r->dir.y));
	d.c = anglecos * (dist.z * dist.z + dist.x * dist.x)
		- anglesin * (dist.y * dist.y);
	d.delta = d.b * d.b - 4.0 * d.a * d.c;
	if (d.delta < 0.00000001)
		return (0);
	d.delta = sqrtf((float)d.delta);
	return (ft_min_ray((-d.b + d.delta) / (2.0 * d.a),
				(-d.b - d.delta) / (2.0 * d.a), t));
}

int				ft_cylindre_compute(t_object *p, t_intersect *in)
{
	t_ray	r;

	r = in->ray;
	r.start = ft_rotate_vec3(r.start, p->rotate, -1);
	r.dir = ft_rotate_vec3(r.dir, p->rotate, -1);
	r.start = ft_translate_vec3(r.start, p->translate, -1);
	if (!ft_cylindre_intersect(p, &r, &in->t))
		return (0);
	in->current = p;
	in->p = ft_vector_sum(in->ray.start, ft_vector_kmult(in->t, in->ray.dir));
	in->n = ft_normal_cylindre(p, ft_vector_sub(in->p, p->pos));
	in->p = ft_vector_sum(r.start, ft_vector_kmult(in->t, r.dir));
	in->n = ft_normal_cylindre(p, ft_vector_sub(in->p, p->pos));
	return (1);
}

int				ft_cylindre_intersect(t_object *c, t_ray *r, float *t)
{
	t_delta		d;
	t_vector	dist;
	float		t1;
	float		t2;

	d.a = (r->dir.x * r->dir.x + r->dir.z * r->dir.z);
	dist = ft_vector_sub(r->start, c->pos);
	d.b = 2.0 * (dist.x * r->dir.x + dist.z * r->dir.z);
	d.c = (dist.x * dist.x + dist.z * dist.z) - c->radius * c->radius;
	d.delta = d.b * d.b - 4.0 * d.a * d.c;
	if (d.delta < 0.0)
		return (0);
	d.delta = sqrt((float)d.delta);
	t1 = (-d.b + d.delta) / (2.0 * d.a);
	t2 = (-d.b - d.delta) / (2.0 * d.a);
	if (t1 > t2)
		t1 = t2;
	if (t1 > 0.001 && t1 < *t)
	{
		*t = t1;
		return (1);
	}
	return (0);
}

int			ft_plane_compute(t_object *p, t_intersect *in)
{
	t_ray	r;
	int		ret;

	r = in->ray;

	r.dir = ft_rotate_vec3(in->ray.dir, p->rotate, 0);
	//r.dir = ft_rotate_vec3(r.dir, p->rotate, 0);
return (1);
	r.start = ft_rotate_vec3(r.start, p->rotate, -1);
	r.start = ft_translate_vec3(r.start, p->translate, -1);
	

	ret = ft_plane_intersect(p, &r, &in->t);
	
	if (!ret)
		return (0);
    in->current = p;
	in->p = ft_vector_sum(in->ray.start, ft_vector_kmult(in->t, in->ray.dir));
	in->n = ft_normal_plane(p, ret);
	return (1);
}

int			ft_plane_intersect(t_object *plane, t_ray *r, float *t)
{
	float		ddn;
	t_vector	dist;
	float		t1;


	ddn = ft_vector_dot(r->dir, plane->normal);
	if (ddn == 0.000001)
		return (0);
	dist = ft_vector_sub(plane->pos, r->start);
	t1 = (ft_vector_dot(dist, plane->normal)) / ddn;
	if (t1 < *t && t1 > 0.001)
	{
		*t = t1;
		if (ddn > 0.0001)
			return (2);
		return (1);
	}
	return (0);
}

int			ft_sphere_compute(t_object *p, t_intersect *in)
{
	t_ray		r;
	t_vector	tmp;

	
	r = in->ray;
	/*r.start = ft_rotate_vec3(r.start, p->rotate, -1);
	r.dir = ft_rotate_vec3(r.dir, p->rotate, -1);

	r.start = ft_translate_vec3(r.start, p->translate, -1);*/
	if (!ft_sphere_intersect(p, &r, &in->t))
		return (0);
		return (1);
	in->current = p;
	/*in->p = ft_vector_sum(in->ray.start, ft_vector_kmult(in->t, in->ray.dir));
	tmp = ft_vector_sub(in->p, p->pos);*/
	in->p = ft_vector_sum(r.start, ft_vector_kmult(in->t, r.dir));
	tmp = ft_vector_sub(in->p, p->pos);
	in->n = ft_normal_sphere(p, tmp);
	return (1);
}


int		ft_sphere_intersect(t_object *s, t_ray *r,  float	*tt)
{
	t_vector	dist = ft_vector_sub(s->pos, r->start);
	float	b =  ft_vector_dot(dist, r->dir);
	float	c = ft_vector_dot(dist,  dist) -  s->radius * s->radius;
	float	delta = b * b - c;

	if (delta < 0.0f)
		return (0);
    else
       *tt = b - sqrt(delta);
   if (*tt < 0.0f)
	{
		*tt = b + sqrt(delta);
		if (*tt < 0.0f)
		return (0);
	}
   else
return (1);
}

/*
int			ft_sphere_intersect(t_object *s, t_ray *r, float *t)
{
	t_vector	dist;
	t_delta		d;
	float		t1;
	float		t2;

	d.a = ft_vector_dot(r->dir, r->dir);
	dist = ft_vector_sub(s->pos, r->start);
	d.b = 2.0 * ft_vector_dot(r->dir, dist);
	d.c = ft_vector_dot(dist, dist) - (s->radius * s->radius);
	d.delta = d.b * d.b - 4.0 * d.c * d.a;

	if (d.delta < 0.0001)
		return (0);

	d.delta = sqrtf(d.delta);

	t1 = (d.b + d.delta) / (2.0 * d.a);
	t2 = (d.b - d.delta) / (2.0 * d.a);

	if (t1 > t2 && t2 > 0.0001)
		t1 = t2;
	if ((t1 > 0.0000001) && (t1 < *t))
	{
		return (1);
		*t = t1;
		return (1);
	}
	//return (1);
	return (0);
}*/

t_vector	ft_normal_sphere(t_object *s, t_vector p)
{
	p = ft_translate_vec3(p, s->translate, -1);
	p = ft_rotate_vec3(p, s->rotate, -1);
	return (ft_vector_kmult(1.0 / s->radius, p));
}

t_vector	ft_normal_plane(t_object *plane, int ret)
{
	t_vector	p;

	if (ret == 1)
		p = plane->normal;
	else
		p = ft_vector_kmult(-1.0, plane->normal);
	p = ft_rotate_vec3(p, plane->rotate, -1);
    p = ft_translate_vec3(p, plane->translate, -1);
	return (ft_vector_normalized(p));
}

t_vector	ft_normal_cone(t_object *cone, t_vector p)
{
	if (p.y > 0)
		p.y = -sqrtf(p.z * p.z + p.x * p.x) * tan(cone->angle);
	else
		p.y = sqrtf(p.z * p.z + p.x * p.x) * tan(cone->angle);
	p = ft_rotate_vec3(p, cone->rotate, -1);
	p = ft_translate_vec3(p, cone->translate, -1);
	return (ft_vector_normalized(p));
}

t_vector	ft_normal_cylindre(t_object *cylindre, t_vector p)
{
	p = ft_translate_vec3(p, cylindre->translate, -1);
	p = ft_rotate_vec3(p, cylindre->rotate, -1);
	p = ft_vector_kmult(1.0 / cylindre->radius, p);
	return (ft_vector(p.x, 0.001, p.z));
}

t_ray	ft_transform_ray(t_object *p, t_ray *ro, int invert)
{
	t_ray	r;

	r.start = ft_rotate_vec3(ro->start, p->rotate, invert);
	r.dir = ft_rotate_vec3(ro->dir, p->rotate, invert);
	r.start = ft_translate_vec3(r.start, p->translate, invert);
	return (r);
}

t_vector	ft_random_unit(void)
{
	t_vector	p;

	p = (t_vector){1.0, 1.0, 1.0};
	while (p.x * p.x + p.y * p.y + p.z * p.z >= 1.0)
		p = ft_vector_sub(ft_vector_kmult(2.0, ft_vector(ft_rand48(), ft_rand48(), ft_rand48())), ft_vector(1.0, 1.0, 1.0));
	return (p);
}

int			ft_lambertian_sc(t_intersect *in, t_color *att)
{
	t_vector	target;

	in->ray.start = in->p;
	target = ft_vector_sum(ft_vector_sum(in->p, in->n), ft_random_unit());
	*att = in->current->material.diffuse;
	in->ray.dir = ft_vector_sub(target, in->p);
	return (1);
}

int			ft_metal_sc(t_intersect *in, t_color *att)
{
	t_vector	reflected;

	in->ray.start = in->p;
	reflected = ft_reflect(ft_vector_normalized(in->ray.dir), in->n);
	*att = in->current->material.diffuse;
	in->ray.dir = reflected;
	return (ft_vector_dot(reflected, in->n) > 0);
}

int			ft_dielectric_sc(t_intersect *in, t_color *att, float ref_idx)
{
	t_vector	reflected;
	t_vector	refracted;
	t_vector	out_n;
	float		ni_over_nt;

	*att = (t_color){1.0, 1.0, 1.0};
	in->ray.start = in->p;
	reflected = ft_reflect(in->ray.dir, in->n);
	if ((in->ray.dir.x * in->n.x + in->ray.dir.y * in->n.y +
				in->ray.dir.z * in->n.z) > 0.001)
	{
		out_n = (t_vector){-in->n.x, -in->n.y, -in->n.z};
		ni_over_nt = ref_idx;
	}
	else
	{
		out_n = (t_vector){in->n.x, in->n.y, in->n.z};
		ni_over_nt = 1.0 / ref_idx;
	}
	if (ft_refract(in->ray.dir, out_n, ni_over_nt, &refracted))
		in->ray.dir = refracted;
	else
		in->ray.dir = reflected;
	return (1);
}

t_color		ft_path_trace(global t_scene *s, t_intersect *in, int depth)
{
	t_color		c;

	c = (t_color){0.0, 0.0, 0.0};
	in->t = INFINITY;
	if (!ft_scene_intersect(s, in))
		return (ft_background_color(&in->ray));
	if (depth < MAX_DEPTH)
	{
		if (in->current->material.refraction > 0.0)
		{
			if (ft_dielectric_sc(in, &c, in->current->material.refraction))
				return (ft_color_mult(c, ft_path_trace(s, in, depth + 1)));
		}
		else if (in->current->material.reflection > 0.0)
		{
			if (ft_metal_sc(in, &c))
				return (ft_color_mult(c, ft_path_trace(s, in, depth + 1)));
		}
		else if (ft_lambertian_sc(in, &c))
			return (ft_color_mult(c, ft_path_trace(s, in, depth + 1)));
	}
	return (c);
}

int		ft_reflect_light(t_intersect *in)
{
	t_vector	reflect;

	reflect = ft_reflect(in->ray.dir, in->n);
	in->ray.start = ft_vector_sum(in->p, ft_vector_kmult(0.001, reflect));
	in->ray.dir = ft_vector_normalized(reflect);
	return (1);
}

void		ft_floor_object(t_object *o, t_material *m, t_vector pos)
{
	int		square;

	square = 0;
	if (o->type != PLANE)
		return ;
	if ((m)->chess)
	{
		if (o->normal.y > 0)
		square = floor(pos.x) + floor(pos.z);
		if (o->normal.z > 0)
		square = floor(pos.x) + floor(pos.y);
		if (o->normal.x > 0)
		square = floor(pos.z) + floor(pos.y);
		if (square % 2)
			(m)->diffuse = (t_color){0.0, 0.0, 0.0};
	}
}

t_color	ft_light(global t_scene *s, t_intersect *in, t_material m, t_color c)
{
	t_light			*p;
	t_vector		dist;

	p = s->light;
	ft_floor_object(in->current, &m, in->p);
	while (p)
	{
		dist = ft_vector_sub(p->pos, in->p);
		if ((ft_vector_dot(in->n, dist) <= 0.001))
		{
			p = p->next;
			continue;
		}
		if ((in->t = sqrtf(ft_vector_dot(dist, dist))) && in->t <= 0.001)
		{
			p = p->next;
			continue;
		}
		in->ray_light = (t_ray){in->p, ft_vector_kmult(1.0 / in->t, dist)};
		if (!ft_scene_intersectl(s, in))
			c = ft_color_sum(c, ft_trace(in, &m, p, &s->ambiant));
		p = p->next;
	}
	return (c);
}

t_color			ft_ray_trace(global t_scene *s, t_intersect *in, int depth)
{
	t_color		c;

	c = (t_color){0.0, 0.0, 0.0};
	in->t = INFINITY;
	if (!ft_scene_intersect(s, in))
		return (s->bg_color);
	if (depth >= MAX_DEPTH)
		return (c);
	c = ft_color_sum(c, ft_light(s, in, in->current->material, c));
	if (in->current->material.reflection > 1.0 && ft_metal_sc(in, &c))
		c = ft_color_mult(c, ft_ray_trace(s, in, depth + 1));
	else if (in->current->material.refraction > 0.0)
	{
		if (ft_dielectric_sc(in, &c, in->current->material.refraction))
			c = ft_color_mult(c, ft_ray_trace(s, in, depth + 1));
	}
	else if (in->current->material.reflection > 0.0)
	{
		ft_reflect_light(in);
		c = ft_color_sum(c, ft_color_kmult(in->current->material.reflection,
					ft_ray_trace(s, in, depth + 1)));
	}
	return (c);
}

int		ft_scene_intersect(global t_scene *s, t_intersect *in)
{
	t_object	*p;
	int			hit;

	in->current = 0;
	p = s->obj;
	while (p)
	{
	   if (p->type == SPHERE && ft_sphere_compute(p, in))
			hit = 1;
		/*else if (p->type == CONE && ft_cone_compute(p, in))
			hit = 1;
		else if (p->type == CYLINDRE && ft_cylindre_compute(p, in))
			hit = 1;
		else if ((p->type == PLANE ) && ft_plane_compute(p, in))
			hit = 1;*/
		p = p->next;
	}
	return (hit);
}

int		ft_scene_intersectl(global t_scene *s, t_intersect *in)
{
	t_object	*p;
	t_ray		r;

	p = s->obj;
	while (p)
	{
		r = ft_transform_ray(p, &in->ray_light, 1);
		if (p->type == SPHERE && ft_sphere_intersect(p, &r, &in->t))
			return (1);
		else if (p->type == CONE && ft_cone_intersect(p, &r, &in->t))
			return (1);
		else if (p->type == PLANE && ft_plane_intersect(p, &r, &in->t))
			return (1);
		else if (p->type == CYLINDRE && ft_cylindre_intersect(p, &r, &in->t))
			return (1);
		p = p->next;
	}
	return (0);
}

t_color			ft_edit_trace(global t_scene *s, t_intersect *in, int depth)
{
	in->t = INFINITY;
	(void)depth;
	if (ft_scene_intersect(s, in))
		return ((t_color){1.1, 1.5, 0.77});
	else
	    return (s->bg_color);
}


/*
t_ray		ft_camera_ray(global t_camera *cam, float x, float y)
{

   t_ray		r;
	t_vector	tmp;

	tmp = ft_vector_sum(cam->low_left, ft_vector_kmult((x) / (float)W_W,
				cam->horiz));
	tmp = ft_vector_sum(tmp, ft_vector_kmult((y) / (float)W_H, cam->vert));
	r.start = cam->pos;
	r.dir = ft_vector_normalized(ft_vector_sub(tmp, r.start));
	return (r);
}*/

t_ray	ft_camera_ray(int x, int  y, int w, int h)
{
	t_vector	f;
	t_ray		r;
	float  		aspect_ratio = (float)w / (float)h;

	float	px = ((float)x + 0.5) / (float)w;
	float	py = ((float)y + 0.5) / (float)h;
	float	p_x = 2.0 * px - 1.0;
	float	p_y = -(2.0 * py - 1.0);
	f.x = p_x * aspect_ratio * tan(M_PI / 2.0);
	f.y = p_y * tan(M_PI / 2.0);
	f.z = -1.0;
	r.start = (t_vector){0., .0, 0.0};

	r.start = (t_vector){w / 2 - x, h / 2 - y, -200.0};
	f.x = 0;
	f.y = 0;
	f.z = 1;

	r.dir = ft_vector_normalized(ft_vector_sub(f, r.start));
	return (r);
}

__kernel void		ft_render(__global t_scene *s, __global uint *pixels, unsigned int w, unsigned int h)
{
	const	int i = get_global_id(0);
	
	t_intersect	inter;

	int			x = i % W_W;
	int			y = i / W_W;

 
	s->a = s->nb_samples;
	s->c = (t_color){0.0, 0.0, 0.0};
	//while (--s->a >= 0)
	//{
		inter.ray = ft_camera_ray(x, y, w, h);
		//inter.ray = ft_camera_ray(&s->cam, x + (float)s->a / s->nb_samples, y + (float)s->a / s->nb_samples);
		s->c =  ft_edit_trace(s, &inter, 0);
	//}
	pixels[i] = ft_clamp_gama(s->c.red, s->c.green, s->c.blue, 1.0 / s->nb_samples);
}
