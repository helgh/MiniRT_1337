/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hits_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:07:08 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/03/05 18:10:17 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Minirt_bonus.h"

double	choise_point(t_intersect *sec)
{
	t_intersect	tmp;

	tmp = *sec;
	if (sec->point_sec_1 < 0)
		return (sec->t = sec->point_sec_2, sec->point_sec_2);
	else if (sec->point_sec_2 < 0)
		return (sec->t = sec->point_sec_1, sec->point_sec_1);
	else if (sec->point_sec_1 < sec->point_sec_2)
		return (sec->t = sec->point_sec_1, sec->point_sec_1);
	return (sec->t = sec->point_sec_2, sec->point_sec_2);
}

t_intersect	*hit(t_intersect **secs, int index)
{
	int			i;
	t_intersect	*send;

	i = -1;
	send = secs[0];
	while (++i <= index)
	{
		if (send->t > secs[i]->t)
			send = secs[i];
	}
	return (send);
}
