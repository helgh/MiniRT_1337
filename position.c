/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 22:09:05 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/11/01 19:23:10 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

t_tuple	position(t_ray *ray, double t)
{
	t_tuple	vec;

	vec = mult_by_scalar(ray->direction_v, t);
	return (addition(ray->origin_p, vec));
}
