/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spot_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:27:21 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/02/16 19:01:16 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Minirt.h"

static void	light_compenent(t_scene *scene, t_light *light)
{
	double		ratio;

	light->f_color = ft_malloc(scene, sizeof(t_color));
	ratio = light->intensity;
	light->f_color->r = ratio;
	light->f_color->g = ratio;
	light->f_color->b = ratio;
}

void	parse_light(t_scene *scene, char **line)
{
	t_light		*light;
	int			len;

	len = lengh(line);
	if (scene->light)
		print_scene_err(scene, ERR_L);
	if (len != 3 && len != 4)
		print_scene_err(scene, ERR_L_1);
	if ((len == 4 && strcmp(line[len - 1], "\n")))
		print_scene_err(scene, ERR_L_1);
	if (valid_float(line[2], false))
		print_scene_err(scene, ERR_L_1);
	light = ft_malloc(scene, sizeof(t_light));
	light->pos = _get_position(scene, line[1], ERR_L_1);
	light->intensity = ft_atof(line[2]);
	if (light->intensity < 0.0 || light->intensity > 1.0)
		print_scene_err(scene, ERR_L_2);
	scene->light = light;
	light_compenent(scene, scene->light);
}
