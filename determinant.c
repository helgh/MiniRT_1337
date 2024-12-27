/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   determinant.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 18:25:09 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/12/18 18:31:27 by hael-ghd         ###   ########.fr       */
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
		if (sub)
			free_sub_matrix(sub);
	}
	else
		res = (a[0][0] * a[1][1]) - (a[0][1] * a[1][0]);
	return (res);
}

double	det_minor(double **a)
{
	double	det_m;
	int		i;
	int		size;

	i = -1;
	det_m = 0;
	size = count_size(a);
	while (++i < size)
	{
		a[0][i] *= pow(-1, i);
		det_m += a[0][i] * minor(a, 0, i);
	}
	return (det_m);
}

double	cofactor(double **a, int row, int col)
{
	double	factor;
	double	**sub;

	sub = NULL;
	factor = 0;
	sub = submatrix(a, row, col);
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
