/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:43:40 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/03/05 16:13:16 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils.h"

static int	leng(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (*(str + i) != 0)
		i++;
	return (i);
}

char	*save_free(t_scene *scene, char *str, char *p)
{
	int		i;
	int		c;
	char	*s;
	char	*part;

	c = 0;
	if (str == NULL || p == NULL)
		return (NULL);
	i = leng(str);
	while (*(str + c) != 0 && *(str + c) != 10)
		c++;
	if (*(str + c) == 10)
		c++;
	s = malloc(sizeof(char) * ((i - c) + 1));
	if (s == NULL)
		return (print_scene_err(scene, F_MALL), str = find_leak(str));
	part = s;
	while (c++ < i)
		*(part)++ = *(str + c - 1);
	*part = 0;
	if (*s == 0)
		return (str = find_leak(str), free(s), NULL);
	free(str);
	return (s);
}

char	*copy_line(t_scene *scene, char *str)
{
	char	*s;
	char	*p;
	int		i;

	i = 0;
	if (str == NULL)
		return (NULL);
	while (*(str + i) != 0 && *(str + i) != 10)
		i++;
	if (*(str + i) == 10)
		i++;
	s = malloc(sizeof(char) * (i + 1));
	if (s == NULL)
		return (print_scene_err(scene, F_MALL), str = find_leak(str));
	p = s;
	while (i-- > 0)
		*(s)++ = *(str)++;
	*s = 0;
	return (p);
}

char	*mul_str(t_scene *scene, char *all, char *str)
{
	char	*s;
	char	*al;
	char	*part;
	int		i;

	i = leng(all);
	if (all == NULL && *str == 0)
		return (NULL);
	s = malloc(sizeof(char) * (i + leng(str) + 1));
	if (s == NULL)
		return (print_scene_err(scene, F_MALL), all = find_leak(all));
	part = s;
	al = all;
	if (i != 0)
	{
		while (*al != 0)
			*(s)++ = *(al)++;
	}
	while (*str != 0)
		*(s)++ = *(str)++;
	*s = 0;
	return (all = find_leak(all), part);
}
