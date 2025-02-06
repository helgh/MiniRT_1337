/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:54:56 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/02/06 18:31:11 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Minirt.h"

t_cylinder	*get_cylinder(t_cylinder *cy, int id)
{
	while (cy)
	{
		if (cy->id == id)
			break;
		cy = cy->next;
	}
	return (cy);
}

t_plane	*get_plane(t_plane *pl, int id)
{
	while (pl)
	{
		if (pl->id == id)
			break;
		pl = pl->next;
	}
	return (pl);
}

t_sphere	*get_sphere(t_sphere *sp, int id)
{
	while (sp)
	{
		if (sp->id == id)
			break;
		sp = sp->next;
	}
	return (sp);
}
