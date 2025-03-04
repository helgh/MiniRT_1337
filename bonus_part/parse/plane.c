/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:29:41 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/03/04 21:09:15 by hael-ghd         ###   ########.fr       */
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

static t_checker	*_get_checker(t_scene *scene, char **line, char *msg1, char *msg2)
{
	t_checker	*checker;
	int			len;

	len = lengh(line);
	if (!line[0] || !ft_strcmp(line[0], "\n") || len == 1)
		return (NULL);
	if (len < 3 || ft_strcmp(line[0], "checker"))
		print_scene_err(scene, msg1);
	checker = ft_malloc(scene, sizeof(t_checker), false);
	checker->ratio = _check_get_number(scene, line[1], msg1);
	check_color(scene, line[2], msg1, msg2);
	checker->color = _get_color(scene, line[2]);
	return (checker);
}

void	plane_compenent(t_scene *scene)
{
	t_plane		*pl;
	t_tmp_heap	*tmp;

	pl = scene->plane;
	tmp = scene->tmp_heap;
	while (pl)
	{
		if (pl->flag_text == true)
			pl->text = get_image_texture(scene, pl->path);
		if (magnitude(*pl->normal_v) != 1.0)
		{
			write(2, NORMAL_PL, ft_strlen(NORMAL_PL));
			*pl->normal_v = normal(*pl->normal_v);
		}
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
	if (len < 4 || len > 8)
		print_scene_err(scene, ERR_PL_1);
	plane = ft_malloc(scene, sizeof(t_plane), false);
	plane->checker = _get_checker(scene, &line[4], ERR_PL_1, ERR_PL_2);
	if (plane->checker)
		plane->path = texture_parse(scene, &line[7], ERR_PL_1);
	else
		plane->path = texture_parse(scene, &line[4], ERR_PL_1);
	plane->flag_text = false;
	plane->pos = _get_position(scene, line[1], ERR_PL_1);
	plane->normal_v = _get_normal_v(scene, line[2], ERR_PL_1);
	check_color(scene, line[3], ERR_PL_1, ERR_PL_3);
	plane->color = _get_color(scene, line[3]);
	if (plane->path)
		plane->flag_text = true;
	plane->next = NULL;
	if (!scene->plane)
		scene->plane = plane;
	else
		add_pl_list(scene, plane);
}
