/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minirt_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:43:56 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/03/17 21:22:22 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_BONUS_H
# define MINIRT_BONUS_H

# include "../../utils/utils.h"

// -------------------------  parse_scene  ----------------------------- //

void		parse_part(t_scene *scene, char *str);

// -------------------------  parse_ab_light  ----------------------------- //

void		parse_ab_light(t_scene *scene, char **line);

// -------------------------  parse_spot_light  ----------------------------- //

void		parse_light(t_scene *scene, char **line);
void		light_compenent(t_scene *scene);

// -------------------------  parse_camera  ----------------------------- //

void		parse_camera(t_scene *scene, char **line);
double		**view_transform(t_scene *scene, t_tuple from, \
					t_tuple to, t_tuple up);

// -------------------------  parse_sphere  ----------------------------- //

void		parse_sphere(t_scene *scene, char **line);
void		sphere_compenent(t_scene *scene);

// -------------------------  parse_plane  ----------------------------- //

void		parse_plane(t_scene *scene, char **line);
void		plane_compenent(t_scene *scene);

// -------------------------  parse_cylinder  ----------------------------- //

void		parse_cylinder(t_scene *scene, char **line);
void		cylinder_compenent(t_scene *scene);

// -------------------------  parse_cone  ----------------------------- //

void		parse_cone(t_scene *scene, char **line);
void		cone_compenent(t_scene *scene);

// -------------------------  parse_checker  ----------------------------- //

t_checker	*_get_checker(t_scene *scene, char **line, char *msg1, char *msg2);

// -------------------------  texture_parse  ----------------------------- //

char		*texture_parse(t_scene *scene, char **line, char *msg);
t_texture	*get_image_texture(t_scene *scene, char *path);

// -------------------------  utils_parse  ----------------------------- //

t_tuple		*_get_position(t_scene *scene, char *line, char *error);
t_tuple		*_get_normal_v(t_scene *scene, char *line, char *err1, char *err2);
int			valid_float(char *str, bool checker);
void		check_color(t_scene *scene, char *str, char *err1, char *err2);
t_color		*_get_color(t_scene *scene, char *line);
double		_check_get_number(t_scene *scene, char *line, char *msg);

// -------------------------  render  ----------------------------- //

void		render(t_scene *scene);
void		draw(t_scene *scene, t_mlx *mlx);
t_ray		ray_for_pixel(t_camera *camera, int pos_x, int pos_y);
t_color		lighting(t_scene *scene, t_obj_draw *obj, \
	t_am_light *am_light, t_color col);
t_tuple		normal_at(t_obj_draw obj, t_tuple poin, int op);
bool		check_shadow(t_scene *scene, t_obj_draw *obj, t_light light);
t_tuple		_bump_map_sphere(t_obj_draw obj, t_tuple obj_p);
t_tuple		_bump_map_plane(t_obj_draw obj, t_tuple poin);
t_tuple		_bump_map_cylinder(t_obj_draw obj, t_tuple poin);
t_color		_color_pl_or_checker(t_obj_draw *obj);
t_color		_color_sp_or_checker(t_obj_draw *obj);
t_color		_color_cy_or_checker(t_obj_draw *obj);
void		spherical_cord(t_obj_draw obj, t_tuple obj_p, \
	double *u, double *v);

// -------------------------  intersect  ----------------------------- //

void		intersect_world(t_scene *scene, t_ray *ray);
t_intersect	*intersect_sphere(t_scene *scene, t_sphere *sp, t_ray *ray);
t_intersect	*intersect_plane(t_scene *scene, t_plane *pl, t_ray *ray);
t_intersect	*intersect_cylinder(t_scene *scene, t_cylinder *cy, t_ray *ray);
t_intersect	*intersect_cone(t_scene *scene, t_cone *cone, t_ray *ray);
double		choise_point(t_intersect *sec);
t_intersect	*hit(t_intersect **secs, int index);

// -------------------------  rays  ----------------------------- //

t_ray		transform_ray(t_ray *ray, double **a);
t_ray		ray_for_pixel(t_camera *camera, int pos_x, int pos_y);
t_tuple		point_sec(t_ray cam, double t);
t_tuple		normal_at(t_obj_draw obj, t_tuple poin, int op);

#endif