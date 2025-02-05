/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_scal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:49:00 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/02/04 20:20:23 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

static t_color	mult_by_scal(t_color col, double scal)
{
	t_color	color;

	return (color.r = col.r * scal,
		color.g = col.g * scal,
		color.b = col.b * scal, color);
}

static t_color	div_by_scal(t_color col, double scal)
{
	t_color	color;

	return (color.r = col.r / scal,
		color.g = col.g / scal,
		color.b = col.b / scal, color);
}

t_color	color_scal(t_color col, double scal, int operator)
{
	if (operator == MULT)
		return (mult_by_scal(col, scal));
	return (div_by_scal(col, scal));
}