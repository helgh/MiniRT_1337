/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:13:06 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/01/29 15:31:52 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

static t_color	check_color(t_color color)
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

static t_color	mult_color(t_color col1, t_color col2)
{
	t_color	new;

	return (new.r = col1.r * col2.r,
		new.g = col1.g * col2.g,
		new.b = col1.b * col2.b, new);
}

static t_color	add_color(t_color col1, t_color col2)
{
	t_color	new;

	return (new.r = col1.r + col2.r,
		new.g = col1.g + col2.g,
		new.b = col1.b + col2.b, new);
}

static t_color	sub_color(t_color col1, t_color col2)
{
	t_color	new;

	return (new.r = col1.r - col2.r,
		new.g = col1.g - col2.g,
		new.b = col1.b - col2.b, new);
}

static t_color	div_color(t_color col1, t_color col2)
{
	t_color	new;

	return (new.r = col1.r / col2.r,
		new.g = col1.g / col2.g,
		new.b = col1.b / col2.b, new);
}

t_color	op_color(t_color col1, t_color col2, char operator)
{
	if (operator == MULT)
		return (check_color(mult_color(col1, col2)));
	else if (operator == DIV)
		return (check_color(div_color(col1, col2)));
	else if (operator == SUB)
		return (check_color(sub_color(col1, col2)));
	return (check_color(add_color(col1, col2)));
}
