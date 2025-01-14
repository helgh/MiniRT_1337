/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_product.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 18:49:14 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/01/14 11:47:27 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

// get a scalar value //
// use of function when start intersecting rays with objects or when compute the shading on a surface //

double	dot_product(t_tuple vec1, t_tuple vec2)
{
	double	result;

	result = (vec1.x * vec2.x) + (vec1.y * vec2.y) + (vec1.z * vec2.z);
	return (result);
}
