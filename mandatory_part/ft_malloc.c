/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:47:01 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/02/02 15:04:00 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

t_leaks	*ft_lstlast(t_leaks *lst)
{
	if (lst != NULL)
	{
		while (lst->next != NULL)
			lst = lst -> next;
		return (lst); 
	}
	return (NULL); 
}

void	ft_lstadd_back(t_leaks **lst, t_leaks *new)
{
	t_leaks	*temp;

	if (new != NULL)
	{
		if (*lst != NULL)
		{
			temp = ft_lstlast((*lst));
			temp -> next = new;
		}
		else
			(*lst) = new;
	}
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
}

static void	_ft_free_all(t_leaks *heap)
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

static t_leaks	*leaks_collector(void *for_leaks, t_leaks **heap, bool flag)
{
	static t_leaks	*head;
	static t_leaks	*tail;
	t_leaks			*new;

	new = malloc(sizeof(t_leaks));
	if (!new)
		return (NULL);
	new->address = for_leaks;
	new->_struct = new;
	new->next = NULL;
	new->is_free = flag;
	if (!*heap)
	{
		*heap = new;
		tail = *heap;
		head = *heap;
	}
	else
	{
		tail->next = new;
		tail = tail->next;
	}
	return (new);
}

void	__ft_free(t_scene *scene, int flag, int exit_status)
{

	(void) flag;
	_ft_free_part(scene);
	_ft_free_all(scene->heap);
	if (scene->tmp_heap->fd >= 0)
		close(scene->tmp_heap->fd);
	free(scene->tmp_heap);
	free(scene);
	exit(exit_status);
}

void	*ft_malloc(t_scene *scene, size_t size, bool flag)
{
	void	*new;

	new = malloc (size);
	if (!new)
		return (print_scene_err(scene, F_MALL), NULL);
	if (!leaks_collector(new, &scene->heap, flag))
		return (free(new), print_scene_err(scene, F_MALL), NULL);
	return (new);
}
