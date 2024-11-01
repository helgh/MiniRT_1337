/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addition.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 19:14:05 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/11/01 18:28:31 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

t_axis	*addition(t_axis *point, t_axis *vec)
{
	t_axis	*poin;

	poin = malloc(sizeof(t_axis));
	if (!poin)
		return (NULL);
	poin->x = point->x + vec->x;
	poin->y = point->y + vec->y;
	poin->z = point->z + vec->z;
	poin->w = 1;
	return (poin);
}
