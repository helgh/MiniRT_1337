/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shearing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:08:44 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/12/20 19:48:15 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

double	**shearing(double *arr)
{
	double	**shearing;

	shearing = identity_matrix();
	shearing[0][1] = arr[0];
	shearing[0][2] = arr[1];
	shearing[1][0] = arr[2];
	shearing[1][2] = arr[3];
	shearing[2][0] = arr[4];
	shearing[2][1] = arr[5];
	return (shearing);
}
int main()
{
	double	**tr;
	t_tuple	*point;
	t_tuple	*new_point;
	double	*arr;
	arr = malloc(sizeof(double) * 6);
	arr[0] = 0;
	arr[1] = 1;
	arr[2] = 0;
	arr[3] = 0;
	arr[4] = 0;
	arr[5] = 0;
	tr = shearing(arr);
	// tr = inverse(tr);
	point->x = 2;
	point->y = 3;
	point->z = 4;
	point->w = 1;
	new_point = mult_mat_point(tr, point);
	printf("x = %2.f\n", new_point->x);
	printf("y = %2.f\n", new_point->y);
	printf("z = %2.f\n", new_point->z);
	printf("w = %2.f\n", new_point->w);
}
