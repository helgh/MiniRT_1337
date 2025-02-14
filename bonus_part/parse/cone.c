/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:57:12 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/02/10 17:33:06 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Minirt.h"

static void	add_cone_list(t_scene *scene, t_cone *cone)
{
	t_cone	*co;

	co = scene->cone;
	while (co->next)
		co = co->next;
	co->next = cone;
}

void	cone_compenent(t_scene *scene)
{
	t_cone	*cone;
	t_tmp_heap	*tmp;
	int			i;

	cone = scene->cone;
	tmp = scene->tmp_heap;
	i = 0;
	while (cone)
	{
		cone->id = i;
		tmp->rot = _get_trans_rot(scene, *cone->normal_v);
		tmp->scal = scaling(scene, cone->radius, 1, cone->radius);
		tmp->trans = translation(scene, cone->pos->x, cone->pos->y, cone->pos->z);
		tmp->all = mult_matrix(scene, tmp->trans, tmp->rot);
		tmp->trans = free_matrix(tmp->trans);
		tmp->rot = free_matrix(tmp->rot);
		tmp->trans = mult_matrix(scene, tmp->all, tmp->scal);
		tmp->scal = free_matrix(tmp->scal);
		tmp->all = free_matrix(tmp->all);
		cone->inv_trans = inverse(scene, tmp->trans);
		tmp->trans = free_matrix(tmp->trans);
		cone->transpose_inv_matrix = transpose(scene, cone->inv_trans);
		cone = cone->next;
		i++;
	}
}

void	parse_cone(t_scene *scene, char **line)
{
	t_cone	*cone;
	int			len;

	len = lengh(line);
	if ((len != 6 && len != 7) || (len == 7 && strcmp(line[len - 1], "\n")))
		print_scene_err(scene, ERR_CY_1);
	if (valid_float(line[3], false) || valid_float(line[4], false))
		print_scene_err(scene, ERR_CY_1);
	cone = ft_malloc(scene, sizeof(t_cone), false);
	cone->pos = _get_position(scene, line[1], ERR_CY_1);
	cone->normal_v = _get_normal_v(scene, line[2], ERR_CY_1);
	if (magnitude(*cone->normal_v) != 1.0)
		*cone->normal_v = normal(*cone->normal_v);
	check_color(scene, line[5], ERR_CY_1, ERR_CY_3);
	cone->color = _get_color(scene, line[5]);
	cone->radius = _check_get_number(scene, line[3], ERR_CY_1) / 2.0;
	cone->max_min = _check_get_number(scene, line[4], ERR_CY_1) / 2.0;
	cone->next = NULL;
	if (!scene->cone)
		scene->cone = cone;
	else
		add_cone_list(scene, cone);
}
