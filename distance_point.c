/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance_point.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 19:14:33 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/12/17 15:44:35 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

double	distance_point(t_tuple p1, t_tuple p2)
{
	double	distance;
	t_tuple	sub;

	sub = subtract(p1, p2);
	distance = magnitude(sub);
	return (distance);
}
