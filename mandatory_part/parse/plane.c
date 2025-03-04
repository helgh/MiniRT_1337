/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:29:41 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/03/04 17:33:58 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Minirt.h"

static void	add_pl_list(t_scene *scene, t_plane *pl)
{
	static t_plane	*plane;

	if (!plane)
	{
		plane = scene->plane;
		plane->next = pl;
		plane = plane->next;
	}
	else
	{
		plane->next = pl;
		plane = plane->next;
	}
}

void	plane_compenent(t_scene *scene)
{
	t_plane		*pl;
	t_tmp_heap	*tmp;

	pl = scene->plane;
	tmp = scene->tmp_heap;
	while (pl)
	{
		tmp->scal = _get_trans_rot(scene, *pl->normal_v);
		tmp->trans = translation(scene, pl->pos->x, pl->pos->y, pl->pos->z);
		tmp->all = mult_matrix(scene, tmp->trans, tmp->scal);
		tmp->scal = free_matrix(tmp->scal);
		tmp->trans = free_matrix(tmp->trans);
		pl->inv_trans = inverse(scene, tmp->all);
		tmp->all = free_matrix(tmp->all);
		pl->transpose_inv_matrix = transpose(scene, pl->inv_trans);
		pl = pl->next;
	}
}

void	parse_plane(t_scene *scene, char **line)
{
	t_plane	*plane;
	int		len;

	len = lengh(line);
	if (len != 4)
		print_scene_err(scene, ERR_PL_1);
	plane = ft_malloc(scene, sizeof(t_plane));
	plane->pos = _get_position(scene, line[1], ERR_PL_1);
	plane->normal_v = _get_normal_v(scene, line[2], ERR_PL_1);
	if (magnitude(*plane->normal_v) != 1.0)
	{
		write(2, NORMAL_PL, ft_strlen(NORMAL_PL));
		*plane->normal_v = normal(*plane->normal_v);
	}
	check_color(scene, line[3], ERR_PL_1, ERR_PL_3);
	plane->color = _get_color(scene, line[3]);
	plane->next = NULL;
	if (!scene->plane)
		scene->plane = plane;
	else
		add_pl_list(scene, plane);
}
