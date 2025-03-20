/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:28:51 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/03/20 01:00:18 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Minirt.h"

static void	add_sp_list(t_scene *scene, t_sphere *sp)
{
	static t_sphere	*sphere;

	if (!sphere)
	{
		sphere = scene->sphere;
		sphere->next = sp;
		sphere = sphere->next;
	}
	else
	{
		sphere->next = sp;
		sphere = sphere->next;
	}
}

void	sphere_compenent(t_scene *scene, t_sphere *sphere)
{
	t_tmp_heap	*tmp;

	tmp = scene->tmp_heap;
	tmp->trans = translation(scene, sphere->pos.x, \
		sphere->pos.y, sphere->pos.z);
	tmp->scal = scaling(scene, sphere->radius, sphere->radius, \
		sphere->radius);
	tmp->all = mult_matrix(scene, tmp->trans, tmp->scal);
	tmp->trans = free_matrix(tmp->trans);
	tmp->scal = free_matrix(tmp->scal);
	sphere->inv_trans = inverse(scene, tmp->all);
	tmp->all = free_matrix(tmp->all);
	sphere->transpose_inv_matrix = transpose(scene, sphere->inv_trans);
}

void	parse_sphere(t_scene *scene, char **line)
{
	t_sphere	*sphere;
	int			len;

	len = lengh(line);
	if (len != 4 || valid_float(line[2], false))
		print_scene_err(scene, ERR_SP_1);
	sphere = ft_malloc(scene, sizeof(t_sphere));
	ft_memset(sphere, 0, sizeof(t_sphere));
	sphere->pos = _get_position(scene, line[1], ERR_SP_1);
	check_color(scene, line[3], ERR_SP_1, ERR_SP_2);
	sphere->color = _get_color(scene, line[3]);
	sphere->radius = ft_atof(line[2]) / 2.0;
	if (sphere->radius < EPSILON)
		print_scene_err(scene, ERR_SP_1);
	sphere_compenent(scene, sphere);
	if (!scene->sphere)
		scene->sphere = sphere;
	else
		add_sp_list(scene, sphere);
}
