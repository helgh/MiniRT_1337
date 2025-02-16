/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   determinant.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 20:59:35 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/02/16 19:01:38 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Minirt.h"

static double	**submatrix(t_scene *scene, double **a, int *arr, int size)
{
	double	**sub;
	int		i;
	int		s;
	int		l;
	int		b;

	i = -1;
	b = -1;
	sub = ft_malloc(scene, sizeof(double *) * size);
	while (++i < size)
	{
		if (i == arr[0])
			i++;
		if (i < size)
			sub[++b] = ft_malloc(scene, sizeof(double) * (size - 1));
		else
			break ;
		s = -1;
		l = -1;
		while (++l < size)
			if (l != arr[1])
				sub[b][++s] = a[i][l];
	}
	sub[++b] = NULL;
	return (sub);
}

static double	minor(t_scene *scene, double **a, int *arr, int size)
{
	double	res;
	double	**sub;

	sub = NULL;
	if (size == 3)
	{
		sub = submatrix(scene, a, arr, 3);
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
	int		arr[2];

	i = -1;
	det_m = 0.0;
	arr[0] = 0;
	while (++i < 3)
	{
		arr[1] = i;
		a[0][i] *= pow(-1, i);
		det_m += a[0][i] * minor(scene, a, arr, 3);
	}
	return (det_m);
}

double	cofactor(t_scene *scene, double **a, int row, int col)
{
	double	factor;
	double	**sub;
	int		arr[2];

	sub = NULL;
	factor = 0.0;
	arr[0] = row;
	arr[1] = col;
	sub = submatrix(scene, a, arr, 4);
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
