/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trans_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 11:22:46 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/01/17 16:49:27 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

int main() {
    // Define a 4x4 matrix
    // double **matrix = malloc(sizeof(double *) * 5); // 4 rows + 1 for NULL termination
    // matrix[0] = malloc(sizeof(double) * 3); // Row 0
    // matrix[1] = malloc(sizeof(double) * 3); // Row 1
    // matrix[2] = malloc(sizeof(double) * 3); // Row 2
    // matrix[3] = malloc(sizeof(double) * 4); // Row 3
    // matrix[4] = NULL; // NULL terminate the array

    // // Fill the matrix
    // matrix[0][0] = 3; matrix[0][1] = -9; matrix[0][2] = 7; matrix[0][3] = 3;
    // matrix[1][0] = 3; matrix[1][1] = -8;  matrix[1][2] = 2; matrix[1][3] = -9;
    // matrix[2][0] = -4;  matrix[2][1] = 4;  matrix[2][2] = 4; matrix[2][3] = 1;
    // matrix[3][0] = -6; matrix[3][1] = 5;  matrix[3][2] = -1; matrix[3][3] = 1;
    // double **mat = malloc(sizeof(double *) * 5); // 4 rows + 1 for NULL termination
    // mat[0] = malloc(sizeof(double) * 3); // Row 0
    // mat[1] = malloc(sizeof(double) * 3); // Row 1
    // mat[2] = malloc(sizeof(double) * 3); // Row 2
    // mat[3] = malloc(sizeof(double) * 4); // Row 3
    // mat[4] = NULL; // NULL terminate the array

    // // Fill the matrix
    // mat[0][0] = 8; mat[0][1] = 2; mat[0][2] = 2; mat[0][3] = 2;
    // mat[1][0] = 3; mat[1][1] = -1;  mat[1][2] = 7; mat[1][3] = 0;
    // mat[2][0] = 7;  mat[2][1] = 0;  mat[2][2] = 5; mat[2][3] = 4;
    // mat[3][0] = 6; mat[3][1] = -2;  mat[3][2] = 0; mat[3][3] = 5;

	// printf("cofactor (0, 0) = %f\n", inv[][]);
	// printf("minor (0, 0) = %f\n", minor(matrix, 0, 0));
	// printf("%f -- %f -- %f -- %f\n", inv[][], inv[][], inv[][], inv[][]);
	// printf("%f -- %f -- %f -- %f\n", inv[][], inv[][], inv[][], inv[][]);
	// printf("%f -- %f -- %f -- %f\n", inv[][], inv[][], inv[][], inv[][]);
	// printf("%f -- %f -- %f -- %f\n", inv[][], inv[][], inv[][], inv[][]);
	// printf("cofactor (0, 2) = %f\n", inv[][]);
	// printf("cofactor (0, 3) = %f\n", inv[][]);
	// printf("determinant (matrix) = %f\n", det(matrix));
	// printf("minor (1, 0) = %f\n", minor(matrix, 1, 0));
	double **inv = identity_matrix();
	inv[0][0] = 2;
	inv[1][1] = 2;
	inv[2][2] = 2;
	inv[0][3] = 3;
	inv[1][3] = 3;
	inv[2][3] = 3;
	inv = inverse(inv);
	// double **inv;

	// mult = mult_matrix(matrix, mat);
	// inv = mult_matrix(mult, inverse(mat));
	printf("%f -- %f -- %f -- %f\n", inv[0][0], inv[0][1], inv[0][2], inv[0][3]);
	printf("%f -- %f -- %f -- %f\n", inv[1][0], inv[1][1], inv[1][2], inv[1][3]);
	printf("%f -- %f -- %f -- %f\n", inv[2][0], inv[2][1], inv[2][2], inv[2][3]);
	printf("%f -- %f -- %f -- %f\n", inv[3][0], inv[3][1], inv[3][2], inv[3][3]);

    // for (int i = 0; i < 4; i++)
    //     free(matrix[i]);
    // free(matrix);
    // for (int i = 0; i < 4; i++)
    //     free(mat[i]);
    // free(mat);
    return 0;
}
