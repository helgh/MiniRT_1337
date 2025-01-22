/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:44:53 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/01/22 18:30:11 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

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
	// __ft_free(scene, PART, 0);
	return (color);
}

void	check_color(t_scene *scene, char *str)
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
		print_scene_err(scene, ERR_A_1);
	while (tmp[++s])
	{
		i = -1;
		while (ft_isdigit(tmp[s][++i]))
			;
		if (tmp[s][i] && tmp[s][i] != 10)
			print_scene_err(scene, ERR_A_1);
		if (ft_atoi(tmp[s]) > 255)
			print_scene_err(scene, ERR_A_3);
	}
	// __ft_free(scene, PART, 0);
}

int		valid_float(char *str)
{
	int	i;
	int	flag;

	i = -1;
	flag = 0;
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

void	parse_ab_light(t_scene *scene, char **line)
{
	t_am_light	*ab_light;
	float		n;
	int			len;

	len = lengh(line);
	if (scene->Ambient)
		print_scene_err(scene, ERR_A);
	ab_light = ft_malloc(scene, sizeof(t_am_light), false);
	scene->Ambient = ab_light;
	if (len != 3 && len != 4)
		print_scene_err(scene, ERR_A_1);
	if ((len == 4 && strcmp(line[len - 1], "\n"))
			|| valid_float(line[1]))
		print_scene_err(scene, ERR_A_1);
	n = ft_atof(line[1]);
	if (n > 1 || n < EPSILON)
		print_scene_err(scene, ERR_A_2);
	ab_light->am_ratio = n;
	check_color(scene, line[2]);
	ab_light->color = _get_color(scene, line[2]);
}

void	parse_element(t_scene *scene, char **line, int fd)
{
	(void) fd;
	if (!strcmp(line[0], "A"))
		parse_ab_light(scene, line);
	// else if (!strcmp(line[0], "C"))
	// 	parse_camera(scene, line);
	// else if (!strcmp(line[0], "L"))
	// 	parse_light(scene, line);
	// else if (!strcmp(line[0], "sp"))
	// 	parse_sphere(scene, line);
	// else if (!strcmp(line[0], "pl"))
	// 	parse_plane(scene, line);
	// else if (!strcmp(line[0], "cy"))
	// 	parse_cylinder(scene, line);
}

void	parse_scene(t_scene *scene, char *str)
{
	char	*buff;
	char	**spl;
	int		fd;

	fd = open(str, O_RDONLY);
	if (fd < 0)
		ft_printf(OPEN_FILE_ERR, STDERR_FILENO);
	while (1)
	{
		buff = get_next_line(fd);
		if (!buff)
			break ;
		if (strcmp(buff, "\n"))
		{
			spl = ft_split(scene, buff, 32);
			parse_element(scene, spl, fd);
			__ft_free(scene, PART, 0);
			free(buff);
		}
		else
			free(buff);
	}
	close(fd);
}

t_scene	*init_struct(void)
{
	t_scene	*scene;

	scene = malloc(sizeof(t_scene));
	if (!scene)
		return (NULL);
	scene->Ambient = NULL;
	scene->camera = NULL;
	scene->light = NULL;
	scene->sphere = NULL;
	scene->plane = NULL;
	scene->cylinder = NULL;
	scene->heap = NULL;
	return (scene);
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
		return (1);
	if (ac != 2)
		return (free(scene), write(2, "Invalid argument\n", strlen("Invalid argument\n")), 1);
	if (check_extention(av[1]))
		return (1);
	parse_scene(scene, av[1]);
	__ft_free(scene, ALL, 0);
}