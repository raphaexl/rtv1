# define RAY_T_MIN 0.0001
# define RAY_T_MAX 1.0e30
# define N_MAX  20

typedef enum	e_object
{
	NONE = 0, SPHERE, PLANE, TRIANGLE, CONE
}				t_object;

typedef struct	s_delta
{
	float a;
	float b;
	float c;
	float delta;
}				t_delta;

typedef struct 	s_vector
{
	float x;
	float y;
	float z;
}		t_vector;

typedef struct	s_color
{
	float		red;
	float		green;
	float 		blue;
}				t_color;

typedef struct	s_ray
{
	t_vector	start;
	t_vector	dir;
}				t_ray;

typedef struct	s_intersect
{
	int			id;
	float		t;
	t_vector	n;
	t_vector	p;
	t_ray		ray;
	t_ray		ray_light;
}				t_intersect;

typedef struct	s_material
{
	float	reflection;
	t_color	diffuse;
}				t_material;

typedef struct	s_sphere
{
	int			material;
	float		radius;
	t_vector		pos;
}				t_sphere;

typedef struct	s_plane
{
	int			material;
	t_vector	pos;
	t_vector	normal;
}				t_plane;

typedef	struct	s_light
{
	t_vector	pos;
	t_color 	intensity;
}		t_light;

typedef	struct	s_camera
{
	t_vector		pos;
	t_vector		cam;
}				t_camera;

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
	t_sphere	spheres[N_MAX];
	t_plane		planes[N_MAX];
	t_light		lights[N_MAX];
	t_material	materials[N_MAX];
}				t_scene;

t_vector	ft_vector(float x, float y, float z);
t_vector	ft_vector_sum(t_vector a, t_vector b);
t_vector	ft_vector_sub(t_vector a, t_vector b);
t_vector	ft_vector_mult(t_vector a, t_vector b);
t_vector	ft_vector_cross(t_vector a, t_vector b);
t_vector	ft_vector_kmult(float k, t_vector b);
t_vector	ft_vector_multk(t_vector a, float k);
t_vector	ft_vector_div(t_vector a, float k);
t_vector	ft_vector_normalized(t_vector a);
float		ft_vector_norm2(t_vector a);
float		ft_vector_norm(t_vector a);
float		ft_vector_dot(t_vector a, t_vector b);


uint	ft_clamp_gama(float red, float green, float blue, float factor);
t_ray	ft_camera_ray(int x, int  y, int w, int h);
int		ft_sphere_intersect(t_sphere s, t_ray r,  float	*tt);
int		ft_plane_intersect(t_plane plane, t_ray r, float *t);
int		ft_scene_intersect(t_scene s, t_intersect *i);
int		ft_scene_intersectl(t_scene s, t_intersect *i);
t_color	ft_ray_trace(t_scene	s, t_intersect *in);

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

t_ray	ft_camera_ray(int x, int  y, int w, int h)
{
	t_vector	f;
	t_ray	r;
	float  aspect_ratio = (float)w / (float)h;

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

t_vector	ft_vector_div(t_vector a, float k)
{
	t_vector res;

	res.x = a.x / k;
	res.y = a.y / k;
	res.z = a.z / k;
	return (res);
}

t_vector	ft_vector_mult(t_vector a, t_vector b)
{
	t_vector res;

	res.x = a.x * b.x;
	res.y = a.y * b.y;
	res.z = a.z * b.z;
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

t_vector	ft_vector_multk(t_vector a, float k)
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


t_vector	ft_vector_normalized(t_vector a)
{	t_vector res;
	float	 k;

	k = sqrt(ft_vector_norm2(a));
	res.x = a.x / k;
	res.y = a.y / k;
	res.z = a.z / k;
	return (res);
}

float	ft_vector_norm2(t_vector a)
{
	return (a.x * a.x + a.y * a.y + a.z * a.z);
}

float	ft_vector_norm(t_vector a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

float	ft_vector_dot(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

int			ft_sphere_intersect(t_sphere s, t_ray r, float *t)
{
	t_vector	dist;
	t_delta		d;
	float 		t1;
	float		t2;

	return (1);
	d.a = ft_vector_dot(r.dir, r.dir);
	dist = ft_vector_sub(r.start, s.pos);
	d.b = 2 * ft_vector_dot(r.dir, dist);
	d.c = ft_vector_dot(dist, dist) - (s.radius * s.radius);
	d.delta = d.b * d.b - 4 * d.a * d.c;
	if (d.delta < 0)
		return (0);
	d.delta = sqrt(d.delta);
	t1 = (-d.b + d.delta) / 2.0;
	t2 = (-d.b - d.delta) / 2.0;
	if (t1 > t2)
		t1 = t2;
	if ((t1 > 0.001) && (t1 < *t))
	{	
		*t = t1;
		return (1);	
	}
	return (0);
}

int			ft_plane_intersect(t_plane plane, t_ray r, float *t)
{
	float		ddn;
	t_vector	h1;

	ddn = ft_vector_dot(r.dir, plane.normal);
	if (ddn == 0.0)
		return (0);
	h1 = ft_vector_sub(plane.pos, r.start);
	*t = ft_vector_dot(h1, plane.normal) / ddn;
	if (*t <= RAY_T_MIN || *t >= RAY_T_MAX)
		return (0);
	return (1);
}

int		ft_scene_intersect(t_scene s, t_intersect *in)
{
	int		i;
	int		hit;

	i = -1;
	hit = 0;
	while (++i < s.nb_objects)
	{
		if (i < s.nb_spheres && ft_sphere_intersect(s.spheres[i], in->ray, &in->t))
		{
			in->id = i;
			s.obj = SPHERE;
			hit = 1;
			in->p = ft_vector_sum(in->ray.start, ft_vector_kmult(in->t, in->ray.dir));
			in->n = ft_vector_sub(in->p, s.spheres[i].pos);
			break ;
		}
		else if (i < s.nb_planes && ft_plane_intersect(s.planes[i], in->ray, &in->t))
			{
			s.obj = PLANE;
			in->id = i;
			hit = 1;
			in->p = ft_vector_sum(in->ray.start, ft_vector_kmult(in->t, in->ray.dir));
			in->n = ft_vector_sub(in->p, s.planes[i].pos);
			}
	}
	return (hit);
}

int		ft_scene_intersectl(t_scene s, t_intersect *in)
{
	int		i;
	int		hit;

	i = -1;
	hit = 0;
	while (++i < s.nb_objects)
	{
		if (i < s.nb_spheres && ft_sphere_intersect(s.spheres[i], in->ray_light, &in->t))
		{
			s.obj = SPHERE;
			hit = 1;
			break ;
		}
		else if (i < s.nb_planes && ft_plane_intersect(s.planes[i], in->ray_light, &in->t))
		{
			s.obj = PLANE;
			hit = 1;
			break ;
		}
	}
	return (hit);
}

t_color		ft_ray_trace(t_scene	s, t_intersect *in)
{
	t_color	c = {1.0f, 1.0f, 1.0f};
	int level = 0;
	float coef = 1.0;
	int			id = -1;
	if (ft_scene_intersect(s, in) && in->id >= 0)
		return (s.materials[s.spheres[in->id].material].diffuse);
	else
		return ((t_color){1.0, 0.0, 0.0});
	while (coef > 0.0f && level < 15)
	{
		id = -1;
		in->t = 20000.0f;
		if (ft_scene_intersect(s, in))
			id = in->id;
		if (id == -1 || s.obj == NONE)
			break;
		float    temp = ft_vector_dot(in->n, in->n);
		if (temp == 0)
			break;
		temp = 1.0 / sqrt(temp);
		in->n = ft_vector_kmult(temp, in->n);
		t_material curr_material;
		if (s.obj == SPHERE)
			curr_material = s.materials[s.spheres[id].material];
		if (s.obj == PLANE)
		{
			curr_material = s.materials[s.planes[id].material];
		}
		int j = -1;
		while (++j < s.nb_lights)
		{
			t_light curr_light = s.lights[j];
			t_vector dist = ft_vector_sub(curr_light.pos, in->p);
			if (ft_vector_dot(in->n, dist) <= 0.0f)
			{
				continue;
			}
			float t = sqrt(ft_vector_dot(dist, dist));
			if (t <= 0.0f)
				continue;
			in->ray_light = (t_ray){in->p, ft_vector_kmult(1 / t, dist)};
			in->t = t;
			int in_shadow = ft_scene_intersectl(s, in);
			if (!in_shadow)
			{
				float lambert = ft_vector_dot(in->ray_light.dir, in->n) * coef;
				c.red += lambert * curr_light.intensity.red * curr_material.diffuse.red;
				c.green += lambert * curr_light.intensity.green * curr_material.diffuse.green;
				c.blue += lambert * curr_light.intensity.blue * curr_material.diffuse.blue;
			}
		}
		coef *= curr_material.reflection;
		in->ray.start = in->p;
		float reflected = 2.0f * ft_vector_dot(in->ray.dir, in->n);
		t_vector tmp = ft_vector_kmult(reflected, in->n);
		in->ray.dir = ft_vector_sub(in->ray.dir, tmp);
		level++;
	}
	return (c);
}

__kernel void ft_render(__global  uint *output, t_scene s, unsigned int w, unsigned int h)
{
	const	int		i = get_global_id(0);
	int		x = i % w;
	int		y = i / w;
	t_intersect	inter;
	t_ray	r;
	t_color	color = {0.240, 0.142, 0.78};

	r = ft_camera_ray(x, y, w, h);
	inter.ray.start.x = x;
	inter.ray.start.y = y;
	inter.ray.start.z = -10000;
	inter.ray.dir.x = 0.0;
	inter.ray.dir.y = 0.0;
	inter.ray.dir.z = 1.0;
	if (s.nb_objects == 6)
		color = ft_ray_trace(s, &inter);
	output[i] = ft_clamp_gama(color.red, color.green, color.blue, 1.0);
}
