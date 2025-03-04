/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:08:03 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/03/04 17:13:35 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Minirt.h"

int	count_size(double **a)
{
	int	i;

	i = -1;
	while (a[++i])
		;
	return (i);
}

double	degree_to_rad(double degree)
{
	double	value;

	value = (degree * (double) M_PI) / 180.0;
	return (value);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	lengh(char **str)
{
	int	i;

	i = -1;
	if (!str)
		return (0);
	while (str[++i])
		;
	if (!ft_strcmp(str[i - 1], "\n"))
		i--;
	return (i);
}
