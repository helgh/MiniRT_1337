#include "Minirt.h"

int main()
{
	t_ray *ray = malloc(sizeof(t_ray));
	t_axis	*or = malloc(sizeof(t_axis));
	t_axis	*dir = malloc(sizeof(t_axis));

	ray->origin_p = or;
	ray->direction_v = dir;
	ray->origin_p->x = 0;
	ray->origin_p->y = 0;
	ray->origin_p->z = -5;
	ray->origin_p->w = 1;
	ray->direction_v->x = 0;
	ray->direction_v->y = 0;
	ray->direction_v->z = 1;
	ray->direction_v->w = 0;

	t_sphere *sp;

	sp = malloc(sizeof(t_sphere));
	sp->cord = malloc(sizeof(t_axis));
	sp->cord->x = 5;
	sp->cord->y = 0;
	sp->cord->z = 0;
	sp->cord->w = 1;
	sp->trans = translation(5, 0, 0, 1);
	// int i = -1;
	// while (++i < 4)
	// {
	// 	int s = -1;
	// 	while (++s < 4)
	// 		printf("%f -- ", sp->trans[i][s]);
	// 	printf("\n");
	// }
	t_intersect *sec = intersect_sphere(sp, ray);

	// printf("%d\n", sec->nbr_sec);
	// printf("%f\n", *sec->point_sec);
	// printf("%f\n", *(sec->point_sec + 1));
}
