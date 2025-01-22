/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:47:01 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/01/22 18:27:19 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

static void	_ft_free_part(t_leaks *heap)
{
	t_leaks	*tmp;

	while(heap && heap->next)
	{
		tmp = heap;
		heap = heap->next;
		if (tmp->address && tmp->is_free == true)
		{
			free (tmp->address);
			free (tmp->_struct);
			tmp->address = NULL;
		}
	}
	tmp = heap;
	if (tmp && tmp->is_free == true)
	{
		free (tmp->address);
		free (tmp->_struct);
		heap->address = NULL;
	}
}

static void	_ft_free_all(t_leaks *heap)
{
	t_leaks	*tmp;

	while (heap && heap->next)
	{
		tmp = heap;
		heap = heap->next;
		if (tmp->address)
		{
			free (tmp->address);
			free (tmp->_struct);
		}
	}
	if (heap)
	{
		free (heap->address);
		free (heap->_struct);
	}
}

static t_leaks	*leaks_collector(void *for_leaks, t_leaks **heap, bool flag)
{
	t_leaks	*tmp;
	t_leaks	*new;

	tmp = *heap;
	new = malloc(sizeof(t_leaks));
	if (!new)
		return (NULL);
	new->address = for_leaks;
	new->_struct = new;
	new->next = NULL;
	new->is_free = flag;
	if (!*heap)
		return (*heap = new);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (*heap);
}

void	__ft_free(t_scene *scene, int flag, int exit_status)
{

	if (flag == ALL)
	{
		_ft_free_all(scene->heap);
		exit(exit_status);
	}
	else
		_ft_free_part(scene->heap);
}


void	*ft_malloc(t_scene *scene, size_t size, bool flag)
{
	void	*new;

	new = malloc (size);
	if (!new)
		return (__ft_free(scene, ALL, EXIT_FAILURE), NULL);
	if (!leaks_collector(new, &scene->heap, flag))
		return (free(new), __ft_free(scene, ALL, EXIT_FAILURE), NULL);
	return (new);
}
