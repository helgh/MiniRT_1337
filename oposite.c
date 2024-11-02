/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oposite.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 21:45:37 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/11/01 21:48:19 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

t_axis	*oposite(t_axis *ax1)
{
	t_axis	*new_ax;

	new_ax = malloc(sizeof(t_axis));
	if (!new_ax)
		return (NULL);
	new_ax->x = -1 * ax1->x;
	new_ax->y = -1 * ax1->y;
	new_ax->z = -1 * ax1->z;
	new_ax->w = -1 * ax1->w;
	return (new_ax);
}