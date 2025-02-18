/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:30:22 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/02/18 20:51:32 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Minirt.h"

static void	add_cy_list(t_scene *scene, t_cylinder *cy)
{
	static t_cylinder	*cylinder;

	if (!cylinder)
	{
		cylinder = scene->cylinder;
		cylinder->next = cy;
		cylinder = cylinder->next;
	}
	else
	{
		cylinder->next = cy;
		cylinder = cylinder->next;
	}
}

void	cylinder_compenent(t_scene *scene)
{
	t_cylinder	*cy;
	t_tmp_heap	*tmp;

	cy = scene->cylinder;
	tmp = scene->tmp_heap;
	while (cy)
	{
		tmp->rot = _get_trans_rot(scene, *cy->normal_v);
		tmp->scal = scaling(scene, cy->radius, 1, cy->radius);
		tmp->trans = translation(scene, cy->pos->x, cy->pos->y, cy->pos->z);
		tmp->all = mult_matrix(scene, tmp->trans, tmp->rot);
		tmp->trans = free_matrix(tmp->trans);
		tmp->rot = free_matrix(tmp->rot);
		tmp->trans = mult_matrix(scene, tmp->all, tmp->scal);
		tmp->scal = free_matrix(tmp->scal);
		tmp->all = free_matrix(tmp->all);
		cy->inv_trans = inverse(scene, tmp->trans);
		tmp->trans = free_matrix(tmp->trans);
		cy->transpose_inv_matrix = transpose(scene, cy->inv_trans);
		cy = cy->next;
	}
}

void	parse_cylinder(t_scene *scene, char **line)
{
	t_cylinder	*cylinder;
	int			len;

	len = lengh(line);
	if ((len != 6 && len != 7) || (len == 7 && ft_strcmp(line[len - 1], "\n")))
		print_scene_err(scene, ERR_CY_1);
	if (valid_float(line[3], false) || valid_float(line[4], false))
		print_scene_err(scene, ERR_CY_1);
	cylinder = ft_malloc(scene, sizeof(t_cylinder));
	cylinder->pos = _get_position(scene, line[1], ERR_CY_1);
	cylinder->normal_v = _get_normal_v(scene, line[2], ERR_CY_1);
	if (magnitude(*cylinder->normal_v) != 1.0)
	{
		write(2, NORMAL_CY, ft_strlen(NORMAL_CY));
		*cylinder->normal_v = normal(*cylinder->normal_v);
	}
	check_color(scene, line[5], ERR_CY_1, ERR_CY_3);
	cylinder->color = _get_color(scene, line[5]);
	cylinder->radius = ft_atof(line[3]) / 2.0;
	cylinder->max_min = ft_atof(line[4]) / 2.0;
	cylinder->next = NULL;
	if (!scene->cylinder)
		scene->cylinder = cylinder;
	else
		add_cy_list(scene, cylinder);
}
