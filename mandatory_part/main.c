/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:44:53 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/02/03 20:11:01 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

double	degree_to_rad(double degree)
{
	double	value;

	value = (degree * (double) RADIAN) / 180.0;
	return (value);
}

// // get a scalar value //
// // use of function when start intersecting rays with objects or when compute the shading on a surface //

t_tuple	normal_at(t_obj_draw obj, t_tuple poin, int op)
{
	t_tuple	obj_p;
	t_tuple	world_vec;
	double	dis;

	if (op == SPHERE)
	{
		obj_p = mult_mat_point(obj.sp->inv_trans, poin);
		world_vec = mult_mat_point(obj.sp->transpose_inv_matrix, obj_p);
		world_vec.w = 0.0;
		return (normal(world_vec));
	}
	else if (op == PLANE)
		return (obj.normal_v);
	dis = pow (poin.x, 2) + pow(poin.z, 2);
	if (dis < 1 && poin.y >= (obj.cy->height / 2) - EPSILON)
		return (vector(0.0,1.0,0.0));
	else if (dis < 1 && poin.y <= (-(obj.cy->height) / 2) + EPSILON)
		return (vector(0.0,-1.0,0.0));
	return (vector(poin.x, 0.0, poin.z));
}

// function get oposite of some vector //

t_tuple	point_sec(t_ray cam, double t)
{
	t_tuple	direction;

	direction = tuple_scal(cam.direction_v, t, MULT);
	return (op_tuple(cam.origin_p, direction, ADD));
}

double	choise_point(t_intersect *sec)
{
	t_intersect	tmp;

	tmp = *sec;
	if (sec->point_sec_1 < EPSILON)
		return (sec->t = sec->point_sec_2, sec->point_sec_2);
	else if (sec->point_sec_2 < EPSILON)
		return (sec->t = sec->point_sec_1, sec->point_sec_1);
	else if (sec->point_sec_1 < sec->point_sec_2)
		return (sec->t = sec->point_sec_1, sec->point_sec_1);
	return (sec->t = sec->point_sec_2, sec->point_sec_2);
}

t_intersect	*hit(t_intersect *sec)
{
	t_intersect	*tmp;
	t_intersect	*send;
	double point_sec;
	double		t;

	send = NULL;
	tmp = sec;
	t = -1.0;
	while (tmp)
	{
		point_sec = tmp->t;
		if (t < 0.0 || point_sec < t)
		{
			t = point_sec;
			send = tmp;
		}
		tmp = tmp->next;
	}
	return (send);
}

void	add_intersect(t_intersect **head, t_intersect *new)
{
	t_intersect	*tmp;

	if (!new)
		return ;
	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

double rgb_to_hex(double r, double g, double b)
{
	r *= 255.0;
	g *= 255.0;
	b *= 255.0;
    return ((u_int64_t)r << 16 | (u_int64_t)g << 8 | (u_int64_t)b);
}

int	handle_event(int keycode, t_scene *scene)
{
	if (keycode == 53)
		__ft_free(scene, ALL, 0);
	return (0);
}

void	add_to_list(t_scene *scene, void *obj, int type)
{
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylinder	*cylinder;

	if (type == SPHERE)
	{
		sphere = scene->sphere;
		while (sphere->next)
			sphere = sphere->next;
		sphere->next = obj;
	}
	else if (type == PLANE)
	{
		plane = scene->plane;
		while (plane->next)
			plane = plane->next;
		plane->next = obj;
	}
	else if (type == CYLINDER)
	{
		cylinder = scene->cylinder;
		while (cylinder->next)
			cylinder = cylinder->next;
		cylinder->next = obj;
	}
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
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

static int	check_extention(const char *str)
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
		return (close(fd), EXIT_SUCCESS);
	}
	return (close(fd), write(2, "invalid extention\n", 19), EXIT_FAILURE);
}

void	print_scene_err(t_scene *scene, char *msg)
{
	int	i;

	i = -1;
	write(2, "Error\n", 7);
	while (msg[++i])
		write(2, &msg[i], 1);
	__ft_free(scene, ALL, EXIT_FAILURE);
}

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
	if (len != 3 && len != 4)
		print_scene_err(scene, err1);
	while (tmp->split[++s])
	{
		i = -1;
		while (ft_isdigit(tmp->split[s][++i]))
			;
		if (tmp->split[s][i] && tmp->split[s][i] != 10)
			print_scene_err(scene, err1);
		if (ft_atof(tmp->split[s]) > 255.0)
			print_scene_err(scene, err2);
	}
	scene->tmp_heap->split = free_split(tmp->split);
}

int		valid_float(char *str, bool checker)
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
	}
	return (0);
}

t_tuple	*_get_normal_v(t_scene *scene, char *line, char *err1)
{
	t_tmp_heap	*tmp;
	t_tuple		*normal_v;
	double		cord[3];
	int		i;

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
	int		i;

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

double	_get_fov(t_scene *scene, char *line)
{
	double	fov;
	int		i;

	i = -1;
	while (line[++i])
	{
		if (!ft_isdigit(line[i]))
		{
			if (line[i] == 10)
				break ;
			print_scene_err(scene, ERR_C_1);
		}
	}
	fov = ft_atof(line);
	if (fov < 0.0 || fov > 180.0)
		print_scene_err(scene, ERR_C_3);
	return (fov);
}

void	parse_cylinder(t_scene *scene, char **line)
{
	t_cylinder	*cylinder;
	int			len;

	len = lengh(line);
	if ((len != 6 && len != 7) || (len == 7 && strcmp(line[len - 1], "\n")))
		print_scene_err(scene, ERR_CY_1);
	if (valid_float(line[3], false) || valid_float(line[4], false))
		print_scene_err(scene, ERR_CY_1);
	cylinder = ft_malloc(scene, sizeof(t_cylinder), false);
	cylinder->pos = _get_position(scene, line[1], ERR_CY_1);
	cylinder->normal_v = _get_normal_v(scene, line[2], ERR_CY_1);
	check_color(scene, line[5], ERR_CY_1, ERR_CY_3);
	cylinder->color = _get_color(scene, line[5]);
	cylinder->diameter = ft_atof(line[3]);
	cylinder->height = ft_atof(line[4]);
	cylinder->next = NULL;
	if (!scene->cylinder)
		scene->cylinder = cylinder;
	else
		add_to_list(scene, cylinder, CYLINDER);
}

void	parse_plane(t_scene *scene, char **line)
{
	t_plane	*plane;
	int		len;

	len = lengh(line);
	if (len != 4 && len != 5)
		print_scene_err(scene, ERR_PL_1);
	if (len == 5 && strcmp(line[len - 1], "\n"))
		print_scene_err(scene, ERR_PL_1);
	plane = ft_malloc(scene, sizeof(t_plane), false);
	plane->pos = _get_position(scene, line[1], ERR_PL_1);
	plane->normal_v = _get_normal_v(scene, line[2], ERR_PL_1);
	check_color(scene, line[3], ERR_PL_1, ERR_PL_3);
	plane->color = _get_color(scene, line[3]);
	plane->next = NULL;
	if (!scene->plane)
		scene->plane = plane;
	else
		add_to_list(scene, plane, PLANE);
}

void	parse_sphere(t_scene *scene, char **line)
{
	t_sphere	*sphere;
	int			len;

	len = lengh(line);
	if (len != 4 && len != 5)
		print_scene_err(scene, ERR_SP_1);
	if (len == 5 && strcmp(line[len - 1], "\n"))
		print_scene_err(scene, ERR_SP_1);
	if (valid_float(line[2], false))
		print_scene_err(scene, ERR_SP_1);
	sphere = ft_malloc(scene, sizeof(t_sphere), false);
	sphere->pos = _get_position(scene, line[1], ERR_SP_1);
	check_color(scene, line[3], ERR_SP_1, ERR_SP_2);
	sphere->color = _get_color(scene, line[3]);
	sphere->diameter = ft_atof(line[2]);
	sphere->next = NULL;
	if (!scene->sphere)
		scene->sphere = sphere;
	else
		add_to_list(scene, sphere, SPHERE);
}

void	parse_light(t_scene *scene, char **line)
{
	t_light		*light;
	int			len;

	len = lengh(line);
	if (scene->light)
		print_scene_err(scene, ERR_L);
	if (len != 3 && len != 4)
		print_scene_err(scene, ERR_L_1);
	if ((len == 4 && strcmp(line[len - 1], "\n")))
		print_scene_err(scene, ERR_L_1);
	if (valid_float(line[2], false))
		print_scene_err(scene, ERR_L_1);
	light = ft_malloc(scene, sizeof(t_light), false);
	light->pos = _get_position(scene, line[1], ERR_L_1);
	light->intensity = ft_atof(line[2]);
	if (light->intensity < 0.0 || light->intensity > 1.0)
		print_scene_err(scene, ERR_L_2);
	scene->light = light;
}

void	parse_camera(t_scene *scene, char **line)
{
	t_camera	*camera;
	int			len;

	len = lengh(line);
	if (scene->camera)
		print_scene_err(scene, ERR_C);
	if (len != 4 && len != 5)
		print_scene_err(scene, ERR_C_1);
	if ((len == 5 && strcmp(line[len - 1], "\n")))
		print_scene_err(scene, ERR_C_1);
	camera = ft_malloc(scene, sizeof(t_camera), false);
	camera->FOV = degree_to_rad(_get_fov(scene, line[3]));
	camera->pos = _get_position(scene, line[1], ERR_C_1);
	camera->normal_v = _get_normal_v(scene, line[2], ERR_C_1);
	scene->camera = camera;
}

void	parse_ab_light(t_scene *scene, char **line)
{
	int			len;

	len = lengh(line);
	if (scene->Ambient)
		print_scene_err(scene, ERR_A);
	if (len != 3 && len != 4)
		print_scene_err(scene, ERR_A_1);
	if ((len == 4 && strcmp(line[len - 1], "\n"))
			|| valid_float(line[1], false))
		print_scene_err(scene, ERR_A_1);
	scene->Ambient = ft_malloc(scene, sizeof(t_am_light), false);
	scene->Ambient->am_ratio = ft_atof(line[1]);
	if (scene->Ambient->am_ratio > 1 || scene->Ambient->am_ratio < EPSILON)
		print_scene_err(scene, ERR_A_2);
	check_color(scene, line[2], ERR_A_1, ERR_A_3);
	scene->Ambient->color = _get_color(scene, line[2]);
}

void	important_element(t_scene *scene)
{
	if (!scene->Ambient)
		print_scene_err(scene, "  No ambient light found \n");
	if (!scene->camera)
		print_scene_err(scene, "  No camera found\n");
	if (!scene->light)
		print_scene_err(scene, "  No light found\n");
}

void	parse_element(t_scene *scene, char **line)
{
	if (!line[0])
		return ;
	if (!strcmp(line[0], "A"))
		parse_ab_light(scene, line);
	else if (!strcmp(line[0], "C"))
		parse_camera(scene, line);
	else if (!strcmp(line[0], "L"))
		parse_light(scene, line);
	else if (!strcmp(line[0], "sp"))
		parse_sphere(scene, line);
	else if (!strcmp(line[0], "pl"))
		parse_plane(scene, line);
	else if (!strcmp(line[0], "cy"))
		parse_cylinder(scene, line);
	else
		print_scene_err(scene, "  Invalid element\n");
}

void	parse_scene(t_scene *scene, char *str)
{
	scene->tmp_heap->fd = open(str, O_RDONLY);
	if (scene->tmp_heap->fd < 0)
		print_scene_err(scene, OPEN_FILE_ERR);
	while (1)
	{
		scene->tmp_heap->line = get_next_line(scene->tmp_heap->fd);
		if (!scene->tmp_heap->line)
			break ;
		if (strcmp(scene->tmp_heap->line, "\n"))
		{
			scene->tmp_heap->spl = ft_split(scene, scene->tmp_heap->line, 32);
			parse_element(scene, scene->tmp_heap->spl);
			scene->tmp_heap->spl = free_split(scene->tmp_heap->spl);
			free(scene->tmp_heap->line);
			scene->tmp_heap->line = NULL;
		}
		else
			free(scene->tmp_heap->line);
	}
	close(scene->tmp_heap->fd);
	scene->tmp_heap->fd = -1;
}

t_scene	*init_struct(void)
{
	t_scene	*scene;

	scene = malloc(sizeof(t_scene));
	if (!scene)
		return (NULL);
	scene->tmp_heap = malloc(sizeof(t_tmp_heap));
	if (!scene->tmp_heap)
		return (free(scene), NULL);
	scene->tmp_heap->fd = -1;
	scene->tmp_heap->line = NULL;
	scene->tmp_heap->spl = NULL;
	scene->tmp_heap->split = NULL;
	scene->tmp_heap->trans = NULL;
	scene->tmp_heap->scal = NULL;
	scene->tmp_heap->rot = NULL;
	scene->Ambient = NULL;
	scene->camera = NULL;
	scene->light = NULL;
	scene->sphere = NULL;
	scene->plane = NULL;
	scene->cylinder = NULL;
	scene->sect = NULL;
	scene->heap = NULL;
	return (scene);
}

void	am_light_compenent(t_scene *scene, t_am_light *am_light)
{
	t_color		color;
	double		ratio;

	am_light->f_color = ft_malloc(scene, sizeof(t_color), false);
	ratio = am_light->am_ratio;
	color = *am_light->color;
	color = color_scal(color, ratio, MULT);
	am_light->f_color->r = color.r;
	am_light->f_color->g = color.g;
	am_light->f_color->b = color.b;
}

void	camera_compenent(t_scene *scene)
{
	t_camera	*cam;
	t_tuple		up;

	up = vector(0.0, 1.0, 0.0);
	cam = scene->camera;
	if (fabs(magnitude(*cam->normal_v) - 1.0) >= EPSILON)
		*cam->normal_v = normal(*cam->normal_v);
	cam->transform = view_transform(scene, *cam->pos, *cam->normal_v, up);
	cam->inv_transform = inverse(scene, cam->transform);
	cam->aspect = (double) WIDTH / (double) HEIGHT;
	if (cam->aspect >= 1.0)
	{
		cam->half_width = tan(cam->FOV / 2.0);
		cam->half_height = cam->half_width / cam->aspect;
	}
	else
	{
		cam->half_height = tan(cam->FOV / 2.0);
		cam->half_width = cam->half_height * cam->aspect;
	}
	cam->pixel_size = (cam->half_width * 2.0) / (double) WIDTH;
}

void	light_compenent(t_scene *scene, t_light *light)
{
	double		ratio;

	light->f_color = ft_malloc(scene, sizeof(t_color), false);
	ratio = light->intensity;
	light->f_color->r = ratio;
	light->f_color->g = ratio;
	light->f_color->b = ratio;
}

void	sphere_compenent(t_scene *scene)
{
	t_sphere	*sphere;
	t_tmp_heap	*tmp;
	int			i;

	i = 0;
	tmp = scene->tmp_heap;
	sphere = scene->sphere;
	while (sphere)
	{
		sphere->id = i;
		sphere->radius = sphere->diameter / 2.0;
		tmp->trans = translation(scene, sphere->pos->x, sphere->pos->y, sphere->pos->z);
		tmp->scal = scaling(scene, sphere->radius, sphere->radius, sphere->radius);
		sphere->trans = mult_matrix(scene, tmp->trans, tmp->scal);
		tmp->trans = free_matrix(tmp->trans);
		tmp->scal = free_matrix(tmp->scal);
		sphere->inv_trans = inverse(scene, sphere->trans);
		sphere->transpose_matrix = transpose(scene, sphere->trans);
		sphere->transpose_inv_matrix = transpose(scene, sphere->inv_trans);
		sphere = sphere->next;
		i++;
	}
}

double	**get_rot(t_scene *scene, t_tmp_heap *tmp, double beta)
{
	int	i;
    int	j;

	i = -1;
    tmp->rot = identity_matrix(scene);
    while (++i < 4)
	{
        j  = -1;
        while (++j < 4)
		{
            tmp->trans[i][j] = (1- cos(beta)) * tmp->trans[i][j];
            tmp->rot[i][j] = tmp->rot[i][j] + tmp->trans[i][j] + tmp->scal[i][j];
        }
    }
	tmp->scal = free_matrix(tmp->scal);
	tmp->trans = free_matrix(tmp->trans);
	return (tmp->rot);
}

double **_get_trans_rot(t_scene *scene, t_tuple target)
{
	t_tmp_heap	tmp;
    t_tuple 	init;
	t_tuple 	new_vec;
	double 		beta;

	init = vector(0.0, 1.0, 0.0);
	new_vec = normal(cross_product(init, target));
    beta = acos(dot_product(init, target));
    tmp.scal = identity_matrix(scene);
    tmp.scal[0][1] = (-new_vec.z);
    tmp.scal[1][0] = new_vec.z;
    tmp.scal[1][2] = -new_vec.x;
    tmp.scal[2][1] = new_vec.x;
    tmp.scal[0][0] = 0;
    tmp.scal[1][1] = 0;
    tmp.scal[2][2] = 0;
    tmp.scal[3][3] = 0;
    tmp.trans  = mult_matrix(scene, tmp.scal, tmp.scal);
    tmp.scal[0][1] = sin(beta) * (-new_vec.z);
    tmp.scal[1][0] = sin(beta) * new_vec.z;
    tmp.scal[1][2] = sin(beta) * -new_vec.x;
    tmp.scal[2][1] = sin(beta) * new_vec.x;
    return (get_rot(scene, &tmp, beta));
}

void	plane_compenent(t_scene *scene)
{
	t_plane		*pl;
	t_tmp_heap	tmp;
	int		i;

	pl = scene->plane;
	i = 0;
	while (pl)
	{
		pl->id = i;
		if (fabs(magnitude(*pl->normal_v) - 1.0) >= EPSILON)
			*pl->normal_v = normal(*pl->normal_v);
		tmp.scal = _get_trans_rot(scene, *pl->normal_v);
		tmp.trans = translation(scene, pl->pos->x, pl->pos->y, pl->pos->z);
		pl->trans = mult_matrix(scene, tmp.trans, tmp.scal);
		tmp.scal = free_matrix(tmp.scal);
		tmp.trans = free_matrix(tmp.trans);
		pl->inv_trans = inverse(scene, pl->trans);
		pl->transpose_inv_matrix = transpose(scene, pl->inv_trans);
		pl = pl->next;
		i++;
	}
}

void	cylinder_compenent(t_scene *scene)
{
	t_cylinder	*cy;
	t_tmp_heap	tmp;
	int			i;

	cy = scene->cylinder;
	i = 0;
	while (cy)
	{
		cy->id = i;
		cy->radius = cy->diameter / 2.0;
		if (fabs(magnitude(*cy->normal_v) - 1.0) >= EPSILON)
			*cy->normal_v = normal(*cy->normal_v);
		tmp.scal = scaling(scene, cy->radius, cy->radius, cy->radius);
		tmp.trans = translation(scene, cy->pos->x, cy->pos->y, cy->pos->z);
		cy->trans = mult_matrix(scene, tmp.trans, tmp.scal);
		tmp.scal = free_matrix(tmp.scal);
		tmp.trans = free_matrix(tmp.trans);
		cy->inv_trans = inverse(scene, cy->trans);
		cy->transpose_inv_matrix = transpose(scene, cy->inv_trans);
		cy = cy->next;
		i++;
	}
}

void	parse_part(t_scene *scene, char *str)
{
	parse_scene(scene, str);
	important_element(scene);
	am_light_compenent(scene, scene->Ambient);
	camera_compenent(scene);
	light_compenent(scene, scene->light);
	sphere_compenent(scene);
	plane_compenent(scene);
	cylinder_compenent(scene);
}

void	sec_spheres(t_scene *scene, t_ray *ray)
{
	t_intersect	*tmp;
	t_sphere	*sp;

	sp = scene->sphere;
	while (sp)
	{
		tmp = intersect_sphere(scene, sp, ray);
		if (tmp)
			add_intersect(&scene->sect, tmp);
		sp = sp->next;
	}
}

void	sec_planes(t_scene *scene, t_ray *ray)
{
	t_intersect	*tmp;
	t_plane		*pl;

	pl = scene->plane;
	while (pl)
	{
		tmp = intersect_plane(scene, pl, ray);
		if (tmp)
			add_intersect(&scene->sect, tmp);
		pl = pl->next;
	}
}

void	sec_cylinders(t_scene *scene, t_ray *ray)
{
	t_intersect	*tmp;
	t_cylinder	*cy;

	cy = scene->cylinder;
	while (cy)
	{
		tmp = intersect_cylinder(scene, cy, ray);
		if (tmp)
			add_intersect(&scene->sect, tmp);
		cy = cy->next;
	}
}

void	intersect_world(t_scene *scene, t_ray *ray)
{
	scene->sect = NULL;
	if (scene->sphere)
		sec_spheres(scene, ray);
	if (scene->plane)
		sec_planes(scene, ray);
	if (scene->cylinder)
		sec_cylinders(scene, ray);
	if (scene->sect)
		scene->sect = hit(scene->sect);
}

t_cylinder	*get_cylinder(t_cylinder *cy, int id)
{
	while (cy)
	{
		if (cy->id == id)
			break;
		cy = cy->next;
	}
	return (cy);
}

t_plane	*get_plane(t_plane *pl, int id)
{
	while (pl)
	{
		if (pl->id == id)
			break;
		pl = pl->next;
	}
	return (pl);
}

t_sphere	*get_sphere(t_sphere *sp, int id)
{
	while (sp)
	{
		if (sp->id == id)
			break;
		sp = sp->next;
	}
	return (sp);
}

t_color	lighting(t_light *light, t_obj_draw *obj, t_am_light *am_light)
{
	t_color	ambient;
	t_color	difusse;
	t_color	object;
	t_tuple	light_v;
	double	light_normal;

	if (obj->render == SPHERE)
		object = *obj->sp->color;
	else if (obj->render == PLANE)
		object = *obj->pl->color;
	else
		object = *obj->cy->color;
	difusse = color(0.0, 0.0, 0.0);
	ambient = op_color(*am_light->f_color, object, MULT);
	light_v = normal(op_tuple(*light->pos, obj->position, SUB));
	light_normal = dot_product(light_v, obj->normal_v);
	if (obj->shadow == true)
		return (ambient);
	if (light_normal >= 0)
	{
		difusse = op_color(*light->f_color, object, MULT);
		difusse = color_scal(difusse, light_normal, MULT);
	}
	t_color result = op_color(ambient, difusse, ADD);
	return (result);
}

void	prepare_compute(t_scene *scene, t_obj_draw *obj, t_ray ray, int op)
{
	t_tuple		*light;

	light = scene->light->pos;
	if (op == SPHERE)
		obj->sp = get_sphere(scene->sphere, scene->sect->id);
	else if (op == PLANE)
	{
		obj->pl = get_plane(scene->plane, scene->sect->id);
		obj->normal_v = *obj->pl->normal_v;
	}
	else
		obj->cy = get_cylinder(scene->cylinder, scene->sect->id);
	obj->position = point_sec(ray, scene->sect->t);
	obj->eye_v = tuple_scal(ray.direction_v, -1, OPP);
	obj->normal_v = normal_at(*obj, obj->position, op);
	obj->inside = true;
	obj->shadow = false;
	if (dot_product(obj->normal_v, obj->eye_v) < 0.0)
		obj->normal_v = tuple_scal(obj->normal_v, 1, OPP);
	else
		obj->inside = false;
}

void	check_shadow(t_scene *scene, t_obj_draw *obj)
{
	t_ray		ray;
	t_tuple		v;
	t_tuple		direction;
	double		magn;

	v = op_tuple(*scene->light->pos, obj->position, SUB);
	magn = magnitude(v);
	direction = normal(v);
	ray.origin_p = obj->position;
	ray.direction_v = direction;
	intersect_world(scene, &ray);
	if (scene->sect && scene->sect->t < magn)
		obj->shadow = true;
}

t_color	_get_final_color(t_scene *scene, t_ray ray, int object)
{
	t_obj_draw	*obj;

	obj = ft_malloc(scene, sizeof(t_obj_draw), true);
	if (object == SPHERE)
		prepare_compute(scene, obj, ray, SPHERE);
	else if (object == PLANE)
		prepare_compute(scene, obj, ray, PLANE);
	else
		prepare_compute(scene, obj, ray, CYLINDER);
	check_shadow(scene, obj);
	obj->render = object;
	return (lighting(scene->light, obj, scene->Ambient));
}

t_color	color_pixel(t_scene *scene, t_ray *ray)
{
	intersect_world(scene, ray);
	if (!scene->sect)
		return (color(0.0, 0.0, 0.0));
	else if (scene->sect->type == SPHERE)
		return (_get_final_color(scene, *ray, SPHERE));
	else if (scene->sect->type == PLANE)
		return (_get_final_color(scene, *ray, PLANE));
	else if (scene->sect->type == CYLINDER)
		return (_get_final_color(scene, *ray, CYLINDER));
	return (color(0.0, 0.0, 0.0));
}

void	draw(t_scene *scene, t_mlx *mlx)
{
	t_camera	*camera;
	t_color		color;
	t_ray		ray;
	double		col;
	int			pix;
	int			x;
	int			y;

	camera = scene->camera;
	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			ray = ray_for_pixel(camera, x, y);
			pix = (y * mlx->s_line + x * (mlx->bpp / 8));
			color = color_pixel(scene, &ray);
			col = rgb_to_hex(color.r, color.g, color.b);
			*(int *)(mlx->pixels + pix) = col;
		}
	}
	
}

void	render(t_scene *scene)
{
	t_mlx	*m;

	m = malloc(sizeof(t_mlx));
	m->mlx = mlx_init();
	m->mlx_win = mlx_new_window(m->mlx, WIDTH, HEIGHT, "SCENE");
	m->mlx_img = mlx_new_image(m->mlx, WIDTH, HEIGHT);
	m->pixels = mlx_get_data_addr(m->mlx_img, &m->bpp, &m->s_line, &m->endian);
	draw(scene, m);
	mlx_put_image_to_window(m->mlx, m->mlx_win, m->mlx_img, 0, 0);
	mlx_key_hook(m->mlx_win, &handle_event, &scene);
	mlx_loop(m->mlx);
}

void	leaks(void)
{
	system("leaks -q miniRT");
}

int main(int ac, char **av)
{
	t_scene	*scene;

	atexit(leaks);
	scene = init_struct();
	if (!scene)
		return (write(2, "Allocation failed!\n", strlen("Allocation failed")), 1);
	if (ac != 2)
		return (free(scene), write(2, "Invalid argument\n", strlen("Invalid argument\n")), 1);
	if (check_extention(av[1]))
		return (free(scene->tmp_heap), free(scene), 1);
	parse_part(scene, av[1]);
	render(scene);
	free(scene);
	free(scene->tmp_heap);
	// __ft_free(scene, ALL, 0);
}