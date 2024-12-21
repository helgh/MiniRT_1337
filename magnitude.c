/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   magnitude.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 18:26:51 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/12/17 15:43:56 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

// count magnitude (lenght) of a vector //

double	magnitude(t_tuple *tuple)
{
	double	magnitude;

	magnitude = pow(tuple->x, 2);
	magnitude += pow(tuple->y, 2);
	magnitude += pow(tuple->z, 2);
	magnitude = sqrt(magnitude);
	return (magnitude);
}
