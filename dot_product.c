/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_product.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 18:49:14 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/12/18 15:58:00 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

// get a scalar value //
// use of function when start intersecting rays with objects or when compute the shading on a surface //

double	dot_product(t_tuple *vec1, t_tuple *vec2)
{
	double	result;

	result = (vec1->x * vec2->x) + (vec1->y * vec2->y) + (vec1->z * vec2->z);
	result += (vec1->w * vec2->w);
	return (result);
}
