/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:43:56 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/03/08 23:10:26 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../../utils/utils.h"

// -------------------------  parse_scene  ----------------------------- //

void		parse_part(t_scene *scene, char *str);

// -------------------------  parse_ab_light  ----------------------------- //

void		parse_ab_light(t_scene *scene, char **line);

// -------------------------  parse_spot_light  ----------------------------- //

void		parse_light(t_scene *scene, char **line);

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

// -------------------------  utils_parse  ----------------------------- //

t_tuple		*_get_position(t_scene *scene, char *line, char *error);
t_tuple		*_get_normal_v(t_scene *scene, char *line, char *err1, char *err2);
int			valid_float(char *str, bool checker);
void		check_color(t_scene *scene, char *str, char *err1, char *err2);
t_color		*_get_color(t_scene *scene, char *line);

// -------------------------  render  ----------------------------- //

void		render(t_scene *scene);
void		draw(t_scene *scene, t_mlx *mlx);
t_ray		ray_for_pixel(t_camera *camera, int pos_x, int pos_y);
t_color		lighting(t_light *light, t_obj_draw *obj, t_am_light *am_light);
void		check_shadow(t_scene *scene, t_obj_draw *obj);

// -------------------------  intersect  ----------------------------- //

void		intersect_world(t_scene *scene, t_ray *ray);
t_intersect	*intersect_sphere(t_scene *scene, t_sphere *sp, t_ray *ray);
t_intersect	*intersect_plane(t_scene *scene, t_plane *pl, t_ray *ray);
t_intersect	*intersect_cylinder(t_scene *scene, t_cylinder *cy, t_ray *ray);
double		choise_point(t_intersect *sec);
t_intersect	*hit(t_intersect **secs, int index);

// -------------------------  rays  ----------------------------- //

t_ray		transform_ray(t_ray *ray, double **a);
t_ray		ray_for_pixel(t_camera *camera, int pos_x, int pos_y);
t_tuple		point_sec(t_ray cam, double t);
t_tuple		normal_at(t_obj_draw obj, t_tuple poin, int op);

#endif