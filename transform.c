/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:28:58 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/11/07 17:35:27 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

int	count_size(double **a)
{
	int	i;

	i = -1;
	while (a[++i])
		;
	return (i);
}

t_ray	*transform_ray(t_ray *ray, double **a)
{
	t_ray	*new_ray;

	new_ray = malloc(sizeof(t_tuple));
	if (!new_ray)
		return (NULL);
	new_ray->origin_p = mult_mat_point(a, ray->origin_p);
	new_ray->direction_v = mult_mat_point(a, ray->direction_v);
	return (new_ray);
}

double	**transform_sphere(t_sphere *sp, t_tuple *tr, double angle, int flag)
{
	if (flag == TRANSLATING)
		sp->trans = translation(tr->x, tr->y, tr->z, tr->w);
	else if (flag == SCALING)
		sp->trans = scaling(tr->x, tr->y, tr->z, tr->w);
	else if (flag == ROTATE_X)
		sp->trans == rotate_x(angle);
	else if (flag == ROTATE_Y)
		sp->trans == rotate_y(angle);
	else if (flag == ROTATE_Z)
		sp->trans == rotate_Z(angle);
	return (sp->trans);
}

int main()
{
	t_intersect	*ins;
	t_ray		*ray;
	t_sphere	*sp;
	t_tuple		*tr;
	t_tuple		*o;
	t_tuple		*d;

	tr = malloc(sizeof(t_tuple));
	o = malloc(sizeof(t_tuple));
	d = malloc(sizeof(t_tuple));
	ray = malloc(sizeof(t_ray));
	sp = malloc(sizeof(t_sphere));
	ins = malloc(sizeof(t_intersect));
	tr->x = 2;
	tr->y = 2;
	tr->z = 2;
	tr->w = 1;
	o->x = 0;
	o->y = 0;
	o->z = -5;
	o->w = 1;
	d->x = 0;
	d->y = 0;
	d->z = 1;
	d->w = 0;
	ray->origin_p = o;
	ray->direction_v = d;
	ins = intersect_sphere(sp, ray, SCALING);
	//trans = transform_object(sp, tr, SCALING);
	//t_ray	*new_ray = transform_ray(ray, trans);

	printf("%f\n", ins->point_sec[0]);
	printf("%f\n", ins->point_sec[1]);
	//printf("%f\n", new_ray->origin_p->x);
	//printf("%f\n", new_ray->origin_p->y);
	//printf("%f\n", new_ray->origin_p->z);
	//printf("%f\n", new_ray->origin_p->w);
	//printf("%f\n", new_ray->direction_v->x);
	//printf("%f\n", new_ray->direction_v->y);
	//printf("%f\n", new_ray->direction_v->z);
	//printf("%f\n", new_ray->direction_v->w);
}