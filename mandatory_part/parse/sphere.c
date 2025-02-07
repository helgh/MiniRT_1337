/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:28:51 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/02/07 17:54:43 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Minirt.h"

static void	add_sp_list(t_scene *scene, t_sphere *sp)
{
	t_sphere	*sphere;

	sphere = scene->sphere;
	while (sphere->next)
		sphere = sphere->next;
	sphere->next = sp;
}

void	sphere_compenent(t_scene *scene)
{
	t_sphere	*sphere;
	t_tmp_heap	*tmp;
	int			i;

	i = 0;
	tmp = scene->tmp_heap;
	sphere = scene->sphere;
	while (sphere)
	{
		sphere->id = i;
		tmp->trans = translation(scene, sphere->pos->x, \
			sphere->pos->y, sphere->pos->z);
		tmp->scal = scaling(scene, sphere->radius, sphere->radius, \
			sphere->radius);
		tmp->all = mult_matrix(scene, tmp->trans, tmp->scal);
		tmp->trans = free_matrix(tmp->trans);
		tmp->scal = free_matrix(tmp->scal);
		sphere->inv_trans = inverse(scene, tmp->all);
		tmp->all = free_matrix(tmp->all);
		sphere->transpose_inv_matrix = transpose(scene, sphere->inv_trans);
		sphere = sphere->next;
		i++;
	}
}

void	parse_sphere(t_scene *scene, char **line)
{
	t_sphere	*sphere;
	int			len;

	len = lengh(line);
	if (len != 4 && len != 5)
		print_scene_err(scene, ERR_SP_1);
	if (len == 5 && strcmp(line[len - 1], "\n"))
		print_scene_err(scene, ERR_SP_1);
	if (valid_float(line[2], false))
		print_scene_err(scene, ERR_SP_1);
	sphere = ft_malloc(scene, sizeof(t_sphere), false);
	sphere->pos = _get_position(scene, line[1], ERR_SP_1);
	check_color(scene, line[3], ERR_SP_1, ERR_SP_2);
	sphere->color = _get_color(scene, line[3]);
	sphere->radius = ft_atof(line[2]) / 2.0;
	sphere->next = NULL;
	if (!scene->sphere)
		scene->sphere = sphere;
	else
		add_sp_list(scene, sphere);
}
