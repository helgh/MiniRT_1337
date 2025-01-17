/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:00:20 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/01/17 14:58:32 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

t_color	check_col(t_color color)
{
	double	min;
	double	max;

	max = 1.0;
	min = 0.0;
    if (color.r < min) color.r = min; if (color.r > max) color.r = max;
    if (color.g < min) color.g = min; if (color.g > max) color.g = max;
    if (color.b < min) color.b = min; if (color.b > max) color.b = max;
	return (color);
}

static t_color	color_by_scalar(t_color color, double scalar)
{
	t_color	new_color;

	new_color.r = color.r * scalar;
	new_color.g = color.g * scalar;
	new_color.b = color.b * scalar;
	return (new_color);
}

t_color	op_color(t_color col1, t_color col2, char operator, double scalar)
{
	t_color	new_color;

	if (operator == '*')
	{
		new_color.r = col1.r * col2.r;
		new_color.g = col1.g * col2.g;
		new_color.b = col1.b * col2.b;
		return (new_color);
	}
	else if (operator == '+')
	{
		new_color.r = col1.r + col2.r;
		new_color.g = col1.g + col2.g;
		new_color.b = col1.b + col2.b;
		return (new_color);
	}
	else if (operator == '-')
	{
		new_color.r = col1.r - col2.r;
		new_color.g = col1.g - col2.g;
		new_color.b = col1.b - col2.b;
		return (new_color);
	}
	return (color_by_scalar(col1, scalar));
}
