/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:44:53 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/02/07 17:42:11 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/Minirt.h"

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

static t_scene	*init_struct(void)
{
	t_scene	*scene;

	scene = malloc(sizeof(t_scene));
	if (!scene)
		return (NULL);
	scene->tmp_heap = malloc(sizeof(t_tmp_heap));
	if (!scene->tmp_heap)
		return (free(scene), NULL);
	scene->tmp_heap->fd = -1;
	scene->tmp_heap->line = NULL;
	scene->tmp_heap->spl = NULL;
	scene->tmp_heap->split = NULL;
	scene->tmp_heap->trans = NULL;
	scene->tmp_heap->scal = NULL;
	scene->tmp_heap->rot = NULL;
	scene->tmp_heap->all = NULL;
	scene->ambient = NULL;
	scene->camera = NULL;
	scene->light = NULL;
	scene->sphere = NULL;
	scene->plane = NULL;
	scene->cylinder = NULL;
	scene->sect = NULL;
	scene->heap = NULL;
	return (scene);
}

int main(int ac, char **av)
{
	t_scene	*scene;

	scene = init_struct();
	if (!scene)
		return (write(2, "Allocation failed!\n", strlen("Allocation failed")), 1);
	if (ac != 2)
		return (free(scene), write(2, "Invalid argument\n", strlen("Invalid argument\n")), 1);
	if (check_extention(av[1]))
		return (free(scene->tmp_heap), free(scene), 1);
	parse_part(scene, av[1]);
	render(scene);
}