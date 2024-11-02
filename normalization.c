/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalization.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 18:40:52 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/11/01 22:38:23 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

t_axis	*normal(t_axis *point)
{
	t_axis	*new_ax;
	double	magn;

	new_ax = malloc(sizeof(t_axis));
	if (!new_ax)
		return (NULL);
	magn = magnitude(point);
	if (!magn)
		return (NULL);
	new_ax->x = point->x / magn;
	new_ax->y = point->y / magn;
	new_ax->z = point->z / magn;
	return (new_ax);
}
