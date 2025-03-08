/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_map_sp_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 22:33:43 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/03/08 00:45:31 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Minirt_bonus.h"

void	spherical_cord(t_obj_draw obj, t_tuple obj_p, \
	double *u, double *v)
{
	double	theta;
	double	phi;

	(void) obj;
	theta = atan2(obj_p.z, obj_p.x);
	phi = acos(obj_p.y);
	*u = (theta + M_PI) / (2.0 * M_PI);
	*v = (M_PI - phi) / M_PI;
}

static double	get_height_sp(t_obj_draw obj, double u, double v)
{
	int				bump_x;
	int				bump_y;
	int				index;
	unsigned char	color;
	double			f_heght;

	bump_x = (int) round(u * (obj.sp->text->w - 1));
	bump_y = (int) round((1 - v) * (obj.sp->text->h - 1));
	index = (bump_y * obj.sp->text->s_line + bump_x * (obj.sp->text->bpp / 8));
	color = obj.sp->text->data[index];
	f_heght = 2.0 * (color / 255.0) - 1.0;
	return (f_heght);
}

t_tuple	_bump_map_sphere(t_obj_draw obj, t_tuple obj_p)
{
	t_tuple	new_normal_v;
	double	u;
	double	v;
	double	height;

	obj_p = normal(obj_p);
	spherical_cord(obj, obj_p, &u, &v);
	height = get_height_sp(obj, u, v);
	new_normal_v.x = obj_p.x + height;
	new_normal_v.y = obj_p.y + height;
	new_normal_v.z = obj_p.z;
	new_normal_v.w = 0;
	return (normal(new_normal_v));
}
