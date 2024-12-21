/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addition.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 19:14:05 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/12/16 16:38:05 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

// this function get new point for know where you would be if you followed the vector from the old point (start) //
// or //
// this function get new vec //

t_tuple	*addition(t_tuple *start, t_tuple *vec)
{
	t_tuple	*point;

	point = malloc(sizeof(t_tuple));
	if (!point)
		return (NULL);
	point->x = start->x + vec->x;
	point->y = start->y + vec->y;
	point->z = start->z + vec->z;
	point->w = start->w + vec->w;
	return (point);
}
