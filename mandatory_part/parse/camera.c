/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:27:59 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/03/08 23:10:08 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Minirt.h"

static double	_get_fov(t_scene *scene, char *line)
{
	double	fov;
	int		i;

	i = -1;
	while (line[++i])
	{
		if (!ft_isdigit(line[i]))
		{
			if (line[i] == 10)
				break ;
			print_scene_err(scene, ERR_C_1);
		}
	}
	fov = ft_atof(line);
	if (fov < 0.0 || fov >= 180.0)
		print_scene_err(scene, ERR_C_3);
	return (fov);
}

static void	camera_compenent(t_scene *scene)
{
	t_tmp_heap	*tmp;
	t_camera	*cam;
	t_tuple		up;

	up = vector(0.0, 1.0, 0.0);
	tmp = scene->tmp_heap;
	cam = scene->camera;
	tmp->all = view_transform(scene, *cam->pos, *cam->normal_v, up);
	cam->inv_transform = inverse(scene, tmp->all);
	tmp->all = free_matrix(tmp->all);
	cam->aspect = (double) WIDTH / (double) HEIGHT;
	if (cam->aspect >= 1.0)
	{
		cam->half_width = tan(cam->fov / 2.0);
		cam->half_height = cam->half_width / cam->aspect;
	}
	else
	{
		cam->half_height = tan(cam->fov / 2.0);
		cam->half_width = cam->half_height * cam->aspect;
	}
	cam->pixel_size = (cam->half_width * 2.0) / (double) WIDTH;
}

void	parse_camera(t_scene *scene, char **line)
{
	t_camera	*camera;
	int			len;

	len = lengh(line);
	if (scene->camera)
		print_scene_err(scene, ERR_C);
	if (len != 4)
		print_scene_err(scene, ERR_C_1);
	camera = ft_malloc(scene, sizeof(t_camera));
	camera->fov = degree_to_rad(_get_fov(scene, line[3]));
	camera->pos = _get_position(scene, line[1], ERR_C_1);
	camera->normal_v = _get_normal_v(scene, line[2], ERR_C_1, ERR_C_2);
	if (magnitude(*camera->normal_v) != 1.0)
	{
		write(2, NORMAL_C, ft_strlen(NORMAL_C));
		*camera->normal_v = normal(*camera->normal_v);
	}
	scene->camera = camera;
	camera_compenent(scene);
}
