/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ab_light_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:25:40 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/03/05 18:13:55 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Minirt_bonus.h"

static void	am_light_compenent(t_scene *scene, t_am_light *am_light)
{
	t_color		color;
	double		ratio;

	(void) scene;
	ratio = am_light->am_ratio;
	color = *am_light->f_color;
	color = color_scal(color, ratio, MULT);
	am_light->f_color->r = color.r;
	am_light->f_color->g = color.g;
	am_light->f_color->b = color.b;
}

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
	am_light_compenent(scene, scene->ambient);
}
