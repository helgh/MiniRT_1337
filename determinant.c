/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   determinant.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 18:25:09 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/10/30 22:10:26 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

void	free_sub_matrix(double **sub)
{
	int		i;
	double	*tmp;

	i = 0;
	while (sub[i])
	{
		tmp = sub[i];
		i++;
		free (tmp);
	}
	free (sub);
}

int	count_size(double **a)
{
	int	i;

	i = -1;
	while (a[++i])
		;
	return (i);
}

double	**submatrix(double **a, int row, int col)
{
	double	**sub;
	int		size;
	int		i;
	int		s;
	int		l;
	int		b;

	i = -1;
	b = -1;
	size = count_size(a);
	sub = malloc(sizeof(double *) * size);
	if (!sub)
		return (NULL);
	while (++i < size)
	{
		if (i == row)
			i++;
		if (i < size)
			sub[++b] = malloc(sizeof(double) * (size - 1));
		else
			break ;
		s = -1;
		l = -1;
		while (++l < size)
			if (l != col)
				sub[b][++s] = a[i][l];
	}
	sub[++b] = NULL;
	return (sub);
}

double	minor(double **a, int row, int col)
{
	double	res;
	double	**sub;

	sub = NULL;
	if (count_size(a) == 3)
	{
		sub = submatrix(a, row, col);
		res = (sub[0][0] * sub[1][1]) - (sub[0][1] * sub[1][0]);
	}
	else
		res = (a[0][0] * a[1][1]) - (a[0][1] * a[1][0]);
	if (sub)
		free_sub_matrix(sub);
	return (res);
}

double	det_minor(double **a)
{
	double	det_minor;
	int		i;
	int		size;

	i = -1;
	det_minor = 0;
	size = count_size(a);
	while (++i < size)
	{
		a[0][i] *= pow(-1, i);
		det_minor += a[0][i] * minor(a, 0, i);
	}
	return (det_minor);
}

double	cofactor(double **a, int row, int col)
{
	double	factor;
	double	**sub;
	int		i;
	int		size;

	sub = NULL;
	factor = 0;
	sub = submatrix(a, row, col);
	size = count_size(sub);
	factor = pow(-1, row + col) * det_minor(sub);
	if (sub)
		free_sub_matrix(sub);
	return (factor);
}

double	det(double **a)
{
	double	det;
	int		i;
	int		size;

	det = 0;
	size = count_size(a);
	if (size == 2)
		return (det = minor(a, 0, 0));
	else
	{
		i = -1;
		while (++i < size)
			det += (a[0][i] * cofactor(a, 0, i));
	}
	return (det);
}

double	**trans_mat(double **a, double det)
{
	double	**tr;
	int		i;
	int		s;
	int		size;

	size = count_size(a);
	i = -1;
	tr = malloc(sizeof(double *) * (size + 1));
	while (++i < size)
		tr[i] = malloc(sizeof(double) * size);
	i = -1;
	while (++i < size)
	{
		s = -1;
		while (++s < size)
			tr[s][i] = a[i][s] / det;
	}
	tr[size] = NULL;
	return (tr);
}

double	**inverse(double **a)
{
	double	**a2;
	double	c;
	int		size;
	int		row;
	int		col;
	double	d;

	row = -1;
	size = count_size(a);
	a2 = malloc(sizeof(double *) * (size + 1));
	d = det(a);
	if (d == 0)
		return (NULL);
	while (++row < size)
	{
		col = -1;
		a2[row] = malloc(sizeof(double) * size);
		while (++col < size)
			a2[row][col] = cofactor(a, row, col);
	}
	a2[row] = NULL;
	a2 = trans_mat(a2, d);
	return (a2);
}

double	find_new_value(double **a, double **b, int i, int s)
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

//     // Print the determinant
//     // printf("Determinant: %f\n", determinant);

// 	inverse(matrix);
//     // Free the allocated memory for the matrix
//     for (int i = 0; i < 4; i++)
//         free(matrix[i]);
//     free(matrix);

//     return 0;
// }
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

//     // Fill the matri
//     matri[0][0] = 9; matri[0][1] = 3; matri[0][2] = 0;  matri[0][3] = 9;
//     matri[1][0] = -5; matri[1][1] = -2;  matri[1][2] = -6;  matri[1][3] = -3;
//     matri[2][0] = -4;  matri[2][1] = 9;  matri[2][2] = 6; matri[2][3] = 4;
//     matri[3][0] = 7; matri[3][1] = 6;  matri[3][2] = 6;  matri[3][3] = 2;

//     // Calculate the determinant
//     // double determinant = det(matri);
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
// 	double **e = inverse(matri);
// 	row = -1;
// 	while (e[++row])
// 	{
// 		int i = -1;
// 		while (++i < 4)
// 			printf("%f -- ", e[row][i]);
// 		printf("\n");
// 	}
// 	printf("\n-------------------------------------\n");

// 	double **d = mult_matrix(c, e);
// 	row = -1;
// 	while (d[++row])
// 	{
// 		int i = -1;
// 		while (++i < 4)
// 			printf("%f -- ", d[row][i]);
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
int main()
{

	// double **matrix = malloc(sizeof(double *) * 5); // 4 rows + 1 for NULL termination
    // matrix[0] = malloc(sizeof(double) * 4); // Row 0
    // matrix[1] = malloc(sizeof(double) * 4); // Row 1
    // matrix[2] = malloc(sizeof(double) * 4); // Row 2
    // matrix[3] = malloc(sizeof(double) * 4); // Row 3
    // matrix[4] = NULL; // NULL terminate the array

    // // Fill the matrix
    // matrix[0][0] = 1; matrix[0][1] = 0; matrix[0][2] = 0;  matrix[0][3] = 5;
    // matrix[1][0] = 0; matrix[1][1] = 1;  matrix[1][2] = 0;  matrix[1][3] = -3;
    // matrix[2][0] = 0;  matrix[2][1] = 0;  matrix[2][2] = 1; matrix[2][3] = 2;
    // matrix[3][0] = 0; matrix[3][1] = 0;  matrix[3][2] = 0;  matrix[3][3] = 1;
	t_axis	p;
	// t_axis	p1;
	// t_axis	p2;

	p.x = 1;
	p.y = 0;
	p.z = 1;
	// p1.x = 0;
	// p1.y = 0;
	// p1.z = 0;
	// p2.x = 0;
	// p2.y = 1;
	// p2.z = 0;
	// double	**rad = rotate_x(1.570796);
	double	**rad1 = scaling(5, 5, 5);
	// double	**rad2 = translation(10, 5, 7);
	// printf("--- %f ---\n",rad);
	// double	**matrix = rotate_z(rad);
	// printf("%p\n", mat);
	// double	**mat = inverse(matrix);
	// int row = -1;
	// while (rad[++row])
	// {
	// 	int i = -1;
	// 	while (++i < 4)
	// 		printf("%f -- ", rad[row][i]);
	// 	printf("\n");
	// }
	// t_axis	*a = malloc(sizeof(t_axis));
	// a->x = 1;
	// a->y = 0;
	// a->z = 1;
	// a->w = 1;
	t_axis *point = mult_mat_point(rotate_x(1.570796), &p);
	point = mult_mat_point(rad1, point);
	printf("-- %f -- %f -- %f  \n", point->x, point->y, point->z);
}
