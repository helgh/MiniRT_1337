/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:39:30 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/11/07 15:51:41 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

double	hit(t_intersect *sec)
{
	t_intersect	*tmp;
	double		t;

	tmp = sec;
	t = -1;
	while (tmp)
	{
		if (*(tmp->point_sec) >= 0)
			t = *(tmp->point_sec);
		if (*(tmp->point_sec + 1) >= 0)
			if (*(tmp->point_sec + 1) < *(tmp->point_sec))
				t = *(tmp->point_sec + 1);
		tmp = tmp->next;
	}
	return (t);
}
