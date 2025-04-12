/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:44:53 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/04/12 23:09:11 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/Minirt_bonus.h"

static int	check_extention(t_scene *scene, const char *str)
{
	const char	*extention;
	int			i;
	int			fd;

	i = -1;
	extention = (const char *) ".rt";
	fd = open(str, O_RDONLY);
	if (!ft_strcmp(str + (ft_strlen(str) - 3), extention))
	{
		if (fd < 0)
			return (print_scene_err(scene, OPEN_FILE_ERR), 1);
		return (close(fd), EXIT_SUCCESS);
	}
	return (close(fd), EXIT_FAILURE);
}

static void	init_struct(t_scene *scene)
{
	ft_memset(scene, 0, sizeof(t_scene));
	scene->tmp_heap = ft_malloc(scene, sizeof(t_tmp_heap));
	ft_memset(scene->tmp_heap, 0, sizeof(t_tmp_heap));
	scene->tmp_heap->fd = -1;
	scene->mlx.init = false;
}

int	main(int ac, char **av)
{
	t_scene	scene;

	init_struct(&scene);
	if (ac != 2)
		return (print_scene_err(&scene, "Invalid argument\n"), 1);
	if (check_extention(&scene, av[1]))
		return (print_scene_err(&scene, "invalid extention\n"), 1);
	parse_part(&scene, av[1]);
	render(&scene);
}
