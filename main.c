/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 17:10:53 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/10/21 02:06:14 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

void	print_scene_err(char *msg)
{
	int	i;

	i = -1;
	write(2, "Error\n", 7);
	while (msg[++i])
		write(2, &msg[i], 1);
}

void	exit_with_err(int status)
{
	if (status == 1)
	{
		write(2, "Invalid argument\n", strlen("Invalid argument\n"));
		exit(1);
	}
}

int	check_extention(const char *str)
{
	const char	*extention;
	int			i;
	int			fd;

	i = -1;
	extention = (const char *) ".rt";
	fd = open(str, O_RDONLY);
	if (!strncmp(str + (strlen(str) - 3), extention, (unsigned long) 3))
	{
		if (fd < 0)
			return (write(2, "No such file\n", 14), 1);
		return (close(fd), 0);
	}
	return (close(fd), write(2, "invalid extention\n", 19), 1);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	parse_window(char **spl, int len)
{
	int	i;
	int	s;

	if (len != 3)
		return (print_scene_err(ERR_HW), 1);
	if (spl[len - 1][ft_strlen(spl[len - 1]) - 1] == 10)
		spl[len - 1][ft_strlen(spl[len - 1]) - 1] = 0;
	s = 0;
	while (spl[++s])
	{
		i = -1;
		if (spl[s][0] == '-')
			i++;
		while (ft_isdigit(spl[s][++i]))
			;
		if (spl[s][i])
			return (print_scene_err(ERR_HW_1), 1);
	}
	if (ft_atoi(spl[1]) < 1 || ft_atoi(spl[2]) < 1)
		return (print_scene_err(ERR_HW_2), 1);
	if (ft_atoi(spl[1]) > 1200 || ft_atoi(spl[2]) > 1200)
		return (print_scene_err(ERR_HW_3), 1);
	return (0);
}

int		valid_float(char *str)
{
	int	i;
	int	flag;

	i = -1;
	flag = 0;
	while (str[++i])
	{
		if (!ft_isdigit(str[0]))
			return (1);
		if (!ft_isdigit(str[i]))
			if (str[i] != 46 || flag == 1)
				return (1);
		if (str[i] == 46)
			flag = 1;
	}
	return (0);
}

int		check_color(char *str)
{
	char	**tmp;
	int		i;
	int		s;
	int		len;

	s = -1;
	i = -1;
	tmp = ft_split(str, ',');
	len = lengh(tmp);
	if (len != 3)
		return (-1);
	if (tmp[len - 1][ft_strlen(tmp[len - 1]) - 1] == 10)
		tmp[len - 1][ft_strlen(tmp[len - 1]) - 1] = 0;
	while (tmp[++s])
	{
		i = -1;
		while (ft_isdigit(tmp[s][++i]))
			;
		if (tmp[s][i])
			return (-1);
		if (ft_atoi(tmp[s]) > 255)
			return (1);
	}
	return (0);
}

double	ft_atof(char *str)
{
	double	int_part;
	double	div_part;
	double	sign;
	int		i;

	int_part = 0.0;
	div_part = 0.0;
	sign = 1.0;
	while (ft_isdigit(*str))
		int_part = int_part * 10 + (*str++ - '0');
	i = -1;
	if (*str == '.' && *str++)
	{
		while (ft_isdigit(*str))
			div_part += (pow(10, i--) * (*str++ - '0'));
	}
	return (sign * (int_part + div_part));
}

int		parse_A(char **spl, int len)
{
	float	n;
	int		nb;

	if (len != 3)
		return (print_scene_err(ERR_A), 1);
	if (valid_float(spl[1]))
		return (print_scene_err(ERR_A_1), 1);
	n = ft_atof(spl[1]);
	if (n > 1 || n < 0)
		return (print_scene_err(ERR_A_2), 1);
	nb = check_color(spl[2]);
	if (nb)
	{
		if (nb == -1)
			return (print_scene_err(ERR_A_1), 1);
		else
			return (print_scene_err(ERR_A_3), 1);
	}
	return (0);
}

// int		parse_C(char **spl, int len)
// {
// 	if (len != 4)
// 		return (print_scene_err(ERR_C), 1);
// 	if (valid_vector(spl[1]) || valid_vector(spl[2]))
// 		return (print_scene_err(ERR_C_1), 1);
// 	return (0);
// }

int		check_element(t_scene *scene, char **spl, int len)
{
	(void) scene;
	if (!strcmp("Hw", spl[0]))
		return (parse_window(spl, len));
	else if (!strcmp("A", spl[0]))
		return (parse_A(spl, len));
	// else if (!strcmp("C", spl[0]))
	// 	return (parse_C(spl, len));
	// else if (!strcmp("l", spl[0]))
	// 	return (parse_l(spl));
	// else if (!strcmp("pl", spl[0]))
	// 	return (parse_pl(spl));
	// else if (!strcmp("sp", spl[0]))
	// 	return (parse_sp(spl));
	// else if (!strcmp("cy", spl[0]))
	// 	return (parse_cy(spl));
	// else if (!strcmp("tr", spl[0]))
	// 	return (parse_tr(spl));
	// else if (!strcmp("sq", spl[0]))
	// 	return (parse_sq(spl));
	return (-1);
}

int		lengh(char **str)
{
	int	i;

	i = -1;
	if (!str)
		return (0);
	while (str[++i])
		;
	return (i);
}

void	free_spl(char **spl)
{
	char	**tmp;
	int		i;

	tmp = spl;
	i = -1;
	while (spl && tmp[++i])
		free(tmp[i]);
	if (spl)
		free(spl);
}

void	parse_scene(t_scene *scene, char *str)
{
	char	*buff;
	char	**spl;
	int		fd;
	int		len;

	fd = open(str, O_RDONLY);
	if (fd < 0)
		exit(1);
	while (1)
	{
		buff = get_next_line(fd);
		if (!buff)
			break ;
		if (ft_strcmp(buff, "\n"))
		{
			spl = ft_split(buff, 32);
			len = lengh(spl);
			if (check_element(scene, spl, len) == -1)
				print_scene_err(BAD_TYPE);
			free_spl(spl);
		}
		else
			free(buff);
	}
}

int	main(int ac, char **av)
{
	t_scene	*scene;

	scene = NULL;
	if (ac != 2)
		exit_with_err(1);
	if (check_extention(av[1]))
		return (1);
	else
	{
		parse_scene(scene, av[1]);
	}
}
