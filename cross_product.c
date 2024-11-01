/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cross_product.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 18:49:14 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/10/24 18:57:41 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

t_axis	*cross_product(t_axis *vec1, t_axis *vec2)
{
	t_axis	*vec3;

	vec3->x = (vec1->y * vec2->z) - (vec1->z * vec2->y);
	vec3->y = (vec1->x * vec2->z) - (vec1->z * vec2->x);
	vec3->z = (vec1->x * vec2->y) - (vec1->y * vec2->x);
	return (vec3);
}
