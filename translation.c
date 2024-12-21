/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:15:47 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/12/20 17:27:59 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

double	**translation(double x, double y, double z, double w)
{
	double	**tr;

	tr = identity_matrix();
	tr[0][3] = x;
	tr[1][3] = y;
	tr[2][3] = z;
	tr[3][3] = w;
	return (tr);
}

// int main()
// {
// 	double	**tr;
// 	t_tuple	*point;
// 	t_tuple	*new_point;

// 	tr = translation(5, -3, 2, 1);
// 	tr = inverse(tr);
// 	point->x = -3;
// 	point->y = 4;
// 	point->z = 5;
// 	point->w = 0;
// 	new_point = mult_mat_point(tr, point);
// 	printf("x = %2.f\n", new_point->x);
// 	printf("y = %2.f\n", new_point->y);
// 	printf("z = %2.f\n", new_point->z);
// 	printf("w = %2.f\n", new_point->w);
// }
