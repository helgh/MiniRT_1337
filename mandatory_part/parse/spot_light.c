/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spot_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:27:21 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/03/20 00:28:01 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Minirt.h"

void	parse_light(t_scene *scene, char **line)
{
	t_light		*light;
	int			len;

	len = lengh(line);
	if (scene->light)
		print_scene_err(scene, ERR_L);
	if (len != 3 || valid_float(line[2], false))
		print_scene_err(scene, ERR_L_1);
	light = ft_malloc(scene, sizeof(t_light));
	light->pos = _get_position(scene, line[1], ERR_L_1);
	light->intensity = ft_atof(line[2]);
	if (light->intensity < 0.0 || light->intensity > 1.0)
		print_scene_err(scene, ERR_L_2);
	light->f_color = color(light->intensity, light->intensity, \
		light->intensity);
	scene->light = light;
}
