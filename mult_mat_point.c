/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mult_mat_point.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:31:17 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/12/20 19:02:47 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

t_tuple	*mult_mat_point(double **mat, t_tuple *point)
{
	t_tuple	*new_point;

	new_point = malloc(sizeof(t_tuple));
	new_point->x = (point->x * mat[0][0]) + (point->y * mat[0][1]) + (point->z * mat[0][2]);
	new_point->x += (point->w * mat[0][3]);
	new_point->y = (point->x * mat[1][0]) + (point->y * mat[1][1]) + (point->z * mat[1][2]);
	new_point->y += (point->w * mat[1][3]);
	new_point->z = (point->x * mat[2][0]) + (point->y * mat[2][1]) + (point->z * mat[2][2]);
	new_point->z += (point->w * mat[2][3]);
	new_point->w = (point->x * mat[3][0]) + (point->y * mat[3][1]) + (point->z * mat[3][2]);
	new_point->w += (point->w * mat[3][3]);
	return (new_point);
}

// int main()
// {

// 	double **matrix = malloc(sizeof(double *) * 5); // 4 rows + 1 for NULL termination
//     matrix[0] = malloc(sizeof(double) * 4); // Row 0
//     matrix[1] = malloc(sizeof(double) * 4); // Row 1
//     matrix[2] = malloc(sizeof(double) * 4); // Row 2
//     matrix[3] = malloc(sizeof(double) * 4); // Row 3
//     matrix[4] = NULL; // NULL terminate the array

//     // Fill the matrix
//     matrix[0][0] = 1; matrix[0][1] = 0; matrix[0][2] = 0;  matrix[0][3] = 5;
//     matrix[1][0] = 0; matrix[1][1] = 1;  matrix[1][2] = 0;  matrix[1][3] = -3;
//     matrix[2][0] = 0;  matrix[2][1] = 0;  matrix[2][2] = 1; matrix[2][3] = 2;
//     matrix[3][0] = 0; matrix[3][1] = 0;  matrix[3][2] = 0;  matrix[3][3] = 1;
// 	t_tuple	*p;
// 	p->x = -3;
// 	p->y = 4;
// 	p->z = 5;
// 	p->w = 1;
// 	t_tuple	*point = mult_mat_point(matrix, p);
// 	int row = -1;
// 	printf("-- %2.f -- %2.f -- %2.f  \n", point->x, point->y, point->z);
// }
