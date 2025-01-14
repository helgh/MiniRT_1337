/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mult_by_scalar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 22:02:04 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/01/14 11:49:44 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

t_tuple	mult_by_scalar(t_tuple tuple, double scalar)
{
	t_tuple	new_tuple;

	new_tuple.x = tuple.x * scalar;
	new_tuple.y = tuple.y * scalar;
	new_tuple.z = tuple.z * scalar;
	new_tuple.w = tuple.w;
	return (new_tuple);
}
