/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inverse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 20:04:02 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/02/04 20:21:10 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

static double	**submatrix(t_scene *scene, double **a, int row, int col, int size)
{
	double	**sub;
	int		i;
	int		s;
	int		l;
	int		b;

	i = -1;
	b = -1;
	sub = ft_malloc(scene, sizeof(double *) * size, true);
	while (++i < size)
	{
		if (i == row)
			i++;
		if (i < size)
			sub[++b] = ft_malloc(scene, sizeof(double) * (size - 1), true);
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

static double	minor(t_scene *scene, double **a, int row, int col, int size)
{
	double	res;
	double	**sub;

	sub = NULL;
	if (size == 3)
	{
		sub = submatrix(scene, a, row, col, 3);
		res = (sub[0][0] * sub[1][1]) - (sub[0][1] * sub[1][0]);
	}
	else
		res = (a[0][0] * a[1][1]) - (a[0][1] * a[1][0]);
	return (res);
}

static double	det_minor(t_scene *scene, double **a)
{
	double	det_m;
	int		i;

	i = -1;
	det_m = 0.0;
	while (++i < 3)
	{
		a[0][i] *= pow(-1, i);
		det_m += a[0][i] * minor(scene, a, 0, i, 3);
	}
	return (det_m);
}

double	cofactor(t_scene *scene, double **a, int row, int col)
{
	double	factor;
	double	**sub;

	sub = NULL;
	factor = 0.0;
	sub = submatrix(scene, a, row, col, 4);
	factor = pow(-1, row + col) * det_minor(scene, sub);
	return (factor);
}

double	det(t_scene *scene, double **a)
{
	double	det;
	int		i;

	det = 0;
	i = -1;
	while (++i < 4)
		det += (a[0][i] * cofactor(scene, a, 0, i));
	return (det);
}


double	**inverse(t_scene *scene, double **a)
{
	int		row;
	int		col;
	double	**a2;
	double	**a3;
	double	determinant;

	determinant = det(scene, a);
	if (determinant == 0.0)
		return (NULL);
	a2 = ft_malloc(scene, sizeof(double *) * 5, true);
	if (!a2)
		return (NULL);
	row = -1;
	while (++row < 4)
	{
		col = -1;
		a2[row] = ft_malloc(scene, sizeof(double) * 4, true);
		while (++col < 4)
			a2[row][col] = cofactor(scene, a, row, col) / determinant;
	}
	a2[row] = NULL;
	a3 = transpose(scene, a2);
	return (a3);
}
