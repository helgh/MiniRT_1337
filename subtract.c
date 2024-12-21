/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subtract.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 19:18:04 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/12/16 16:47:42 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

// Subtracting two point or Subtracting vector from a point or Subtracting two vector //
// Subtracting vector from a point is just moving backward by the given vector //
// Subtracting two vector representing the change in direction between the two //

t_tuple	*subtract(t_tuple *tuple1, t_tuple *tuple2)
{
	t_tuple	*new_tuple;

	new_tuple = malloc(sizeof(t_tuple));
	if (!new_tuple)
		return (NULL);
	new_tuple->x = tuple1->x - tuple2->x;
	new_tuple->y = tuple1->y - tuple2->y;
	new_tuple->z = tuple1->z - tuple2->z;
	new_tuple->w = tuple1->w - tuple2->w;
	return (new_tuple);
}
