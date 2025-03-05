/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_scal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:49:00 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/03/05 16:13:27 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils.h"

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

t_color	check_color_range(t_color color)
{
	double	min;
	double	max;

	max = 1.0;
	min = 0.0;
	if (color.r < min)
		color.r = min;
	else if (color.r > max)
		color.r = max;
	if (color.g < min)
		color.g = min;
	else if (color.g > max)
		color.g = max;
	if (color.b < min)
		color.b = min;
	else if (color.b > max)
		color.b = max;
	return (color);
}

t_color	color_scal(t_color col, double scal, int operator)
{
	if (operator == MULT)
		return (mult_by_scal(col, scal));
	return (div_by_scal(col, scal));
}
