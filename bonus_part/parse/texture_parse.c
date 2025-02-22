/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:35:35 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/02/22 20:52:48 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Minirt.h"

t_texture	*get_image_texture(t_scene *scene, char *path)
{
	t_mlx		*mlx;
	t_texture	*texture;

	texture = ft_malloc(scene, sizeof(t_texture), true);
	mlx = malloc(sizeof(t_mlx));
	mlx->mlx = mlx_init();
	texture->texture = mlx_xpm_file_to_image(mlx->mlx, path, \
		&texture->w, &texture->h);
	if (!texture->texture)
	{
		free(path);
		print_scene_err(scene, BAD_FILE_TEXTURE);
	}
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
	return (strdup((const char *) path));
}

char	*texture_parse(t_scene *scene, char **line, char *msg)
{
	char	*path;
	int		cmp;

	cmp = ft_strcmp(line[0], "\n");
	if (!cmp)
		return (NULL);
	if (line[1] && ft_strcmp(line[1], "\n"))
		print_scene_err(scene, msg);
	if (cmp)
	{
		if (strncmp(line[0], "texture=", 8))
			print_scene_err(scene, msg);
		scene->tmp_heap->split = ft_split(scene, line[0], '=');
		if (lengh(scene->tmp_heap->split) != 2)
			print_scene_err(scene, msg);
		else
			path = check_path(scene, scene->tmp_heap->split[1]);
	}
	scene->tmp_heap->split = free_split(scene->tmp_heap->split);
	return (path);
}
