/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:15:47 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/10/28 18:03:14 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

double	**translation(double x, double y, double z)
{
	double	**tr;
	int		i;
	int		s;
	int		a;
	int		arr[3];

	i = -1;
	a = 0;
	tr = malloc(sizeof(double *) * 5);
	arr[0] = x;
	arr[1] = y;
	arr[2] = z;
	while (++i < 4)
	{
		s = -1;
		tr[i] = malloc(sizeof(double) * 4);
		while (++s < 4)
		{
			if (i == s)
				tr[i][s] = 1;
			else if (s == 3)
				tr[i][s] = arr[a++];
			else
				tr[i][s] = 0;
		}
	}
	tr[i] = NULL;
	return (tr);
}
