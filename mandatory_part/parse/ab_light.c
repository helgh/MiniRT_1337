/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ab_light.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:25:40 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/03/20 00:23:21 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Minirt.h"

void	parse_ab_light(t_scene *scene, char **line)
{
	int			len;

	len = lengh(line);
	if (scene->ambient)
		print_scene_err(scene, ERR_A);
	if (len != 3 || valid_float(line[1], false))
		print_scene_err(scene, ERR_A_1);
	scene->ambient = ft_malloc(scene, sizeof(t_am_light));
	scene->ambient->am_ratio = ft_atof(line[1]);
	if (scene->ambient->am_ratio > 1 || scene->ambient->am_ratio < 0.0)
		print_scene_err(scene, ERR_A_2);
	check_color(scene, line[2], ERR_A_1, ERR_A_3);
	scene->ambient->f_color = _get_color(scene, line[2]);
	scene->ambient->f_color = color_scal(scene->ambient->f_color, \
		scene->ambient->am_ratio, MULT);
}
