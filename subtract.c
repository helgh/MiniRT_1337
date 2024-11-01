/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subtract.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 19:18:04 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/11/01 19:13:51 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

t_axis	*subtract(t_axis *ax1, t_axis *ax2)
{
	t_axis	*point;
	t_axis	*vec;

	if (ax1->w == 1 && ax2 == 0)
	{
		point = malloc(sizeof(t_axis));
		if (!point)
			return (NULL);
		point->x = ax1->x - ax2->x;
		point->y = ax1->y - ax2->y;
		point->z = ax1->z - ax2->z;
		point->w = 1;
		return (point);
	}
	else
	{
		vec = malloc(sizeof(t_axis));
		if (!vec)
			return (NULL);
		vec->x = ax1->x - ax2->x;
		vec->y = ax1->y - ax2->y;
		vec->z = ax1->z - ax2->z;
		vec->w = 0;
	}
	return (vec);
}
