/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hits.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:07:08 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/02/21 16:03:47 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Minirt.h"

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

	i = 0;
	send = secs[0];
	while (++i <= index)
	{
		if (send->t > secs[i]->t)
		{
			free(send);
			send = secs[i];
		}
		else
			free(secs[i]);
	}
	return (send);
}
