/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:34:14 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/02/07 17:54:12 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Minirt.h"

static void	important_element(t_scene *scene)
{
	if (!scene->ambient)
		print_scene_err(scene, "  No ambient light found \n");
	if (!scene->camera)
		print_scene_err(scene, "  No camera found\n");
	if (!scene->light)
		print_scene_err(scene, "  No light found\n");
}

static void	parse_element(t_scene *scene, char **line)
{
	if (!line[0])
		return ;
	if (!strcmp(line[0], "A"))
		parse_ab_light(scene, line);
	else if (!strcmp(line[0], "C"))
		parse_camera(scene, line);
	else if (!strcmp(line[0], "L"))
		parse_light(scene, line);
	else if (!strcmp(line[0], "sp"))
		parse_sphere(scene, line);
	else if (!strcmp(line[0], "pl"))
		parse_plane(scene, line);
	else if (!strcmp(line[0], "cy"))
		parse_cylinder(scene, line);
	else
		print_scene_err(scene, "  Invalid element\n");
}

static void	parse_scene(t_scene *scene, char *str)
{
	scene->tmp_heap->fd = open(str, O_RDONLY);
	if (scene->tmp_heap->fd < 0)
		print_scene_err(scene, OPEN_FILE_ERR);
	while (1)
	{
		scene->tmp_heap->line = get_next_line(scene->tmp_heap->fd);
		if (!scene->tmp_heap->line)
			break ;
		if (strcmp(scene->tmp_heap->line, "\n"))
		{
			scene->tmp_heap->spl = ft_split(scene, scene->tmp_heap->line, 32);
			parse_element(scene, scene->tmp_heap->spl);
			scene->tmp_heap->spl = free_split(scene->tmp_heap->spl);
			free(scene->tmp_heap->line);
			scene->tmp_heap->line = NULL;
		}
		else
			free(scene->tmp_heap->line);
	}
	close(scene->tmp_heap->fd);
	scene->tmp_heap->fd = -1;
}

void	parse_part(t_scene *scene, char *str)
{
	parse_scene(scene, str);
	important_element(scene);
	sphere_compenent(scene);
	plane_compenent(scene);
	cylinder_compenent(scene);
}
