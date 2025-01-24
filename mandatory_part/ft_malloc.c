/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:47:01 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/01/24 14:59:16 by hael-ghd         ###   ########.fr       */
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

static void	_ft_free_part(t_leaks **heap)
{
	t_leaks	*tmp;
	t_leaks	*prev;

	tmp = *heap;
	prev = NULL;
	while (tmp && tmp->is_free == false)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (!prev)
	{
		while (tmp && tmp->is_free == true)
		{
			prev = tmp->next;
			free (tmp->address);
			free (tmp->_struct);
			tmp = prev;
		}
		*heap = prev;
	}
	else
	{
		while (tmp && tmp->is_free == true)
		{
			prev->next = tmp->next;
			free (tmp->address);
			free (tmp->_struct);
			tmp = prev->next;
		}
	}
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
	t_leaks	*tmp;
	t_leaks	*new;

	new = malloc(sizeof(t_leaks));
	if (!new)
		return (NULL);
	new->address = for_leaks;
	new->_struct = new;
	new->next = NULL;
	new->is_free = flag;
	if (!*heap)
		return (*heap = new);
	tmp = *heap;
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
		free(scene);
		exit(exit_status);
	}
	else
		_ft_free_part(&scene->heap);
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
