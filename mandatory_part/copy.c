#include "stdio.h"
#include "math.h"

typedef struct s_tuple
{
	double	x;
	double	y;
	double	z;
	double	w;
}	t_tuple;

t_tuple	normal(t_tuple tuple)
{
	double	mag;

	mag = sqrt(pow(tuple.x, 2) + pow(tuple.y, 2) + pow(tuple.z, 2));
	tuple.x = tuple.x / mag;
	tuple.y = tuple.y / mag;
	tuple.z = tuple.z / mag;
	return (tuple);
}

t_tuple	oposite(t_tuple tuple)
{
	tuple.x = -1 * tuple.x;
	tuple.y = -1 * tuple.y;
	tuple.z = -1 * tuple.z;
	tuple.w = tuple.w;
	tuple = normal(tuple);
	return (tuple);
}

int main()
{
	t_tuple tuple;
	tuple.x = 1;
	tuple.y = 2;
	tuple.z = 3;
	tuple.w = 4;
	tuple = oposite(tuple);
	printf("tuple.x: %f tuple.y: %f tuple.z: %f tuple.w: %f\n", tuple.x, tuple.y, tuple.z, tuple.w);
	return (0);
}