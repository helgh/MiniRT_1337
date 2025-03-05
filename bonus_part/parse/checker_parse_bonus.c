/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_parse_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 22:26:32 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/03/05 18:13:44 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Minirt_bonus.h"

t_checker	*_get_checker(t_scene *scene, char **line, char *msg1, char *msg2)
{
	t_checker	*checker;
	int			len;

	len = lengh(line);
	if (!line[0] || !ft_strcmp(line[0], "\n") || len == 1)
		return (NULL);
	if (len < 3 || ft_strcmp(line[0], "checker"))
		print_scene_err(scene, msg1);
	checker = ft_malloc(scene, sizeof(t_checker));
	checker->ratio = _check_get_number(scene, line[1], msg1);
	check_color(scene, line[2], msg1, msg2);
	checker->color = _get_color(scene, line[2]);
	return (checker);
}
