/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:39:30 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/01/17 13:07:14 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

double	choise_point(t_intersect *sec)
{
	if (sec->point_sec[0] < EPSILON)
		return (sec->point_sec[1]);
	else if (sec->point_sec[1] < EPSILON)
		return (sec->point_sec[0]);
	else if (sec->point_sec[0] < sec->point_sec[1])
		return (sec->point_sec[0]);
	return (sec->point_sec[1]);
}

double	hit(t_intersect *sec)
{
	t_intersect	*tmp;
	double point_sec;
	double		t;

	tmp = sec;
	t = -1;
	while (tmp)
	{
		if (tmp->hit)
		{
			point_sec = choise_point(tmp);
			if (t < EPSILON)
				t = point_sec;
			else if (point_sec < t)
				t = point_sec;
		}
		tmp = tmp->next;
	}
	return (t);
}
