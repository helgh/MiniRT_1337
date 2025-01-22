/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:38:52 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/01/22 16:38:59 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

double	ft_atof(char *str)
{
	double	int_part;
	double	div_part;
	double	sign;
	int		i;

	int_part = 0.0;
	div_part = 0.0;
	sign = 1.0;
	while (ft_isdigit(*str))
		int_part = int_part * 10 + (*str++ - '0');
	i = -1;
	if (*str == '.' && *str++)
	{
		while (ft_isdigit(*str))
			div_part += (pow(10, i--) * (*str++ - '0'));
	}
	return (sign * (int_part + div_part));
}
