/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_world.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:30:41 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/01/20 17:06:39 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

void	add_to_list(t_intersect **head, t_intersect *new)
{
	t_intersect	*tmp;

	if (!new)
		return ;
	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_light	get_light_attr(double intensity, t_tuple position, t_color color)
{
	t_light	light;

	light.brightness = intensity;
	light.cord = position;
	light.color = color;
	return (light);
}

t_sphere	get_sphere(double diameter, t_color color, t_material material, int i)
{
	t_sphere	sp;

	sp.id = i;
	sp.radius = diameter / 2.0;
	sp.ma = material;
	sp.color = color;
	sp.cord = create_tuple(0, 0, 0, 1);
	sp.trans = scaling(0.5, 0.5, 0.5);
	sp.inv_trans = inverse(sp.trans);
	sp.transpose_matrix = transpose(sp.trans);
	sp.transpose_inv_matrix = transpose(sp.inv_trans);
	return (sp);
}

// t_world	*default_world(void)
// {
// 	t_scene		*world;
// 	t_material	def_material;
	
// 	def_material.color = set_color(0.8, 1.0, 0.6);
// 	def_material.diffuse = 0.7;
// 	def_material.specular = 0.2;
// 	world->light[0] = get_light_attr(1, create_tuple(-10, 10, -10, 1), set_color(1, 1, 1));
// 	world->sphere[0] = get_sphere(1, set_color(0.8, 1.0, 0.6), def_material, 0);
// 	return (world);
// }

t_intersect	*intersect_world(t_world *world, t_ray *ray)
{
	t_intersect	*head;
	t_intersect	*tmp;
	t_intersect	*send;
	int			i;
	int			s;

	head = NULL;
	i = -1;
	s = -1;
	while (++i < world->obj_count)
	{
		if (++s < world->sp_count)
			tmp = intersect_sphere(&world->sp[i], ray);
		// else if (world->pl[i].id != -1)
		// 	tmp = intersect_plane(&world->pl[i], ray);
		// else if (world->cy[i].id != -1)
		// 	tmp = intersect_cylinder(&world->cy[i], ray);
		add_to_list(&head, tmp);
	}
	send = hit(head);
	return (send);
}

t_obj_draw	*get_obj(t_intersect *intersect, t_ray *ray)
{
	t_obj_draw	*obj;

	if (!intersect)
		return (NULL);
	
	obj = malloc(sizeof(t_obj_draw));
	obj->t = intersect->t;
	obj->id = intersect->id;
	obj->object = intersect->object;
	obj->position = point_sec(*ray, obj->t);
	obj->eye_v = oposite(ray->direction_v);
	obj->normal_v = normal_at(*(t_sphere *)intersect->object, obj->position);
	obj->inside = true;
	obj->type = intersect->type;
	if (dot_product(obj->normal_v, obj->eye_v) < EPSILON)
		obj->normal_v = oposite(obj->normal_v);
	else
		obj->inside = false;
	return (obj);
}

t_color	shad_hit(t_world *world, t_ray *ray)
{
	t_intersect	*intersect;
	t_obj_draw	*obj;
	t_color		color;
	t_sphere	sp;

	intersect = intersect_world(world, ray);
	color = set_color(0, 0, 0);
	obj = get_obj(intersect, ray);
	if (!obj)
		return (set_color(0, 0, 0));
	if (obj->type == SPHERE)
	{
		sp = *(t_sphere*) obj->object;
		color = lighting(sp.ma, world->light[0], obj->eye_v, obj->position, obj->normal_v);
	}
	return (color);
}
