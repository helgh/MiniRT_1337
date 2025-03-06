/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:47:01 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/03/06 18:12:57 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	__ft_free(t_scene *scene, int exit_status)
{
	_ft_free_part(scene);
	_ft_free_all(scene->heap);
	if (scene->tmp_heap->fd >= 0)
		close(scene->tmp_heap->fd);
	free(scene->tmp_heap);
	free(scene);
	exit(exit_status);
}

static t_leaks	*leaks_collector(void *for_leaks, t_leaks **heap)
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

void	*ft_malloc(t_scene *scene, size_t size)
{
	void	*new;

	new = malloc (size);
	if (!new)
		return (print_scene_err(scene, F_MALL), NULL);
	if (!leaks_collector(new, &scene->heap))
		return (free(new), print_scene_err(scene, F_MALL), NULL);
	return (new);
}
