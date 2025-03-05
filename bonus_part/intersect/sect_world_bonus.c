/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sect_world_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:56:27 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/03/05 18:10:50 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Minirt_bonus.h"

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
	t_cone		*cone;
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
	t_intersect	*sec;
	t_intersect	*secs[4];
	int			i;

	i = -1;
	scene->sect = NULL;
	sec = sec_spheres(scene, ray);
	if (sec)
		secs[++i] = sec;
	sec = sec_planes(scene, ray);
	if (sec)
		secs[++i] = sec;
	sec = sec_cylinders(scene, ray);
	if (sec)
		secs[++i] = sec;
	sec = sec_cone(scene, ray);
	if (sec)
		secs[++i] = sec;
	if (i >= 0)
		scene->sect = hit(secs, i);
}
