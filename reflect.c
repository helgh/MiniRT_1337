/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:17:33 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/01/13 10:38:12 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

t_tuple	reflect(t_tuple in, t_tuple normal)
{
	double	n;

	n = 2 * dot_product(in, normal);
	return (subtract(in, mult_by_scalar(normal, n)));
}
