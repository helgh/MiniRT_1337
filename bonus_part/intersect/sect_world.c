/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sect_world.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:56:27 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/02/10 18:18:49 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Minirt.h"

static t_intersect	*sec_spheres(t_scene *scene, t_ray *ray)
{
	t_intersect	*tmp;
	t_sphere	*sp;
	t_intersect	*send;
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
			send->sp = sp;
		}
		else if (tmp && tmp->t < send->t)
		{
			send = tmp;
			send->sp = sp;
		}
		sp = sp->next;
	}
	return (send);
}

static t_intersect	*sec_planes(t_scene *scene, t_ray *ray)
{
	t_intersect	*tmp;
	t_plane		*pl;
	t_intersect	*send;
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
			send->pl = pl;
		}
		else if (tmp && tmp->t < send->t)
		{
			send = tmp;
			send->pl = pl;
		}
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
			send->cy = cy;
		}
		else if (tmp && tmp->t < send->t)
		{
			send = tmp;
			send->cy = cy;
		}
		cy = cy->next;
	}
	return (send);
}

static t_intersect	*sec_cone(t_scene *scene, t_ray *ray)
{
	t_intersect	*tmp;
	t_cylinder	*cone;
	t_intersect	*send;
	bool		flag;

	flag = true;
	send = NULL;
	cone = scene->cone;
	while (cone)
	{
		tmp = intersect_cone(scene, cone, ray);
		if (tmp && flag == true)
		{
			flag = false;
			send = tmp;
			send->cone = cone;
		}
		else if (tmp && tmp->t < send->t)
		{
			send = tmp;
			send->cone = cone;
		}
		cone = cone->next;
	}
	return (send);
}

void	intersect_world(t_scene *scene, t_ray *ray)
{
	t_intersect	*sec_sp;
	t_intersect	*sec_pl;
	t_intersect	*sec_cy;
	t_intersect	*sec_cones;
	t_intersect	*secs[4];
	int			i;

	i = -1;
	scene->sect = NULL;
	sec_sp = NULL;
	sec_pl = NULL;
	sec_cy = NULL;
	sec_cones = NULL;
	if (scene->sphere)
		sec_sp = sec_spheres(scene, ray);
	if (scene->plane)
		sec_pl = sec_planes(scene, ray);
	if (scene->cylinder)
		sec_cy = sec_cylinders(scene, ray);
	if (scene->cone)
		sec_cy = sec_cone(scene, ray);
	if (sec_sp)
		secs[++i] = sec_sp;
	if (sec_pl)
		secs[++i] = sec_pl;
	if (sec_cy)
		secs[++i] = sec_cy;
	if (sec_cones)
		secs[++i] = sec_cone;
	if (i >= 0)
		scene->sect = hit(secs, i);
}
