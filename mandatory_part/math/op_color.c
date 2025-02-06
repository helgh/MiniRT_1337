/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:13:06 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/02/06 17:34:48 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Minirt.h"

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
		return (check_color_range(mult_color(col1, col2)));
	else if (operator == DIV)
		return (check_color_range(div_color(col1, col2)));
	else if (operator == SUB)
		return (check_color_range(sub_color(col1, col2)));
	return (check_color_range(add_color(col1, col2)));
}
