/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:44:53 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/01/23 20:29:06 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

void	add_to_list(t_scene *scene, int type)
{
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylinder	*cylinder;

	if (type == SPHERE)
	{
		while (scene->sphere)
			scene->sphere = scene->sphere->next;
		sphere = ft_malloc(scene, sizeof(t_sphere), false);
		scene->sphere = sphere;
	}
	else if (type == PLANE)
	{
		while (scene->plane)
			scene->plane = scene->plane->next;
		plane = ft_malloc(scene, sizeof(t_plane), false);
		scene->plane = plane;
	}
	else if (type == CYLINDER)
	{
		while (scene->cylinder)
			scene->cylinder = scene->cylinder->next;
		cylinder = ft_malloc(scene, sizeof(t_cylinder), false);
		scene->cylinder = cylinder;
	}
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int		lengh(char **str)
{
	int	i;

	i = -1;
	if (!str)
		return (0);
	while (str[++i])
		;
	return (i);
}

static void	ft_printf(char *str, int fd)
{
	int	i;

	i = -1;
	while (str[++i])
		write(fd, &str[i], 1);
}

static int	check_extention(const char *str)
{
	const char	*extention;
	int			i;
	int			fd;

	i = -1;
	extention = (const char *) ".rt";
	fd = open(str, O_RDONLY);
	if (!strncmp(str + (strlen(str) - 3), extention, (unsigned long) 3))
	{
		if (fd < 0)
			return (write(2, "No such file\n", 14), 1);
		return (close(fd), EXIT_SUCCESS);
	}
	return (close(fd), write(2, "invalid extention\n", 19), EXIT_FAILURE);
}

static void	print_scene_err(t_scene *scene, char *msg)
{
	int	i;

	i = -1;
	write(2, "Error\n", 7);
	while (msg[++i])
		write(2, &msg[i], 1);
	free(scene->line);
	if (scene->fd >= 0)
		close(scene->fd);
	__ft_free(scene, ALL, EXIT_FAILURE);
}

t_color	_get_color(t_scene *scene, char *line)
{
	t_color	color;
	char	**tmp;

	tmp = ft_split(scene, line, ',');
	color.r = ft_atoi(tmp[0]);
	color.g = ft_atoi(tmp[1]);
	color.b = ft_atoi(tmp[2]);
	return (color);
}

void	check_color(t_scene *scene, char *str, char *err1, char *err2)
{
	char	**tmp;
	int		i;
	int		s;
	int		len;

	s = -1;
	i = -1;
	tmp = ft_split(scene, str, ',');
	len = lengh(tmp);
	if (len != 3 && len != 4)
		print_scene_err(scene, err1);
	while (tmp[++s])
	{
		i = -1;
		while (ft_isdigit(tmp[s][++i]))
			;
		if (tmp[s][i] && tmp[s][i] != 10)
			print_scene_err(scene, err1);
		if (ft_atoi(tmp[s]) > 255)
			print_scene_err(scene, err2);
	}
}

int		valid_float(char *str, bool checker)
{
	int	i;
	int	flag;

	i = -1;
	flag = 0;
	if (checker == true && str[0] == 45)
		i++;
	while (str[++i])
	{
		if (!ft_isdigit(str[0]))
			return (1);
		if (!ft_isdigit(str[i]))
			if (str[i] != 46 || flag == 1)
				return (1);
		if (str[i] == 46)
			flag = 1;
	}
	return (0);
}

t_tuple	_get_normal_v(t_scene *scene, char *line, char *err1, char *err2)
{
	t_tuple	normal_v;
	double	cord[3];
	char	**tmp;
	int		i;

	i = -1;
	tmp = ft_split(scene, line, ',');
	while (tmp[++i])
	{
		if (valid_float(tmp[i], true))
			print_scene_err(scene, err1);
		cord[i] = ft_atof(tmp[i]);
		if (cord[i] < -1.0 || cord[i] > 1.0)
			print_scene_err(scene, err2);
	}
	normal_v.x = cord[0];
	normal_v.y = cord[1];
	normal_v.z = cord[2];
	normal_v.w = 0;
	return (normal_v);
}

t_tuple	_get_position(t_scene *scene, char *line, char *error)
{
	t_tuple	pos;
	double	cord[3];
	char	**tmp;
	int		i;

	i = -1;
	tmp = ft_split(scene, line, ',');
	while (tmp[++i])
	{
		if (valid_float(tmp[i], true))
			print_scene_err(scene, error);
		cord[i] = ft_atof(tmp[i]);
	}
	pos.x = cord[0];
	pos.y = cord[1];
	pos.z = cord[2];
	pos.w = 1;
	return (pos);
}

int		_get_fov(t_scene *scene, char *line)
{
	int		fov;
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
	fov = ft_atoi(line);
	if (fov < 0 || fov > 180)
		print_scene_err(scene, ERR_C_3);
	return (fov);
}

void	parse_cylinder(t_scene *scene, char **line)
{
	t_cylinder	*cylinder;
	t_tuple		pos;
	t_tuple		normal_v;
	t_color		color;
	int			len;

	len = lengh(line);
	if (len != 6 && len != 7)
		print_scene_err(scene, ERR_CY_1);
	if (len == 7 && strcmp(line[len - 1], "\n"))
		print_scene_err(scene, ERR_CY_1);
	pos = _get_position(scene, line[1], ERR_CY_1);
	normal_v = _get_normal_v(scene, line[2], ERR_CY_1, ERR_CY_2);
	if (valid_float(line[3], false) || valid_float(line[4], false))
		print_scene_err(scene, ERR_CY_1);
	check_color(scene, line[5], ERR_CY_1, ERR_CY_3);
	color = _get_color(scene, line[5]);
	add_to_list(scene, CYLINDER);
	cylinder->cord = pos;
	cylinder->normal_v = normal_v;
	cylinder->diameter = ft_atof(line[3]);
	cylinder->height = ft_atof(line[4]);
	cylinder->color = color;
	cylinder->next = NULL;
}

void	parse_plane(t_scene *scene, char **line)
{
	t_plane	*plane;
	t_tuple	pos;
	t_tuple	normal_v;
	t_color	color;
	int		len;

	len = lengh(line);
	if (len != 4 && len != 5)
		print_scene_err(scene, ERR_PL_1);
	if (len == 5 && strcmp(line[len - 1], "\n"))
		print_scene_err(scene, ERR_PL_1);
	pos = _get_position(scene, line[1], ERR_PL_1);
	normal_v = _get_normal_v(scene, line[2], ERR_PL_1, ERR_PL_2);
	check_color(scene, line[3], ERR_PL_1, ERR_PL_3);
	color = _get_color(scene, line[3]);
	add_to_list(scene, PLANE);
	plane->cord = pos;
	plane->normal_v = normal_v;
	plane->color = color;
	plane->next = NULL;
}

void	parse_sphere(t_scene *scene, char **line)
{
	t_sphere	*sphere;
	t_tuple		pos;
	t_color		color;
	int			len;

	len = lengh(line);
	if (len != 4 && len != 5)
		print_scene_err(scene, ERR_SP_1);
	if (len == 5 && strcmp(line[len - 1], "\n"))
		print_scene_err(scene, ERR_SP_1);
	pos = _get_position(scene, line[1], ERR_SP_1);
	if (valid_float(line[2], false))
		print_scene_err(scene, ERR_SP_1);
	check_color(scene, line[3], ERR_SP_1, ERR_SP_2);
	color = _get_color(scene, line[3]);
	add_to_list(scene, SPHERE);
	sphere->cord = pos;
	sphere->color = color;
	sphere->diameter = ft_atof(line[2]);
	sphere->next = NULL;
}

void	parse_light(t_scene *scene, char **line)
{
	t_light		*light;
	t_tuple		pos;
	double		ratio;
	int			len;

	len = lengh(line);
	if (scene->light)
		print_scene_err(scene, ERR_L);
	if (len != 3 && len != 4)
		print_scene_err(scene, ERR_L_1);
	if ((len == 4 && strcmp(line[len - 1], "\n")))
		print_scene_err(scene, ERR_L_1);
	pos = _get_position(scene, line[1], ERR_L_1);
	if (valid_float(line[2], false))
		print_scene_err(scene, ERR_L_1);
	ratio = ft_atof(line[2]);
	if (ratio < 0 || ratio > 1)
		print_scene_err(scene, ERR_L_2);
	light = ft_malloc(scene, sizeof(t_light), false);
	light->pos = pos;
	light->brightness = ratio;
	scene->light = light;
}

void	parse_camera(t_scene *scene, char **line)
{
	t_camera	*camera;
	t_tuple		pos;
	t_tuple		normal_v;
	int			len;
	int			fov;

	len = lengh(line);
	if (scene->camera)
		print_scene_err(scene, ERR_C);
	if (len != 4 && len != 5)
		print_scene_err(scene, ERR_C_1);
	if ((len == 5 && strcmp(line[len - 1], "\n")))
		print_scene_err(scene, ERR_C_1);
	pos = _get_position(scene, line[1], ERR_C_1);
	normal_v = _get_normal_v(scene, line[2], ERR_C_1, ERR_C_2);
	fov = _get_fov(scene, line[3]);
	camera = ft_malloc(scene, sizeof(t_camera), false);
	scene->camera = camera;
	scene->camera->pos = pos;
	scene->camera->normal_v = normal_v;
	scene->camera->FOV = fov;
}

void	parse_ab_light(t_scene *scene, char **line)
{
	t_am_light	*ab_light;
	t_color		color;
	double		n;
	int			len;

	len = lengh(line);
	if (scene->Ambient)
		print_scene_err(scene, ERR_A);
	if (len != 3 && len != 4)
		print_scene_err(scene, ERR_A_1);
	if ((len == 4 && strcmp(line[len - 1], "\n"))
			|| valid_float(line[1], false))
		print_scene_err(scene, ERR_A_1);
	n = ft_atof(line[1]);
	if (n > 1 || n < EPSILON)
		print_scene_err(scene, ERR_A_2);
	check_color(scene, line[2], ERR_A_1, ERR_A_3);
	color = _get_color(scene, line[2]);
	ab_light = ft_malloc(scene, sizeof(t_am_light), false);
	scene->Ambient = ab_light;
	ab_light->am_ratio = n;
	ab_light->color = _get_color(scene, line[2]);
}

void	important_element(t_scene *scene)
{
	if (!scene->Ambient)
		print_scene_err(scene, "  No ambient light found \n");
	if (!scene->camera)
		print_scene_err(scene, "  No camera found\n");
	if (!scene->light)
		print_scene_err(scene, "  No light found\n");
}


void	parse_element(t_scene *scene, char **line)
{
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

void	parse_scene(t_scene *scene, char *str)
{
	char	**spl;

	scene->fd = open(str, O_RDONLY);
	if (scene->fd < 0)
		print_scene_err(scene, OPEN_FILE_ERR);
	while (1)
	{
		scene->line = get_next_line(scene->fd);
		if (!scene->line)
			break ;
		if (strcmp(scene->line, "\n"))
		{
			spl = ft_split(scene, scene->line, 32);
			parse_element(scene, spl);
			__ft_free(scene, PART, 0);
			free(scene->line);
		}
		else
			free(scene->line);
	}
	close(scene->fd);
	scene->fd = -1;
}

t_scene	*init_struct(void)
{
	t_scene	*scene;

	scene = malloc(sizeof(t_scene));
	if (!scene)
		return (NULL);
	scene->fd = 0;
	scene->line = NULL;
	scene->Ambient = NULL;
	scene->camera = NULL;
	scene->light = NULL;
	scene->sphere = NULL;
	scene->plane = NULL;
	scene->cylinder = NULL;
	scene->heap = NULL;
	return (scene);
}

void	am_light_compenent(t_scene *scene)
{
	t_color		color;
	double		ratio;

	ratio = scene->Ambient->am_ratio;
	color = scene->Ambient->color;
	color = op_color(color, color, 0, ratio);
	color.r /= 255;
	color.g /= 255;
	color.b /= 255;
	scene->Ambient->f_color = color;
}

void	camera_compenent(t_scene *scene)
{
	t_camera	*camera;

	camera = scene->camera;
	camera->transform = view_transform(scene, camera->pos, camera->normal_v);
	camera->inv_transform = inverse(scene, camera->transform);
	camera->aspect = WIDTH / HEIGHT;
	if (camera->aspect >= 1)
	{
		camera->half_width = tan(camera->FOV / 2);
		camera->half_height = camera->half_width / camera->aspect;
	}
	else
	{
		camera->half_height = tan(camera->FOV / 2);
		camera->half_width = camera->half_height * camera->aspect;
	}
	camera->pixel_size = (camera->half_width * 2) / camera->hor_size;
}

void	light_compenent(t_scene *scene)
{
	t_color		color;
	double		ratio;

	ratio = scene->light->brightness;
	color = scene->light->color;
	color = op_color(color, color, 0, ratio);
	color.r /= 255;
	color.g /= 255;
	color.b /= 255;
	scene->light->f_color = color;
}

void	parse_part(t_scene *scene, char *str)
{
	parse_scene(scene, str);
	important_element(scene);
	am_light_compenent(scene);
	camera_compenent(scene);
	light_compenent(scene);
}

void	leaks(void)
{
	system("leaks -q miniRT");
}

int main(int ac, char **av)
{
	t_scene	*scene;

	atexit(leaks);
	scene = init_struct();
	if (!scene)
		return (write(2, "Allocation failed!\n", strlen("Allocation failed")), 1);
	if (ac != 2)
		return (free(scene), write(2, "Invalid argument\n", strlen("Invalid argument\n")), 1);
	if (check_extention(av[1]))
		return (free(scene), 1);
	parse_part(scene, av[1]);
	// printf("scene->ambient->am_ratio: %f\n", scene->Ambient->am_ratio);
	// printf("scene->ambient->color.r: %f\n", scene->Ambient->color.r);
	// printf("scene->ambient->color.g: %f\n", scene->Ambient->color.g);
	// printf("scene->ambient->color.b: %f\n", scene->Ambient->color.b);
	// printf("scene->camera->pos.x: %f\n", scene->camera->pos.x);
	// printf("scene->camera->pos.y: %f\n", scene->camera->pos.y);
	// printf("scene->camera->pos.z: %f\n", scene->camera->pos.z);
	__ft_free(scene, ALL, 0);
	free(scene);
}