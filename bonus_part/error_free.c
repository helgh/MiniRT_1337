/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:09:21 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/02/06 17:28:58 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/Minirt.h"

double	**free_matrix(double **matrix)
{
	double	**mat;
	int		i;

	mat = matrix;
	i = 0;
	while (*mat)
	{
		i++;
		free(*mat);
		mat = (matrix + i);
	}
	free(matrix);
	return (NULL);
}

char	**free_split(char **split)
{
	char	**spl;
	int		i;

	spl = split;
	i = 0;
	while (*spl)
	{
		i++;
		free(*spl);
		spl = (split + i);
	}
	free(split);
	return (NULL);
}

void	_ft_free_part(t_scene *scene)
{
	if (scene->tmp_heap->line)
		free(scene->tmp_heap->line);
	if (scene->tmp_heap->spl)
		free_split(scene->tmp_heap->spl);
	if (scene->tmp_heap->split)
		free_split(scene->tmp_heap->split);
	if (scene->tmp_heap->trans)
		free_matrix(scene->tmp_heap->trans);
	if (scene->tmp_heap->scal)
		free_matrix(scene->tmp_heap->scal);
	if (scene->tmp_heap->rot)
		free_matrix(scene->tmp_heap->rot);
	if (scene->tmp_heap->all)
		free_matrix(scene->tmp_heap->all);
}

void	_ft_free_all(t_leaks *heap)
{
	t_leaks	*tmp;

	while (heap)
	{
		tmp = heap;
		heap = heap->next;
		free (tmp->address);
		free (tmp->_struct);
	}
}

void	print_scene_err(t_scene *scene, char *msg)
{
	int	i;

	i = -1;
	write(2, "Error\n", 7);
	while (msg[++i])
		write(2, &msg[i], 1);
	__ft_free(scene, ALL, EXIT_FAILURE);
}
