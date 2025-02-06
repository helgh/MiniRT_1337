/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_tuple.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:13:32 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/02/06 17:30:16 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Minirt.h"

static t_tuple	mult_tuple(t_tuple p1, t_tuple p2)
{
	t_tuple	new;

	return (new.x = p1.x * p2.x,
		new.y = p1.y * p2.y,
		new.z = p1.z * p2.z,
		new.w = p1.w * p2.w, new);
}

static t_tuple	add_tuple(t_tuple p1, t_tuple p2)
{
	t_tuple	new;

	return (new.x = p1.x + p2.x,
		new.y = p1.y + p2.y,
		new.z = p1.z + p2.z,
		new.w = p1.w + p2.w, new);
}

static t_tuple	sub_tuple(t_tuple p1, t_tuple p2)
{
	t_tuple	new;

	return (new.x = p1.x - p2.x,
		new.y = p1.y - p2.y,
		new.z = p1.z - p2.z,
		new.w = p1.w - p2.w, new);
}

static t_tuple	div_tuple(t_tuple p1, t_tuple p2)
{
	t_tuple	new;

	return (new.x = p1.x / p2.x,
		new.y = p1.y / p2.y,
		new.z = p1.z / p2.z,
		new.w = p1.w / p2.w, new);
}

t_tuple	op_tuple(t_tuple tuple1, t_tuple tuple2, int operator)
{
	if (operator == MULT)
		return (mult_tuple(tuple1, tuple2));
	else if (operator == ADD)
		return (add_tuple(tuple1, tuple2));
	else if (operator == SUB)
		return (sub_tuple(tuple1, tuple2));
	return (div_tuple(tuple1, tuple2));
}
