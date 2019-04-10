#include "../includes/rtv1.h"

float	ft_rand48(void)
{
	static int	initialized = 0;

	if (!initialized)
	{
		initialized = 1;
		srand(time(NULL));
	}
	return ((float)rand() / (float)RAND_MAX);
}
