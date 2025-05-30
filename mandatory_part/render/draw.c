/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:48:40 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/03/20 01:51:16 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Minirt.h"

static double	rgb_to_hex(double r, double g, double b)
{
	r *= 255.0;
	g *= 255.0;
	b *= 255.0;
	return ((u_int64_t)r << 16 | (u_int64_t)g << 8 | (u_int64_t)b);
}

static void	prepare_compute(t_scene *scene, t_obj_draw *obj, t_ray ray, int op)
{
	if (op == SPHERE)
		obj->sp = &scene->sect.sp;
	else if (op == PLANE)
		obj->pl = &scene->sect.pl;
	else
		obj->cy = &scene->sect.cy;
	obj->position = point_sec(ray, scene->sect.t);
	obj->eye_v = tuple_scal(ray.direction_v, -1, OPP);
	obj->normal_v = normal_at(*obj, obj->position, op);
	obj->shadow = false;
	if (dot_product(obj->normal_v, obj->eye_v) <= 0.0)
		obj->normal_v = tuple_scal(obj->normal_v, 1, OPP);
}

static t_color	_get_final_color(t_scene *scene, t_ray ray, int object)
{
	t_obj_draw	obj;
	t_color		color;

	prepare_compute(scene, &obj, ray, object);
	if (object == SPHERE)
		color = obj.sp->color;
	else if (object == PLANE)
		color = obj.pl->color;
	else
		color = obj.cy->color;
	check_shadow(scene, &obj);
	color = lighting(scene->light, &obj, scene->ambient, color);
	return (color);
}

static t_color	color_pixel(t_scene *scene, t_ray *ray)
{
	intersect_world(scene, ray);
	if (scene->sect.exist == false)
		return (color(0.0, 0.0, 0.0));
	else if (scene->sect.type == SPHERE)
		return (_get_final_color(scene, *ray, SPHERE));
	else if (scene->sect.type == PLANE)
		return (_get_final_color(scene, *ray, PLANE));
	else if (scene->sect.type == CYLINDER)
		return (_get_final_color(scene, *ray, CYLINDER));
	return (color(0.0, 0.0, 0.0));
}

void	draw(t_scene *scene, t_mlx *mlx)
{
	t_camera	*camera;
	t_color		color;
	t_ray		ray;
	double		col;
	int			arr[3];

	camera = scene->camera;
	arr[0] = -1;
	while (++arr[0] < HEIGHT)
	{
		arr[1] = -1;
		while (++arr[1] < WIDTH)
		{
			ray = ray_for_pixel(camera, arr[1], arr[0]);
			arr[2] = (arr[0] * mlx->s_line + arr[1] * (mlx->bpp / 8));
			color = color_pixel(scene, &ray);
			col = rgb_to_hex(color.r, color.g, color.b);
			*(int *)(mlx->pixels + arr[2]) = col;
		}
	}
}
