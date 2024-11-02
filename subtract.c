/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subtract.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 19:18:04 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/11/01 21:19:44 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

t_axis	*subtract(t_axis *ax1, t_axis *ax2)
{
	t_axis	*new_ax;

	new_ax = malloc(sizeof(t_axis));
	if (!new_ax)
		return (NULL);
	new_ax->x = ax1->x - ax2->x;
	new_ax->y = ax1->y - ax2->y;
	new_ax->z = ax1->z - ax2->z;
	new_ax->w = ax1->w - ax2->w;
	return (new_ax);
}
