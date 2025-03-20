/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_map_pl_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 23:19:51 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/03/19 22:52:16 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Minirt_bonus.h"

static double	get_height_pl(t_obj_draw obj, t_tuple poin, \
	double *u, double *v)
{
	unsigned char	color;
	int				index;
	double			height;
	int				bump_x;
	int				bump_y;

	poin.x /= 20.0;
	poin.z /= 20.0;
	*u = fmod(poin.x, 1.0);
	*v = fmod(poin.z, 1.0);
	if (*u < 0)
		*u += 1.0;
	if (*v < 0)
		*v += 1.0;
	bump_x = (int) round(*u * (obj.pl->text.w - 1));
	bump_y = (int) round(*v * (obj.pl->text.h - 1));
	index = (bump_y * obj.pl->text.s_line + \
		bump_x * (obj.pl->text.bpp / 8));
	color = obj.pl->text.data[index];
	height = 2.0 * (color / 255.0) - 1.0;
	return (height);
}

t_tuple	_bump_map_plane(t_obj_draw obj, t_tuple poin)
{
	t_tuple			new_normal_v;
	double			u;
	double			v;
	double			height;

	poin = mult_mat_point(obj.pl->inv_trans, poin);
	height = get_height_pl(obj, poin, &u, &v);
	new_normal_v.x = height;
	new_normal_v.y = 1.0;
	new_normal_v.z = height;
	new_normal_v.w = 0.0;
	return (normal(new_normal_v));
}
