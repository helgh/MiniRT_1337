/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:34:14 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/03/20 00:14:57 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Minirt_bonus.h"

static void	important_element(t_scene *scene)
{
	if (!scene->ambient)
		print_scene_err(scene, "  No ambient light found \n");
	if (!scene->camera)
		print_scene_err(scene, "  No camera found\n");
}

static void	parse_element(t_scene *scene, char **line)
{
	if (!strcmp(line[0], "A"))
		parse_ab_light(scene, line);
	else if (!strcmp(line[0], "C"))
		parse_camera(scene, line);
	else if (!strcmp(line[0], "l"))
		parse_light(scene, line);
	else if (!strcmp(line[0], "sp"))
		parse_sphere(scene, line);
	else if (!strcmp(line[0], "pl"))
		parse_plane(scene, line);
	else if (!strcmp(line[0], "cy"))
		parse_cylinder(scene, line);
	else if (!strcmp(line[0], "co"))
		parse_cone(scene, line);
	else
		print_scene_err(scene, BAD_TYPE);
}

static void	parse_scene(t_scene *scene, char *str)
{
	scene->tmp_heap->fd = open(str, O_RDONLY);
	if (scene->tmp_heap->fd < 0)
		print_scene_err(scene, OPEN_FILE_ERR);
	while (1)
	{
		scene->tmp_heap->line = get_next_line(scene, scene->tmp_heap->fd);
		if (!scene->tmp_heap->line)
			break ;
		if (scene->tmp_heap->line[0] != 0 && scene->tmp_heap->line[0] != '\n')
		{
			scene->tmp_heap->spl = ft_split(scene, scene->tmp_heap->line, 32);
			parse_element(scene, scene->tmp_heap->spl);
			scene->tmp_heap->spl = free_split(scene->tmp_heap->spl);
		}
		free(scene->tmp_heap->line);
	}
	close(scene->tmp_heap->fd);
	scene->tmp_heap->fd = -1;
}

void	parse_part(t_scene *scene, char *str)
{
	parse_scene(scene, str);
	important_element(scene);
}
