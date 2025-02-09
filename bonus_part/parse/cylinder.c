/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:30:22 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/02/09 20:17:28 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Minirt.h"

static void	add_cy_list(t_scene *scene, t_cylinder *cy)
{
	t_cylinder	*cylinder;

	cylinder = scene->cylinder;
	while (cylinder->next)
		cylinder = cylinder->next;
	cylinder->next = cy;
}

double	_check_get_number(t_scene *scene, char *line, char *msg)
{
	double	number;
	int		i;

	i = -1;
	while (line[++i])
	{
		if (!ft_isdigit(line[i]))
		{
			if (line[i] == 10)
				break ;
			print_scene_err(scene, msg);
		}
	}
	number = ft_atof(line);
	return (number);
}

void	cylinder_compenent(t_scene *scene)
{
	t_cylinder	*cy;
	t_tmp_heap	*tmp;
	int			i;

	cy = scene->cylinder;
	tmp = scene->tmp_heap;
	i = 0;
	while (cy)
	{
		cy->id = i;
		tmp->rot = _get_trans_rot(scene, *cy->normal_v);
		tmp->scal = scaling(scene, cy->radius, 1, cy->radius);
		tmp->trans = translation(scene, cy->pos->x, cy->pos->y, cy->pos->z);
		tmp->all = mult_matrix(scene, tmp->scal, tmp->rot);
		tmp->scal = free_matrix(tmp->scal);
		tmp->rot = free_matrix(tmp->rot);
		tmp->scal = mult_matrix(scene, tmp->trans, tmp->all);
		tmp->trans = free_matrix(tmp->trans);
		tmp->all = free_matrix(tmp->all);
		cy->inv_trans = inverse(scene, tmp->scal);
		tmp->scal = free_matrix(tmp->scal);
		cy->transpose_inv_matrix = transpose(scene, cy->inv_trans);
		cy = cy->next;
		i++;
	}
}

void	parse_cylinder(t_scene *scene, char **line)
{
	t_cylinder	*cylinder;
	int			len;

	len = lengh(line);
	if ((len != 6 && len != 7) || (len == 7 && strcmp(line[len - 1], "\n")))
		print_scene_err(scene, ERR_CY_1);
	if (valid_float(line[3], false) || valid_float(line[4], false))
		print_scene_err(scene, ERR_CY_1);
	cylinder = ft_malloc(scene, sizeof(t_cylinder), false);
	cylinder->pos = _get_position(scene, line[1], ERR_CY_1);
	cylinder->normal_v = _get_normal_v(scene, line[2], ERR_CY_1);
	if (magnitude(*cylinder->normal_v) != 1.0)
		*cylinder->normal_v = normal(*cylinder->normal_v);
	check_color(scene, line[5], ERR_CY_1, ERR_CY_3);
	cylinder->color = _get_color(scene, line[5]);
	cylinder->radius = _check_get_number(scene, line[3], ERR_CY_1) / 2.0;
	cylinder->max_min = _check_get_number(scene, line[4], ERR_CY_1) / 2.0;
	cylinder->next = NULL;
	if (!scene->cylinder)
		scene->cylinder = cylinder;
	else
		add_cy_list(scene, cylinder);
}
