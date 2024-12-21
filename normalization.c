/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalization.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 18:40:52 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/12/17 10:45:09 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

// Normalization is the process of taking an arbitrary vector and converting it into a unit vector //
// turn vector into a unit vector while preserving its direction //

t_tuple	*normal(t_tuple *tuple)
{
	t_tuple	*new_tuple;
	double	magn;

	new_tuple = malloc(sizeof(t_tuple));
	if (!new_tuple)
		return (NULL);
	magn = magnitude(tuple);
	new_tuple->x = tuple->x / magn;
	new_tuple->y = tuple->y / magn;
	new_tuple->z = tuple->z / magn;
	return (new_tuple);
}
