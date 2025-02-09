/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:37:23 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/02/09 17:48:40 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Minirt.h"

t_color	*_get_color(t_scene *scene, char *line)
{
	t_color		*color;
	t_tmp_heap	*tmp;

	tmp = scene->tmp_heap;
	tmp->split = ft_split(scene, line, ',');
	color = ft_malloc(scene, sizeof(t_color), false);
	color->r = ft_atof(tmp->split[0]) / 255.0;
	color->g = ft_atof(tmp->split[1]) / 255.0;
	color->b = ft_atof(tmp->split[2]) / 255.0;
	scene->tmp_heap->split = free_split(tmp->split);
	return (color);
}

void	check_color(t_scene *scene, char *str, char *err1, char *err2)
{
	t_tmp_heap	*tmp;
	int			i;
	int			s;
	int			len;

	s = -1;
	i = -1;
	tmp = scene->tmp_heap;
	tmp->split = ft_split(scene, str, ',');
	len = lengh(tmp->split);
	if (len != 3)
		print_scene_err(scene, err1);
	while (tmp->split[++s])
	{
		i = -1;
		while (ft_isdigit(tmp->split[s][++i]))
			;
		if (i == 0 || (tmp->split[s][i] && tmp->split[s][i] != 10))
			print_scene_err(scene, err1);
		if (ft_atof(tmp->split[s]) > 255.0)
			print_scene_err(scene, err2);
	}
	scene->tmp_heap->split = free_split(tmp->split);
}

int	valid_float(char *str, bool checker)
{
	int	i;
	int	flag;

	i = -1;
	flag = 0;
	if (checker == true && str[0] == 45)
		i++;
	while (str[++i])
	{
		if (!ft_isdigit(str[0]) && checker == false)
			return (1);
		if (!ft_isdigit(str[i]) && str[i] != 10)
			if (str[i] != 46 || flag == 1)
				return (1);
		if (str[i] == 46)
			flag = 1;
		if (str[i] == 46 && !ft_isdigit(str[i + 1]))
			return (1);
	}
	return (0);
}

t_tuple	*_get_normal_v(t_scene *scene, char *line, char *err1)
{
	t_tmp_heap	*tmp;
	t_tuple		*normal_v;
	double		cord[3];
	int			i;

	i = -1;
	tmp = scene->tmp_heap;
	tmp->split = ft_split(scene, line, ',');
	while (tmp->split[++i])
	{
		if (valid_float(tmp->split[i], true))
			print_scene_err(scene, err1);
		cord[i] = ft_atof(tmp->split[i]);
	}
	normal_v = ft_malloc(scene, sizeof(t_tuple), true);
	normal_v->x = cord[0];
	normal_v->y = cord[1];
	normal_v->z = cord[2];
	normal_v->w = 0.0;
	scene->tmp_heap->split = free_split(tmp->split);
	return (normal_v);
}

t_tuple	*_get_position(t_scene *scene, char *line, char *error)
{
	t_tuple		*pos;
	double		cord[3];
	t_tmp_heap	*tmp;
	int			i;

	i = -1;
	tmp = scene->tmp_heap;
	tmp->split = ft_split(scene, line, ',');
	while (tmp->split[++i])
	{
		if (valid_float(tmp->split[i], true))
			print_scene_err(scene, error);
		cord[i] = ft_atof(tmp->split[i]);
	}
	pos = ft_malloc(scene, sizeof(t_tuple), true);
	pos->x = cord[0];
	pos->y = cord[1];
	pos->z = cord[2];
	pos->w = 1.0;
	scene->tmp_heap->split = free_split(tmp->split);
	return (pos);
}
