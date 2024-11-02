/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mult_by_scalar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 22:02:04 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/11/01 22:05:12 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

t_axis	*mult_by_scalar(t_axis *ax, double scalar)
{
	t_axis	*new_ax;

	new_ax = malloc(sizeof(t_axis));
	if (!new_ax)
		return (NULL);
	new_ax->x = ax->x * scalar;
	new_ax->y = ax->y * scalar;
	new_ax->z = ax->z * scalar;
	new_ax->w = ax->w * scalar;
	return (new_ax);
}
