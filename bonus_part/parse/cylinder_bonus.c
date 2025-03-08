/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:30:22 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/03/07 23:39:59 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Minirt_bonus.h"

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

double	_check_get_number(t_scene *scene, char *line, char *msg)
{
	double	number;
	int		i;

	i = -1;
	if (valid_float(line, false))
		print_scene_err(scene, msg);
	number = ft_atof(line);
	return (number);
}

void	cylinder_compenent(t_scene *scene)
{
	t_cylinder	*cy;
	t_tmp_heap	*tmp;

	cy = scene->cylinder;
	tmp = scene->tmp_heap;
	while (cy)
	{
		if (cy->flag_text == true)
			cy->text = get_image_texture(scene, cy->path);
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

static void	parse_cylinder_2(t_scene *scene, t_cylinder *cy, char **line)
{
	cy->checker = _get_checker(scene, &line[6], ERR_CY_1, ERR_CY_2);
	cy->flag_text = false;
	if (cy->checker)
		cy->path = texture_parse(scene, &line[9], ERR_PL_1);
	else
		cy->path = texture_parse(scene, &line[6], ERR_PL_1);
	if (magnitude(*cy->normal_v) != 1.0)
	{
		write(2, NORMAL_CY, ft_strlen(NORMAL_CY));
		*cy->normal_v = normal(*cy->normal_v);
	}
	if (cy->path)
		cy->flag_text = true;
}

void	parse_cylinder(t_scene *scene, char **line)
{
	t_cylinder	*cylinder;
	int			len;

	len = lengh(line);
	if (len < 6 || len > 10)
		print_scene_err(scene, ERR_CY_1);
	if (valid_float(line[3], false) || valid_float(line[4], false))
		print_scene_err(scene, ERR_CY_1);
	cylinder = ft_malloc(scene, sizeof(t_cylinder));
	cylinder->pos = _get_position(scene, line[1], ERR_CY_1);
	cylinder->normal_v = _get_normal_v(scene, line[2], ERR_CY_1);
	check_color(scene, line[5], ERR_CY_1, ERR_CY_3);
	cylinder->color = _get_color(scene, line[5]);
	cylinder->radius = _check_get_number(scene, line[3], ERR_CY_1) / 2.0;
	cylinder->max_min = _check_get_number(scene, line[4], ERR_CY_1) / 2.0;
	parse_cylinder_2(scene, cylinder, line);
	cylinder->next = NULL;
	if (!scene->cylinder)
		scene->cylinder = cylinder;
	else
		add_cy_list(scene, cylinder);
}
