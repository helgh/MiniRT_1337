/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parse_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:35:35 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/03/21 01:16:29 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Minirt_bonus.h"

t_texture	get_image_texture(t_scene *scene, char *path)
{
	t_texture	texture;

	if (scene->mlx->init == false)
	{
		scene->mlx->mlx = mlx_init();
		scene->mlx->init = true;
	}
	texture.texture = mlx_xpm_file_to_image(scene->mlx->mlx, path, \
		&texture.w, &texture.h);
	if (!texture.texture)
		print_scene_err(scene, BAD_FILE_TEXTURE);
	texture.data = mlx_get_data_addr(texture.texture, &texture.bpp, \
		&texture.s_line, &texture.endian);
	return (texture);
}

char	*check_path(t_scene *scene, char *path)
{
	int	i;

	i = -1;
	(void) scene;
	while (path[++i] && path[i] != '\n')
		;
	if (path[i] == '\n')
		path[i] = 0;
	return (ft_strdup(scene, (const char *) path));
}

char	*texture_parse(t_scene *scene, char **line, char *msg)
{
	char	*path;

	path = NULL;
	if (!line[0] || !ft_strcmp(line[0], "\n") || lengh(line) != 1)
		return (NULL);
	if (ft_strncmp(line[0], "texture=", 8))
		print_scene_err(scene, msg);
	scene->tmp_heap->split = ft_split(scene, line[0], '=');
	if (lengh(scene->tmp_heap->split) != 2)
		print_scene_err(scene, msg);
	else
		path = check_path(scene, scene->tmp_heap->split[1]);
	scene->tmp_heap->split = free_split(scene->tmp_heap->split);
	return (path);
}
