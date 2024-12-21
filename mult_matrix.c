/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mult_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 19:42:47 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/12/20 16:57:39 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

static double	find_new_value(double **a, double **b, int i, int s)
{
	double	value;
	int		r;
	int		size;

	r = -1;
	value = 0;
	size = count_size(a);
	while (++r < size)
		value += (a[i][r] * b[r][s]);
	return (value);
}

double	**mult_matrix(double **a, double **b)
{
	int		i;
	int		s;
	int		size;
	double	**new_mat;

	i = -1;
	size = count_size(a);
	new_mat = malloc(sizeof(double *) * (size + 1));
	while (++i < size)
		new_mat[i] = malloc(sizeof(double) * size);
	i = -1;
	while (++i < size)
	{
		s = -1;
		while (++s < size)
			new_mat[i][s] = find_new_value(a, b, i, s);
	}
	new_mat[i] = NULL;
	return (new_mat);
}

// int main() {
//     // Define a 4x4 matrix
//     double **matrix = malloc(sizeof(double *) * 5); // 4 rows + 1 for NULL termination
//     matrix[0] = malloc(sizeof(double) * 4); // Row 0
//     matrix[1] = malloc(sizeof(double) * 4); // Row 1
//     matrix[2] = malloc(sizeof(double) * 4); // Row 2
//     matrix[3] = malloc(sizeof(double) * 4); // Row 3
//     matrix[4] = NULL; // NULL terminate the array

//     // Fill the matrix
//     matrix[0][0] = 8; matrix[0][1] = -5; matrix[0][2] = 9;  matrix[0][3] = 2;
//     matrix[1][0] = 7; matrix[1][1] = 5;  matrix[1][2] = 6;  matrix[1][3] = 1;
//     matrix[2][0] = -6;  matrix[2][1] = 0;  matrix[2][2] = 9; matrix[2][3] = 6;
//     matrix[3][0] = -3; matrix[3][1] = 0;  matrix[3][2] = -9;  matrix[3][3] = -4;
//     double **matri = malloc(sizeof(double *) * 5); // 4 rows + 1 for NULL termination
//     matri[0] = malloc(sizeof(double) * 4); // Row 0
//     matri[1] = malloc(sizeof(double) * 4); // Row 1
//     matri[2] = malloc(sizeof(double) * 4); // Row 2
//     matri[3] = malloc(sizeof(double) * 4); // Row 3
//     matri[4] = NULL; // NULL terminate the array

//     // Fill the matrix
//     matri[0][0] = 9; matri[0][1] = 3; matri[0][2] = 0;  matri[0][3] = 9;
//     matri[1][0] = -5; matri[1][1] = -2;  matri[1][2] = -6;  matri[1][3] = -3;
//     matri[2][0] = -4;  matri[2][1] = 9;  matri[2][2] = 6; matri[2][3] = 4;
//     matri[3][0] = 7; matri[3][1] = 6;  matri[3][2] = 6;  matri[3][3] = 2;

//     // Calculate the determinant
//     // double determinant = det(matrix);
// 	double **c = mult_matrix(matrix, matri);
// 	int row = -1;
// 	while (c[++row])
// 	{
// 		int i = -1;
// 		while (++i < 4)
// 			printf("%f -- ", c[row][i]);
// 		printf("\n");
// 	}
// 	printf("\n-------------------------------------\n");
// 	c = mult_matrix(c, inverse(matrix));
// 	row = -1;
// 	while (c[++row])
// 	{
// 		int i = -1;
// 		while (++i < 4)
// 			printf("%f -- ", c[row][i]);
// 		printf("\n");
// 	}
//     // Print the determinant
//     // printf("Determinant: %f\n", determinant);

// 	// inverse(matrix);
//     // Free the allocated memory for the matrix
//     for (int i = 0; i < 4; i++)
//         free(matrix[i]);
//     free(matrix);
//     for (int i = 0; i < 4; i++)
//         free(matri[i]);
//     free(matri);

//     return 0;
// }

// int main()
// {

// 	double **a = malloc(sizeof(double *) * 3 + 1);
// 	double **b = malloc(sizeof(double *) * 3 + 1);
// 	a[0] = malloc(sizeof(double) * 3);
// 	a[1] = malloc(sizeof(double) * 3);
// 	a[2] = malloc(sizeof(double) * 3);
// 	b[0] = malloc(sizeof(double) * 3);
// 	b[1] = malloc(sizeof(double) * 3);
// 	b[2] = malloc(sizeof(double) * 3);
//     a[0][0] = 1; a[0][1] = 2; a[0][2] = 6;
//     a[1][0] = 2; a[1][1] = 4; a[1][2] = 3;
//     a[2][0] = 4; a[2][1] = 2; a[2][2] = 1;
//     a[3] = NULL;

//     b[0][0] = 2; b[0][1] = 4; b[0][2] = 4;
//     b[1][0] = 4; b[1][1] = 8; b[1][2] = 3;
//     b[2][0] = 2; b[2][1] = 9; b[2][2] = 0;
//     b[3] = NULL;
	// int	i, j = 0;
	// while (i < 2)
	// {
	// 	j = 0;
	// 	while (j < 2)
	// 	{
	// 		if (j == 1)
	// 			printf("||  ");
	// 		printf("%0.f  ", a[i][j]);
	// 		printf("%0.f  ", b[i][j]);
	// 		j++;
	// 	}
	// 	printf("\n");
	// 	i++;
	// }
	// i=j=0;
	// 	printf("\t");
	// while (i < 2)
	// {
	// 	j = 0;
	// 	while (j < 2)
	// 	{
	// 		printf("%0.f  ", b[i][j]);
	// 		j++;
	// 	}
	// 	printf("\n");
	// 	i++;
	// }
	 //frint_matrice(a, b);
	// mult_matrix(a, b, 3, 3);
	//  frint_matrice(a, b);
// }