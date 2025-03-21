/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:29:41 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/03/21 01:10:10 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Minirt_bonus.h"

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

static void	plane_compenent(t_scene *scene, t_plane *pl)
{
	t_tmp_heap	*tmp;

	tmp = scene->tmp_heap;
	if (pl->path)
		pl->text = get_image_texture(scene, pl->path);
	if (magnitude(pl->normal_v) != 1.0)
	{
		write(2, NORMAL_PL, ft_strlen(NORMAL_PL));
		pl->normal_v = normal(pl->normal_v);
	}
	tmp->scal = _get_trans_rot(scene, pl->normal_v);
	tmp->trans = translation(scene, pl->pos.x, pl->pos.y, pl->pos.z);
	tmp->all = mult_matrix(scene, tmp->trans, tmp->scal);
	tmp->scal = free_matrix(tmp->scal);
	tmp->trans = free_matrix(tmp->trans);
	pl->inv_trans = inverse(scene, tmp->all);
	tmp->all = free_matrix(tmp->all);
	pl->transpose_inv_matrix = transpose(scene, pl->inv_trans);
}

void	parse_plane(t_scene *scene, char **line)
{
	t_plane	*plane;
	int		len;

	len = lengh(line);
	if (len < 4 || len > 8)
		print_scene_err(scene, ERR_PL_1);
	plane = ft_malloc(scene, sizeof(t_plane));
	ft_memset(plane, 0, sizeof(t_plane));
	plane->checker = _get_checker(scene, &line[4], ERR_PL_1, ERR_PL_3);
	if (plane->checker.exist == true)
		plane->path = texture_parse(scene, &line[7], ERR_PL_1);
	else
		plane->path = texture_parse(scene, &line[4], ERR_PL_1);
	plane->pos = _get_position(scene, line[1], ERR_PL_1);
	plane->normal_v = _get_normal_v(scene, line[2], ERR_PL_1, ERR_PL_2);
	check_color(scene, line[3], ERR_PL_1, ERR_PL_3);
	plane->color = _get_color(scene, line[3]);
	plane_compenent(scene, plane);
	if (!scene->plane)
		scene->plane = plane;
	else
		add_pl_list(scene, plane);
}
