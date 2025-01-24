/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:44:53 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/01/24 19:43:54 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minirt.h"

// t_tuple	reflect(t_tuple in, t_tuple normal)
// {
// 	double	n;

// 	n = 2 * dot_product(in, normal);
// 	return (op_tuple(in, op_tuple(normal, normal, 0, n), '-', 1));
// }

// count magnitude (lenght) of a vector //

// t_tuple	create_tuple(double x, double y, double z, double w)
// {
// 	t_tuple	tuple;

// 	tuple.x = x;
// 	tuple.y = y;
// 	tuple.z = z;
// 	tuple.w = w;
// 	return (tuple);
// }

// double	magnitude(t_tuple v)
// {
// 	return (sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2)));
// }

// // get a scalar value //
// // use of function when start intersecting rays with objects or when compute the shading on a surface //

double	dot_product(t_tuple vec1, t_tuple vec2)
{
	double	result;

	result = (vec1.x * vec2.x) + (vec1.y * vec2.y) + (vec1.z * vec2.z);
	return (result);
}

t_tuple	normal_at(t_sphere sp, t_tuple point)
{
	t_tuple	obj_vec;
	t_tuple	obj_p;
	t_tuple	world_vec;

	obj_p = mult_mat_point(sp.inv_trans, point);
	obj_vec = op_tuple(obj_p, create_tuple(0, 0, 0, 1), '-', 1);
	world_vec = mult_mat_point(sp.transpose_inv_matrix, obj_vec);
	world_vec.w = 0;
	return (normal(world_vec));
}

// function get oposite of some vector //

t_tuple	opposite(t_tuple tuple)
{
	t_tuple	new_tuple;

	new_tuple.x = -1 * tuple.x;
	new_tuple.y = -1 * tuple.y;
	new_tuple.z = -1 * tuple.z;
	new_tuple.w = tuple.w;
	return (new_tuple);
}

t_tuple	point_sec(t_ray cam, double t)
{
	return (op_tuple(cam.origin_p, op_tuple(cam.direction_v, cam.direction_v, 0, t), '+', 1));
}

t_color	set_color(double r, double g, double b)
{
	t_color	color;

	color.r = r;
	color.g = g;
	color.b = b;
	return (color);
}

double	choise_point(t_intersect *sec)
{
	t_intersect	tmp;

	tmp = *sec;
	if (sec->point_sec[0] < EPSILON)
		return (sec->t = sec->point_sec[1], sec->point_sec[1]);
	else if (sec->point_sec[1] < EPSILON)
		return (sec->t = sec->point_sec[0], sec->point_sec[0]);
	else if (sec->point_sec[0] < sec->point_sec[1])
		return (sec->t = sec->point_sec[0], sec->point_sec[0]);
	return (sec->t = sec->point_sec[1], sec->point_sec[1]);
}

t_intersect	*hit(t_intersect *sec)
{
	t_intersect	*tmp;
	t_intersect	*send;
	double point_sec;
	double		t;

	send = NULL;
	tmp = sec;
	t = -1;
	while (tmp)
	{
		point_sec = choise_point(tmp);
		if (t < EPSILON)
		{
			t = point_sec;
			send = tmp;
		}
		else if (point_sec < t)
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
	double min;
	double max;

	max = 1.0;
	min = 0.0;
    if (r < min) r = min; if (r > max) r = max;
    if (g < min) g = min; if (g > max) g = max;
    if (b < min) b = min; if (b > max) b = max;
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

static void	print_scene_err(t_scene *scene, char *msg)
{
	int	i;

	i = -1;
	write(2, "Error\n", 7);
	while (msg[++i])
		write(2, &msg[i], 1);
	free(scene->line);
	if (scene->fd >= 0)
		close(scene->fd);
	__ft_free(scene, ALL, EXIT_FAILURE);
}

t_color	_get_color(t_scene *scene, char *line)
{
	t_color	color;
	char	**tmp;

	tmp = ft_split(scene, line, ',');
	color.r = ft_atoi(tmp[0]);
	color.g = ft_atoi(tmp[1]);
	color.b = ft_atoi(tmp[2]);
	return (color);
}

void	check_color(t_scene *scene, char *str, char *err1, char *err2)
{
	char	**tmp;
	int		i;
	int		s;
	int		len;

	s = -1;
	i = -1;
	tmp = ft_split(scene, str, ',');
	len = lengh(tmp);
	if (len != 3 && len != 4)
		print_scene_err(scene, err1);
	while (tmp[++s])
	{
		i = -1;
		while (ft_isdigit(tmp[s][++i]))
			;
		if (tmp[s][i] && tmp[s][i] != 10)
			print_scene_err(scene, err1);
		if (ft_atoi(tmp[s]) > 255)
			print_scene_err(scene, err2);
	}
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

t_tuple	_get_normal_v(t_scene *scene, char *line, char *err1, char *err2)
{
	t_tuple	normal_v;
	double	cord[3];
	char	**tmp;
	int		i;

	i = -1;
	tmp = ft_split(scene, line, ',');
	while (tmp[++i])
	{
		if (valid_float(tmp[i], true))
			print_scene_err(scene, err1);
		cord[i] = ft_atof(tmp[i]);
		if (cord[i] < -1.0 || cord[i] > 1.0)
			print_scene_err(scene, err2);
	}
	normal_v.x = cord[0];
	normal_v.y = cord[1];
	normal_v.z = cord[2];
	normal_v.w = 0;
	return (normal_v);
}

t_tuple	_get_position(t_scene *scene, char *line, char *error)
{
	t_tuple	pos;
	double	cord[3];
	char	**tmp;
	int		i;

	i = -1;
	tmp = ft_split(scene, line, ',');
	while (tmp[++i])
	{
		if (valid_float(tmp[i], true))
			print_scene_err(scene, error);
		cord[i] = ft_atof(tmp[i]);
	}
	pos.x = cord[0];
	pos.y = cord[1];
	pos.z = cord[2];
	pos.w = 1;
	return (pos);
}

int		_get_fov(t_scene *scene, char *line)
{
	int		fov;
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
	fov = ft_atoi(line);
	if (fov < 0 || fov > 180)
		print_scene_err(scene, ERR_C_3);
	return (fov);
}

void	parse_cylinder(t_scene *scene, char **line)
{
	t_cylinder	*cylinder;
	t_tuple		pos;
	t_tuple		normal_v;
	t_color		color;
	int			len;

	len = lengh(line);
	if ((len != 6 && len != 7) || (len == 7 && strcmp(line[len - 1], "\n")))
		print_scene_err(scene, ERR_CY_1);
	pos = _get_position(scene, line[1], ERR_CY_1);
	normal_v = _get_normal_v(scene, line[2], ERR_CY_1, ERR_CY_2);
	if (valid_float(line[3], false) || valid_float(line[4], false))
		print_scene_err(scene, ERR_CY_1);
	check_color(scene, line[5], ERR_CY_1, ERR_CY_3);
	color = _get_color(scene, line[5]);
	cylinder = ft_malloc(scene, sizeof(t_cylinder), false);
	cylinder->pos = pos;
	cylinder->normal_v = normal_v;
	cylinder->diameter = ft_atof(line[3]);
	cylinder->height = ft_atof(line[4]);
	cylinder->color = color;
	cylinder->next = NULL;
	if (!scene->cylinder)
		scene->cylinder = cylinder;
	else
		add_to_list(scene, cylinder, CYLINDER);
}

void	parse_plane(t_scene *scene, char **line)
{
	t_plane	*plane;
	t_tuple	pos;
	t_tuple	normal_v;
	t_color	color;
	int		len;

	len = lengh(line);
	if (len != 4 && len != 5)
		print_scene_err(scene, ERR_PL_1);
	if (len == 5 && strcmp(line[len - 1], "\n"))
		print_scene_err(scene, ERR_PL_1);
	pos = _get_position(scene, line[1], ERR_PL_1);
	normal_v = _get_normal_v(scene, line[2], ERR_PL_1, ERR_PL_2);
	check_color(scene, line[3], ERR_PL_1, ERR_PL_3);
	color = _get_color(scene, line[3]);
	plane = ft_malloc(scene, sizeof(t_plane), false);
	plane->pos = pos;
	plane->normal_v = normal_v;
	plane->color = color;
	plane->next = NULL;
	if (!scene->plane)
		scene->plane = plane;
	else
		add_to_list(scene, plane, PLANE);
}

void	parse_sphere(t_scene *scene, char **line)
{
	t_sphere	*sphere;
	t_tuple		pos;
	t_color		color;
	int			len;

	len = lengh(line);
	if (len != 4 && len != 5)
		print_scene_err(scene, ERR_SP_1);
	if (len == 5 && strcmp(line[len - 1], "\n"))
		print_scene_err(scene, ERR_SP_1);
	pos = _get_position(scene, line[1], ERR_SP_1);
	if (valid_float(line[2], false))
		print_scene_err(scene, ERR_SP_1);
	check_color(scene, line[3], ERR_SP_1, ERR_SP_2);
	color = _get_color(scene, line[3]);
	sphere = ft_malloc(scene, sizeof(t_sphere), false);
	sphere->pos = pos;
	sphere->color = color;
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
	t_tuple		pos;
	double		ratio;
	int			len;

	len = lengh(line);
	if (scene->light)
		print_scene_err(scene, ERR_L);
	if (len != 3 && len != 4)
		print_scene_err(scene, ERR_L_1);
	if ((len == 4 && strcmp(line[len - 1], "\n")))
		print_scene_err(scene, ERR_L_1);
	pos = _get_position(scene, line[1], ERR_L_1);
	if (valid_float(line[2], false))
		print_scene_err(scene, ERR_L_1);
	ratio = ft_atof(line[2]);
	if (ratio < 0 || ratio > 1)
		print_scene_err(scene, ERR_L_2);
	light = ft_malloc(scene, sizeof(t_light), false);
	light->pos = pos;
	light->brightness = ratio;
	scene->light = light;
}

void	parse_camera(t_scene *scene, char **line)
{
	t_camera	*camera;
	t_tuple		pos;
	t_tuple		normal_v;
	int			len;
	int			fov;

	len = lengh(line);
	if (scene->camera)
		print_scene_err(scene, ERR_C);
	if (len != 4 && len != 5)
		print_scene_err(scene, ERR_C_1);
	if ((len == 5 && strcmp(line[len - 1], "\n")))
		print_scene_err(scene, ERR_C_1);
	pos = _get_position(scene, line[1], ERR_C_1);
	normal_v = _get_normal_v(scene, line[2], ERR_C_1, ERR_C_2);
	fov = _get_fov(scene, line[3]);
	camera = ft_malloc(scene, sizeof(t_camera), false);
	scene->camera = camera;
	scene->camera->pos = pos;
	scene->camera->normal_v = normal_v;
	scene->camera->FOV = fov;
}

void	parse_ab_light(t_scene *scene, char **line)
{
	t_am_light	*ab_light;
	t_color		color;
	double		n;
	int			len;

	len = lengh(line);
	if (scene->Ambient)
		print_scene_err(scene, ERR_A);
	if (len != 3 && len != 4)
		print_scene_err(scene, ERR_A_1);
	if ((len == 4 && strcmp(line[len - 1], "\n"))
			|| valid_float(line[1], false))
		print_scene_err(scene, ERR_A_1);
	n = ft_atof(line[1]);
	if (n > 1 || n < EPSILON)
		print_scene_err(scene, ERR_A_2);
	check_color(scene, line[2], ERR_A_1, ERR_A_3);
	color = _get_color(scene, line[2]);
	ab_light = ft_malloc(scene, sizeof(t_am_light), false);
	scene->Ambient = ab_light;
	ab_light->am_ratio = n;
	ab_light->color = _get_color(scene, line[2]);
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
	char	**spl;

	scene->fd = open(str, O_RDONLY);
	if (scene->fd < 0)
		print_scene_err(scene, OPEN_FILE_ERR);
	while (1)
	{
		scene->line = get_next_line(scene->fd);
		if (!scene->line)
			break ;
		if (strcmp(scene->line, "\n"))
		{
			spl = ft_split(scene, scene->line, 32);
			parse_element(scene, spl);
			__ft_free(scene, PART, 0);
			free(scene->line);
		}
		else
			free(scene->line);
	}
	close(scene->fd);
	scene->fd = -1;
}

t_scene	*init_struct(void)
{
	t_scene	*scene;

	scene = malloc(sizeof(t_scene));
	if (!scene)
		return (NULL);
	scene->fd = 0;
	scene->line = NULL;
	scene->Ambient = NULL;
	scene->camera = NULL;
	scene->light = NULL;
	scene->sphere = NULL;
	scene->plane = NULL;
	scene->cylinder = NULL;
	scene->heap = NULL;
	return (scene);
}

void	am_light_compenent(t_am_light *am_light)
{
	t_color		color;
	double		ratio;

	ratio = am_light->am_ratio;
	color = am_light->color;
	color = op_color(color, color, 0, ratio);
	color.r /= 255;
	color.g /= 255;
	color.b /= 255;
	am_light->f_color = color;
}

void	camera_compenent(t_scene *scene)
{
	t_camera	*camera;

	camera = scene->camera;
	camera->transform = view_transform(scene, camera->pos, camera->normal_v);
	camera->inv_transform = inverse(scene, camera->transform);
	camera->aspect = WIDTH / HEIGHT;
	if (camera->aspect >= 1)
	{
		camera->half_width = tan(camera->FOV / 2);
		camera->half_height = camera->half_width / camera->aspect;
	}
	else
	{
		camera->half_height = tan(camera->FOV / 2);
		camera->half_width = camera->half_height * camera->aspect;
	}
	camera->pixel_size = (camera->half_width * 2) / WIDTH;
}

void	light_compenent(t_light *light)
{
	t_color		color;
	double		ratio;

	light->color = set_color(255, 255, 255);
	ratio = light->brightness;
	color = light->color;
	color = op_color(color, color, 0, ratio);
	color.r /= 255;
	color.g /= 255;
	color.b /= 255;
	light->f_color = color;
}

void	sphere_compenent(t_scene *scene)
{
	t_sphere	*sphere;
	double		**tr;
	double		**scal;
	int			i;

	i = 0;
	sphere = scene->sphere;
	while (sphere)
	{
		sphere->id = i;
		sphere->radius = sphere->diameter / 2;
		tr = translation(scene, sphere->pos.x, sphere->pos.y, sphere->pos.z);
		scal = scaling(scene, sphere->radius, sphere->radius, sphere->radius);
		sphere->trans = mult_matrix(scene, tr, scal);
		__ft_free(scene, PART, 0);
		sphere->inv_trans = inverse(scene, sphere->trans);
		sphere->transpose_matrix = transpose(scene, sphere->trans);
		sphere->transpose_inv_matrix = transpose(scene, sphere->inv_trans);
		sphere = sphere->next;
		i++;
	}
}

void	parse_part(t_scene *scene, char *str)
{
	parse_scene(scene, str);
	important_element(scene);
	am_light_compenent(scene->Ambient);
	camera_compenent(scene);
	light_compenent(scene->light);
	sphere_compenent(scene);
	// plane_compenent(scene);
	// cylinder_compenent(scene);
}

t_intersect	*sec_spheres(t_scene *scene, t_ray *ray)
{
	t_intersect	*tmp;
	t_intersect	*send;
	t_sphere	*sp;

	sp = scene->sphere;
	if (!sp)
		return (NULL);
	send = NULL;
	while (sp)
	{
		tmp = intersect_sphere(scene, sp, ray);
		sp = sp->next;
		add_intersect(&send, tmp);
	}
	send = hit(send);
	return (send);
}

t_intersect	*intersect_world(t_scene *scene, t_ray *ray)
{
	t_intersect	*tmp;
	t_intersect	*send;

	send = NULL;
	tmp = NULL;
	while (1)
	{
		tmp = sec_spheres(scene, ray);
		if (tmp)
			add_intersect(&send, tmp);
		// tmp = sec_planes(scene, ray);
		// if (tmp.id != -1)
		// 	add_intersect(&send, &tmp);
		// tmp = sec_cylinders(scene, ray);
		// if (tmp.id != -1)
		// 	add_intersect(&send, &tmp);
		break ;
	}
	send = hit(send);
	return (send);
}

t_sphere	get_node(t_sphere *sp, int id)
{
	while (sp)
	{
		if (sp->id == id)
			break;
		sp = sp->next;
	}
	return (*sp);
}

t_color	lighting(t_light light, t_obj_draw obj, t_am_light am_light)
{
	t_color	ambient;
	t_color	difusse;
	t_tuple	light_v;
	double	light_normal;

	difusse = set_color(0, 0, 0);
	ambient = op_color(am_light.f_color, light.color, '*', 1);
	light_v = normal(op_tuple(light.pos, obj.position, '-', 1));
	light_normal = dot_product(light_v, obj.normal_v);
	if (obj.shadow)
		return (ambient);
	if (light_normal >= EPSILON)
		difusse = op_color(ambient, ambient, 0, light_normal);
	t_color result = op_color(ambient, difusse, '+', 1);
	return (result);
}

t_color	_get_sphere_color(t_scene *scene, t_intersect *sec, t_ray ray)
{
	t_sphere	sp;
	t_obj_draw	obj;
	t_intersect	*shad;
	t_ray		ray_shad;
	t_tuple		light;

	light = scene->light->pos;
	sp = get_node(scene->sphere, sec->id);
	obj.position = point_sec(ray, sec->t);
	obj.eye_v = opposite(ray.direction_v);
	obj.normal_v = normal_at(sp, obj.position);
	obj.inside = true;
	obj.shadow = false;
	if (dot_product(obj.normal_v, obj.eye_v) < EPSILON)
		obj.normal_v = opposite(obj.normal_v);
	else
		obj.inside = false;
	ray_shad.origin_p = obj.position;
	ray_shad.direction_v = normal(op_tuple(light, obj.position, '-', 1));
	shad = intersect_world(scene, &ray);
	if (shad && shad->t < magnitude(ray_shad.direction_v))
		obj.shadow = true;
	__ft_free(scene, PART, 0);
	return (lighting(*scene->light, obj, *scene->Ambient));
}

t_color	color_pixel(t_scene *scene, t_ray *ray)
{
	t_intersect	*inter;

	inter = intersect_world(scene, ray);
	if (!inter)
		return (scene->Ambient->f_color);
	else if (inter->type == SPHERE)
		return (_get_sphere_color(scene, inter, *ray));
	// else if (inter.type == PLANE)
	// 	return (_get_plane_color(scene, &inter));
	// _get_cylinder_color(scene, &inter);
	return (set_color(0, 0, 0));
}

void	draw(t_scene *scene)
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
			ray = ray_for_pixel(*camera, x, y);
			pix = (y * scene->mlx->s_line + x * (scene->mlx->bpp / 8));
			color = color_pixel(scene, &ray);
			col = rgb_to_hex(color.r, color.g, color.b);
			*(int *)(scene->mlx->pixels + pix) = col;
		}
	}
	
}

void	leaks(void)
{
	system("leaks -q miniRT");
}

void	render(t_scene *scene)
{
	t_mlx	*m;

	m = ft_malloc(scene, sizeof(t_mlx), false);
	scene->mlx = m;
	m->mlx = mlx_init();
	m->mlx_win = mlx_new_window(m->mlx, WIDTH, HEIGHT, "SCENE");
	m->mlx_img = mlx_new_image(m->mlx, 2200, 1200);
	m->pixels = mlx_get_data_addr(m->mlx_img, &m->bpp, &m->s_line, &m->endian);
	draw(scene);
	mlx_put_image_to_window(m->mlx, m->mlx_win, m->mlx_img, 0, 0);
	mlx_key_hook(m->mlx_win, &handle_event, &scene);
	mlx_loop(m->mlx);
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
		return (free(scene), 1);
	parse_part(scene, av[1]);
	render(scene);
	// printf("scene->ambient->am_ratio: %f\n", scene->Ambient->am_ratio);
	// printf("scene->ambient->color.r: %f\n", scene->Ambient->color.r);
	// printf("scene->ambient->color.g: %f\n", scene->Ambient->color.g);
	// printf("scene->ambient->color.b: %f\n", scene->Ambient->color.b);
	// printf("scene->camera->pos.x: %f\n", scene->camera->pos.x);
	// printf("scene->camera->pos.y: %f\n", scene->camera->pos.y);
	// printf("scene->camera->pos.z: %f\n", scene->camera->pos.z);
	// __ft_free(scene, ALL, 0);
}