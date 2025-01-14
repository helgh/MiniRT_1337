/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:39:30 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/01/14 12:02:49 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

double	hit(t_intersect *sec)
{
	t_intersect	*tmp;
	double		t;

	tmp = sec;
	t = *(tmp->point_sec);
	while (tmp)
	{
		if (*(tmp->point_sec) >= 0)
			if (*(tmp->point_sec) < t)
				t = *(tmp->point_sec);
		if (*(tmp->point_sec + 1) >= 0)
			if (*(tmp->point_sec + 1) < t)
				t = *(tmp->point_sec + 1);
		tmp = tmp->next;
	}
	return (t);
}
