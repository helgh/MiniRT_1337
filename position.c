/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 22:09:05 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/01/15 11:05:01 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

t_tuple	position(t_ray *ray, double t)
{
	t_tuple	vec;

	vec = op_tuple(ray->direction_v, ray->direction_v, '*', t);
	return (op_tuple(ray->origin_p, vec, '+', 1));
}
