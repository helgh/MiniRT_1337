/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sect_world.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:56:27 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/02/06 20:30:29 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Minirt.h"

static t_intersect	*sec_spheres(t_scene *scene, t_ray *ray)
{
	t_intersect	*tmp;
	t_sphere	*sp;
	t_intersect	*send;
	double		t;
	bool		flag;

	flag = true;
	send = NULL;
	sp = scene->sphere;
	while (sp)
	{
		tmp = intersect_sphere(scene, sp, ray);
		if (tmp && flag == true)
		{
			flag = false;
			send = tmp;
		}
		else if (tmp && tmp->t < send->t)
			send = tmp;
		sp = sp->next;
	}
	return (send);
}

static t_intersect	*sec_planes(t_scene *scene, t_ray *ray)
{
	t_intersect	*tmp;
	t_plane		*pl;
	t_intersect	*send;
	double		t;
	bool		flag;

	flag = true;
	send = NULL;
	pl = scene->plane;
	while (pl)
	{
		tmp = intersect_plane(scene, pl, ray);
		if (tmp && flag == true)
		{
			flag = false;
			send = tmp;
		}
		else if (tmp && tmp->t < send->t)
			send = tmp;
		pl = pl->next;
	}
	return (send);
}

static t_intersect	*sec_cylinders(t_scene *scene, t_ray *ray)
{
	t_intersect	*tmp;
	t_cylinder	*cy;
	t_intersect	*send;
	bool		flag;

	flag = true;
	send = NULL;
	cy = scene->cylinder;
	while (cy)
	{
		tmp = intersect_cylinder(scene, cy, ray);
		if (tmp && flag == true)
		{
			flag = false;
			send = tmp;
		}
		else if (tmp && tmp->t < send->t)
			send = tmp;
		cy = cy->next;
	}
	return (send);
}

void	intersect_world(t_scene *scene, t_ray *ray)
{
	t_intersect	*sec_sp;
	t_intersect	*sec_pl;
	t_intersect	*sec_cy;
	t_intersect	*secs[4];
	int			i;

	i = -1;
	scene->sect = NULL;
	sec_sp = NULL;
	sec_pl = NULL;
	sec_cy = NULL;
	if (scene->sphere)
		sec_sp = sec_spheres(scene, ray);
	if (scene->plane)
		sec_pl = sec_planes(scene, ray);
	if (scene->cylinder)
		sec_cy = sec_cylinders(scene, ray);
	if (sec_sp)
		secs[++i] = sec_sp;
	if (sec_pl)
		secs[++i] = sec_pl;
	if (sec_cy)
		secs[++i] = sec_cy;
	if (i >= 0)
		scene->sect = hit(secs, i);
}
