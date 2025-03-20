/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spot_light_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:27:21 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/03/19 21:56:26 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Minirt_bonus.h"

static void	add_light_list(t_scene *scene, t_light *l)
{
	static t_light	*light;

	if (!light)
	{
		light = scene->light;
		light->next = l;
		light = light->next;
	}
	else
	{
		light->next = l;
		light = light->next;
	}
}

void	parse_light(t_scene *scene, char **line)
{
	t_light		*light;
	int			len;

	len = lengh(line);
	if (len != 4 || valid_float(line[2], false))
		print_scene_err(scene, ERR_L_1);
	light = ft_malloc(scene, sizeof(t_light));
	ft_memset(light, 0, sizeof(t_light));
	light->pos = _get_position(scene, line[1], ERR_L_1);
	light->intensity = ft_atof(line[2]);
	check_color(scene, line[3], ERR_L_1, ERR_L_2);
	light->f_color = _get_color(scene, line[3]);
	if (light->intensity < 0.0 || light->intensity > 1.0)
		print_scene_err(scene, ERR_L_2);
	light->f_color = color_scal(light->f_color, light->intensity, MULT);
	if (!scene->light)
		scene->light = light;
	else
		add_light_list(scene, light);
}
