/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sect_world.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:56:27 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/03/20 00:35:17 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Minirt.h"

static t_intersect	sec_spheres(t_scene *scene, t_ray *ray)
{
	t_intersect	tmp;
	t_sphere	*sp;
	t_intersect	send;
	bool		flag;

	flag = true;
	sp = scene->sphere;
	send.exist = false;
	while (sp)
	{
		tmp = intersect_sphere(scene, sp, ray);
		if (tmp.exist == true && flag == true)
		{
			flag = false;
			send = tmp;
		}
		else if (tmp.exist == true && tmp.t < send.t)
			send = tmp;
		sp = sp->next;
	}
	return (send);
}

static t_intersect	sec_planes(t_scene *scene, t_ray *ray)
{
	t_intersect	tmp;
	t_plane		*pl;
	t_intersect	send;
	bool		flag;

	flag = true;
	pl = scene->plane;
	send.exist = false;
	while (pl)
	{
		tmp = intersect_plane(scene, pl, ray);
		if (tmp.exist == true && flag == true)
		{
			flag = false;
			send = tmp;
		}
		else if (tmp.exist == true && tmp.t < send.t)
			send = tmp;
		pl = pl->next;
	}
	return (send);
}

static t_intersect	sec_cylinders(t_scene *scene, t_ray *ray)
{
	t_intersect	tmp;
	t_cylinder	*cy;
	t_intersect	send;
	bool		flag;

	flag = true;
	cy = scene->cylinder;
	send.exist = false;
	while (cy)
	{
		tmp = intersect_cylinder(scene, cy, ray);
		if (tmp.exist == true && flag == true)
		{
			flag = false;
			send = tmp;
		}
		else if (tmp.exist == true && tmp.t < send.t)
			send = tmp;
		cy = cy->next;
	}
	return (send);
}

void	intersect_world(t_scene *scene, t_ray *ray)
{
	t_intersect	sec;
	t_intersect	secs[4];
	int			i;

	i = -1;
	scene->sect.exist = false;
	sec = sec_spheres(scene, ray);
	if (sec.exist)
		secs[++i] = sec;
	sec = sec_planes(scene, ray);
	if (sec.exist)
		secs[++i] = sec;
	sec = sec_cylinders(scene, ray);
	if (sec.exist)
		secs[++i] = sec;
	if (i >= 0)
		scene->sect = hit(secs, i);
}
