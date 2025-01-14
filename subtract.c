/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subtract.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 19:18:04 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/12/29 18:00:45 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

// Subtracting two point or Subtracting vector from a point or Subtracting two vector //
// Subtracting vector from a point is just moving backward by the given vector //
// Subtracting two vector representing the change in direction between the two //

t_tuple	subtract(t_tuple p_v1, t_tuple p_v2)
{
	t_tuple	new_p_v;

	new_p_v.x = p_v1.x - p_v2.x;
	new_p_v.y = p_v1.y - p_v2.y;
	new_p_v.z = p_v1.z - p_v2.z;
	new_p_v.w = p_v1.w - p_v2.w;
	return (new_p_v);
}
