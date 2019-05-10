typedef struct	s_ray
{
	float3 		start;
	float3 		dir;
}				t_ray;

typedef	struct	s_material
{
	float3		diffuse;
	float3		emission;
}				t_material;

typedef struct	s_sphere
{
	float3		pos;
	float		radius;
	t_material	mat;
}				t_sphere;

typedef	struct	s_camera
{
	float3		pos;
	float3		cam;
}				t_camera;

t_ray	ft_camera_ray(int x, int  y, int w, int h)
{
	float3	f;
	t_ray	r;
	float  aspect_ratio = (float)w / (float)h;

	float	px = ((float)x + 0.5) / (float)w;
	float	py = ((float)y + 0.5) / (float)h;
	float	p_x = 2.0 * px - 1.0;
	float	p_y = -(2.0 * py - 1.0);
	f.x = p_x * aspect_ratio * tan(M_PI / 2.0);
	f.y = p_y * tan(M_PI / 2.0);
	f.z = -1.0;
	r.start = (float3){0., .0, 0.0};

	r.start = (float3){w / 2 - x, h / 2 - y, -200.0};
	f.x = 0;
	f.y = 0;
	f.z = 1;

	r.dir = normalize(f - r.start);
	return (r);
}

int		ft_sphere_intersect(t_sphere s, t_ray r,  float	*tt)
{
	float3	dist = s.pos - r.start;
	float	b =  dot(dist, r.dir);
	float	c = dot(dist,  dist) -  s.radius * s.radius;
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

__kernel void vector_add (__global  float3 *output, unsigned int w, unsigned int h)
{
	const	int		i = get_global_id(0);
	t_ray	r;
	float	tt;
	float	cosinus = 0.0;
	float3	color = {0.240, 0.142, 0.78};
	t_sphere	s = (t_sphere){{0.0, 0.0, -3.0}, 2., {{1.0, 0.2, 0.7}, {0.3, 0.2, 0.8}}};
	int		x = i % w;
	int		y = i / w;

	tt = 1e10;
	r = ft_camera_ray(x, y, w, h);
	if (ft_sphere_intersect(s, r, &tt))
	{
		float3 p = r.start + r.dir * tt;
		float3 normal = normalize(p - s.pos);
        cosinus = -1.0 * dot(normal, r.dir);
		color = cosinus * s.mat.diffuse;
	}
	output[i] = color;

}
