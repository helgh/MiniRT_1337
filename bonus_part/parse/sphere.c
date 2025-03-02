/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:28:51 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/03/02 18:13:13 by hael-ghd         ###   ########.fr       */
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

void	sphere_compenent(t_scene *scene)
{
	t_sphere	*sphere;
	t_tmp_heap	*tmp;

	tmp = scene->tmp_heap;
	sphere = scene->sphere;
	while (sphere)
	{
		if (sphere->flag_text)
			sphere->text = get_image_texture(scene, sphere->path);
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
	}
}

void	parse_sphere(t_scene *scene, char **line)
{
	t_sphere	*sphere;
	int			len;
	char		*path;

	len = lengh(line);
	path = NULL;
	if (len != 4 && len != 5 && len != 6)
		print_scene_err(scene, ERR_SP_1);
	if (len == 6 || len == 5)
		path = texture_parse(scene, &line[4], ERR_SP_1);
	if (valid_float(line[2], false))
		print_scene_err(scene, ERR_SP_1);
	sphere = ft_malloc(scene, sizeof(t_sphere), false);
	sphere->flag_text = false;
	sphere->pos = _get_position(scene, line[1], ERR_SP_1);
	check_color(scene, line[3], ERR_SP_1, ERR_SP_2);
	sphere->color = _get_color(scene, line[3]);
	sphere->radius = ft_atof(line[2]) / 2.0;
	if (path)
		sphere->flag_text = true;
	sphere->path = path;
	sphere->next = NULL;
	if (!scene->sphere)
		scene->sphere = sphere;
	else
		add_sp_list(scene, sphere);
}
