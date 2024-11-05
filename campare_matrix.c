/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   campare_mateix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:20:57 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/11/02 17:25:19 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

bool	campare_mat(double **arr1, double **arr2)
{
	int	i;
	int	s;
	int	size;

	i = -1;
	size = count_size(arr1);
	if (size != count_size(arr2))
		return (true);
	while (++i < size)
	{
		s = -1;
		while (++s < size)
			if (arr1[i][s] != arr2[i][s])
				return (true);
	}
	return (false);
}
