/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_scal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 12:57:57 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/01/29 15:19:03 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

static t_tuple	mult_by_scal(t_tuple tuple, double scalar)
{
	t_tuple	new_tuple;

	return (new_tuple.x = tuple.x * scalar,
		new_tuple.y = tuple.y * scalar,
		new_tuple.z = tuple.z * scalar,
		new_tuple.w = tuple.w,
		new_tuple);
}

static t_tuple	div_by_scal(t_tuple tuple, double scalar)
{
	t_tuple	new_tuple;

	return (new_tuple.x = tuple.x / scalar,
		new_tuple.y = tuple.y / scalar,
		new_tuple.z = tuple.z / scalar,
		new_tuple.w = tuple.w / scalar,
		new_tuple);
}

static t_tuple	oposite(t_tuple tuple)
{
	t_tuple	op;

	return (op.x = tuple.x * -1.0,
		op.y = tuple.y * -1.0,
		op.z = tuple.z * -1.0,
		op.w = tuple.w, op);
}

t_tuple	tuple_scal(t_tuple tuple, double scal, int operator)
{
	if (operator == MULT)
		return (mult_by_scal(tuple, scal));
	else if (operator == DIV)
		return (div_by_scal(tuple, scal));
	return (oposite(tuple));
}
