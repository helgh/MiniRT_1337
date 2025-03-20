/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 22:36:08 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/03/19 22:54:14 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Minirt_bonus.h"

t_color	_color_pl_or_checker(t_obj_draw *obj)
{
	t_color	color;
	t_tuple	obj_space;
	double	scal;
	int		div;

	color = obj->pl->color;
	if (obj->pl->checker.exist == false)
		return (color);
	scal = obj->pl->checker.ratio;
	obj_space = mult_mat_point(obj->pl->inv_trans, obj->position);
	div = (int) fabs(floor(obj_space.x / scal) + floor(obj_space.z / scal));
	div %= 2;
	if (div == 0)
		return (color);
	return (obj->pl->checker.color);
}

t_color	_color_sp_or_checker(t_obj_draw *obj)
{
	t_color	color;
	t_tuple	obj_space;
	double	u;
	double	v;
	int		u_v_tile;

	color = obj->sp->color;
	if (obj->sp->checker.exist == false)
		return (color);
	obj_space = mult_mat_point(obj->sp->inv_trans, obj->position);
	spherical_cord(*obj, obj_space, &u, &v);
	u_v_tile = (int) floor(u * obj->sp->checker.ratio);
	u_v_tile += (int) floor(v * obj->sp->checker.ratio);
	if (u_v_tile % 2 == 0)
		return (color);
	return (obj->sp->checker.color);
}

t_color	_color_cy_or_checker(t_obj_draw *obj)
{
	t_color	color;
	double	u;
	double	v;
	int		u_v_tile;

	color = obj->cy->color;
	if (obj->cy->checker.exist == false)
		return (color);
	u = obj->position.x;
	v = obj->position.y;
	u_v_tile = (int) floor(u * obj->cy->checker.ratio);
	u_v_tile += (int) floor(v * obj->cy->checker.ratio);
	if (u_v_tile % 2 == 0)
		return (color);
	return (obj->cy->checker.color);
}
