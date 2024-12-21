# include <unistd.h>
# include <mlx.h>
# include <time.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>


int	count_size(double **a)
{
	int	i;

	i = -1;
	while (a[++i])
		;
	return (i);
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


double	determinant(double **a)
{
	double	det;

	det = (a[0][0] * a[1][1]) - (a[0][1] * a[1][0]);
	return (det);
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
	double	**sub;
	double	det;

	sub = submatrix(a, row, col);
	if (!sub)
		exit(1);
	det = determinant(sub);
	free_sub_matrix(sub);
	return (det);
}

double	cofactor(double **a, int row, int col)
{
	int		i;
	double	det;
	double	value;
	double	**sub;

	i = -1;
	det = 0;
	sub = a;
	if (count_size(a) > 3)
		sub = submatrix(a, row, col);
	while (++i < 3)
	{
		value = minor(sub, 0, i);
		value *= (sub[0][i] * pow(-1, i));
		det += value;
	}
	det *= pow (-1, row + col);
	return (det);
}

double	det(double **a)
{
	double	**submat;
	double	det;
	int		size;
	int		i;

	size = count_size(a);
	det = 0;
	if (size == 2)
		return (determinant(a));
	else if (size == 3)
		det = cofactor(a, 0, 0);
	else
	{
		i = -1;
		while (++i < size)
			det += (a[0][i] * cofactor(a, 0, i));
	}
	return (det);
}

void	transpose_matrix(double **a2)
{
	double	tmp[4][4];
	int		i;
	int		s;

	i = -1;
	while (++i < 4)
	{
		s = -1;
		while (++s < 4)
			tmp[i][s] = a2[i][s];
	}
	i = -1;
	while (++i < 4)
	{
		s = -1;
		while (++s < 4)
			a2[s][i] = tmp[i][s];
	}
}

double	**inverse(double **a)
{
	int		row;
	int		col;
	double	**a2;
	double	determinant;

	determinant = det(a);
	if (determinant == 0)
		return (NULL);
	a2 = malloc(sizeof(double *) * count_size(a) + 1);
	if (!a2)
		return (NULL);
	row = -1;
	while (++row < 4)
	{
		col = -1;
		a2[row] = malloc(sizeof(double) * 4);
		while (++col < 4)
			a2[row][col] = cofactor(a, row, col) / determinant;
	}
	a2[row] = NULL;
	transpose_matrix(a2);
	return (a2);
}

int main() {
    // Define a 4x4 matrix
    double **matrix = malloc(sizeof(double *) * 5); // 4 rows + 1 for NULL termination
    matrix[0] = malloc(sizeof(double) * 3); // Row 0
    matrix[1] = malloc(sizeof(double) * 3); // Row 1
    matrix[2] = malloc(sizeof(double) * 3); // Row 2
    matrix[3] = malloc(sizeof(double) * 4); // Row 3
    matrix[4] = NULL; // NULL terminate the array

    // Fill the matrix
    matrix[0][0] = 3; matrix[0][1] = -9; matrix[0][2] = 7; matrix[0][3] = 3;
    matrix[1][0] = 3; matrix[1][1] = -8;  matrix[1][2] = 2; matrix[1][3] = -9;
    matrix[2][0] = -4;  matrix[2][1] = 4;  matrix[2][2] = 4; matrix[2][3] = 1;
    matrix[3][0] = -6; matrix[3][1] = 5;  matrix[3][2] = -1; matrix[3][3] = 1;
    double **mat = malloc(sizeof(double *) * 5); // 4 rows + 1 for NULL termination
    mat[0] = malloc(sizeof(double) * 3); // Row 0
    mat[1] = malloc(sizeof(double) * 3); // Row 1
    mat[2] = malloc(sizeof(double) * 3); // Row 2
    mat[3] = malloc(sizeof(double) * 4); // Row 3
    mat[4] = NULL; // NULL terminate the array

    // Fill the matrix
    mat[0][0] = 8; mat[0][1] = 2; mat[0][2] = 2; mat[0][3] = 2;
    mat[1][0] = 3; mat[1][1] = -1;  mat[1][2] = 7; mat[1][3] = 0;
    mat[2][0] = 7;  mat[2][1] = 0;  mat[2][2] = 5; mat[2][3] = 4;
    mat[3][0] = 6; mat[3][1] = -2;  mat[3][2] = 0; mat[3][3] = 5;

	// printf("cofactor (0, 0) = %0.f\n", inv[][]);
	// printf("minor (0, 0) = %0.f\n", minor(matrix, 0, 0));
	// printf("%0.f -- %0.f -- %0.f -- %0.f\n", inv[][], inv[][], inv[][], inv[][]);
	// printf("%0.f -- %0.f -- %0.f -- %0.f\n", inv[][], inv[][], inv[][], inv[][]);
	// printf("%0.f -- %0.f -- %0.f -- %0.f\n", inv[][], inv[][], inv[][], inv[][]);
	// printf("%0.f -- %0.f -- %0.f -- %0.f\n", inv[][], inv[][], inv[][], inv[][]);
	// printf("cofactor (0, 2) = %0.f\n", inv[][]);
	// printf("cofactor (0, 3) = %0.f\n", inv[][]);
	// printf("determinant (matrix) = %0.f\n", det(matrix));
	// printf("minor (1, 0) = %0.f\n", minor(matrix, 1, 0));
	double **mult;
	double **inv;

	mult = mult_matrix(matrix, mat);
	inv = mult_matrix(mult, inverse(mat));
	printf("%0.f -- %0.f -- %0.f -- %0.f\n", inv[0][0], inv[0][1], inv[0][2], inv[0][3]);
	printf("%0.f -- %0.f -- %0.f -- %0.f\n", inv[1][0], inv[1][1], inv[1][2], inv[1][3]);
	printf("%0.f -- %0.f -- %0.f -- %0.f\n", inv[2][0], inv[2][1], inv[2][2], inv[2][3]);
	printf("%0.f -- %0.f -- %0.f -- %0.f\n", inv[3][0], inv[3][1], inv[3][2], inv[3][3]);

    for (int i = 0; i < 4; i++)
        free(matrix[i]);
    free(matrix);
    for (int i = 0; i < 4; i++)
        free(mat[i]);
    free(mat);

    return 0;
}