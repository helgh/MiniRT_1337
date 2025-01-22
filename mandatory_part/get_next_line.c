/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:43:25 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/01/22 17:36:55 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

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

char	*get_next_line(int fd)
{
	static char	*all;
	char		*part;
	int			i;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (all = find_leak(all));
	part = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (part == NULL)
		return (all = find_leak(all));
	i = 1;
	while (i != 0)
	{
		if (check_new_line(all) == 1)
			break ;
		i = read(fd, part, BUFFER_SIZE);
		if (i == -1)
			return (free(part), all = find_leak(all));
		part[i] = 0;
		all = mul_str(all, part);
	}
	free(part);
	part = copy_line(all);
	all = save_free(all, part);
	return (part);
}
