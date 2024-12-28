/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oposite.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 21:45:37 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/12/16 17:02:08 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

// function get oposite of some vector //

t_tuple	oposite(t_tuple tuple)
{
	t_tuple	new_tuple;

	new_tuple.x = -1 * tuple.x;
	new_tuple.y = -1 * tuple.y;
	new_tuple.z = -1 * tuple.z;
	new_tuple.w = -1 * tuple.w;
	return (new_tuple);
}
