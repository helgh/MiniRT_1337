/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scaling.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:45:26 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/12/20 17:46:26 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

double	**scaling(double x, double y, double z, double w)
{
	double	**scaling;
	int		i;
	int		s;

	scaling = identity_matrix();
	scaling[0][0] = x;
	scaling[1][1] = y;
	scaling[2][2] = z;
	scaling[3][3] = w;
	return (scaling);
}

// int main()
// {
// 	double	**tr;
// 	t_tuple	*point;
// 	t_tuple	*new_point;

// 	tr = scaling(-1, 1, 1, 1);
// 	tr = inverse(tr);
// 	point->x = 2;
// 	point->y = 3;
// 	point->z = 4;
// 	point->w = 1;
// 	new_point = mult_mat_point(tr, point);
// 	printf("x = %2.f\n", new_point->x);
// 	printf("y = %2.f\n", new_point->y);
// 	printf("z = %2.f\n", new_point->z);
// 	printf("w = %2.f\n", new_point->w);
// }
