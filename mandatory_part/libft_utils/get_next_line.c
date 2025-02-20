/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:43:25 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/02/20 16:07:17 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Minirt.h"

char	*find_leak(char *all)
{
	if (all == NULL)
		return (NULL);
	free(all);
	return (NULL);
}

static int	check_new_line(char *all)
{
	if (all == NULL)
		return (0);
	while (*all != 0)
	{
		if (*all == 10)
			return (1);
		all++;
	}
	return (0);
}

char	*get_next_line(t_scene *scene, int fd)
{
	static char	*all;
	char		*part;
	int			i;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (all = find_leak(all));
	part = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (part == NULL)
		return (print_scene_err(scene, F_MALL), all = find_leak(all));
	i = 1;
	while (i != 0)
	{
		if (check_new_line(all) == 1)
			break ;
		i = read(fd, part, BUFFER_SIZE);
		if (i == -1)
			return (free(part), all = find_leak(all));
		part[i] = 0;
		all = mul_str(scene, all, part);
	}
	free(part);
	part = copy_line(scene, all);
	all = save_free(scene, all, part);
	return (part);
}
