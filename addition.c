/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addition.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 19:14:05 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/11/01 21:13:17 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

t_axis	*addition(t_axis *ax1, t_axis *ax2)
{
	t_axis	*poin;

	poin = malloc(sizeof(t_axis));
	if (!poin)
		return (NULL);
	poin->x = ax1->x + ax2->x;
	poin->y = ax1->y + ax2->y;
	poin->z = ax1->z + ax2->z;
	poin->w = ax1->w + ax2->w;
	return (poin);
}
