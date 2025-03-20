/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_map_cy_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 23:20:21 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/03/19 22:52:34 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Minirt_bonus.h"

static void	cylindrical_cord(t_obj_draw obj, t_tuple poin, double *u, double *v)
{
	double	theta;

	theta = atan2(poin.x, poin.z);
	*u = (theta + M_PI) / (2.0 * M_PI);
	*v = (poin.y + obj.cy->max_min) / (obj.cy->max_min + obj.cy->max_min);
}

static double	get_height_cy(t_obj_draw obj, double u, double v)
{
	int				bump_x;
	int				bump_y;
	int				index;
	unsigned char	color;
	double			height;

	bump_x = (int) round(u * (obj.cy->text.w - 1));
	bump_y = (int) round(v * (obj.cy->text.h - 1));
	index = (bump_y * obj.cy->text.s_line + bump_x * (obj.cy->text.bpp / 8));
	color = obj.cy->text.data[index];
	height = 2.0 * (color / 255.0) - 1.0;
	return (height);
}

t_tuple	_bump_map_cylinder(t_obj_draw obj, t_tuple poin)
{
	t_tuple			new_normal_v;
	double			u;
	double			v;
	double			height;

	cylindrical_cord(obj, poin, &u, &v);
	height = get_height_cy(obj, u, v);
	new_normal_v.x = poin.x + height;
	new_normal_v.y = 0.0;
	new_normal_v.z = poin.z + height;
	new_normal_v.w = 0;
	return (normal(new_normal_v));
}
