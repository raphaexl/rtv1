#include "../includes/prototypes.h"

double	ft_clamp(double x)
{
	return (x < 0 ? 0 : x > 1 ? 1 : x);
}

int		ft_roundint(double x)
{
	return ((int) pow(ft_clamp(x), 1 / 2.2) * 255 + .5);
}

t_ray	ft_ray(t_vector start, t_vector dir)
{
	t_ray res;

	res.start = start;
	res.dir = dir;
	return (res);
}
