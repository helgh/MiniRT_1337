/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:43:56 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/02/14 19:22:11 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "macros.h"
# include "struct.h"

// -------------------------  libft_utils  ----------------------------- //

char		**ft_split(t_scene *scene, char const *s, char c);
int			ft_strcmp(char *s1, char *s2);
double		ft_atof(char *str);
int			ft_strlen(char *str);
int			lengh(char **str);
int			ft_isdigit(int c);
double		degree_to_rad(double degree);
int			count_size(double **a);

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

// -------------------------  utils_parse  ----------------------------- //

t_tuple		*_get_position(t_scene *scene, char *line, char *error);
t_tuple		*_get_normal_v(t_scene *scene, char *line, char *err1);
int			valid_float(char *str, bool checker);
void		check_color(t_scene *scene, char *str, char *err1, char *err2);
t_color		*_get_color(t_scene *scene, char *line);
double		_check_get_number(t_scene *scene, char *line, char *msg);

// -------------------------  render  ----------------------------- //

void		render(t_scene *scene);
void		draw(t_scene *scene, t_mlx *mlx);
t_ray		ray_for_pixel(t_camera *camera, int pos_x, int pos_y);
t_color		lighting(t_scene *scene, t_obj_draw *obj, t_am_light *am_light, t_color col);
bool		check_shadow(t_scene *scene, t_obj_draw *obj, t_light light);

// -------------------------  intersect  ----------------------------- //

void		intersect_world(t_scene *scene, t_ray *ray);
t_intersect	*intersect_sphere(t_scene *scene, t_sphere *sp, t_ray *ray);
t_intersect	*intersect_plane(t_scene *scene, t_plane *pl, t_ray *ray);
t_intersect	*intersect_cylinder(t_scene *scene, t_cylinder *cy, t_ray *ray);
t_intersect	*intersect_cone(t_scene *scene, t_cone *cone, t_ray *ray);
double		choise_point(t_intersect *sec);
t_intersect	*hit(t_intersect **secs, int index);

// -------------------------  math  ----------------------------- //

t_tuple		op_tuple(t_tuple tuple1, t_tuple tuple2, int operator);
t_tuple		tuple_scal(t_tuple tuple, double scal, int operator);
t_color		color_scal(t_color col, double scal, int operator);
t_color		op_color(t_color col1, t_color col2, char operator);
t_color		check_color_range(t_color color);
t_tuple		cross_product(t_tuple vec1, t_tuple vec2);
double		dot_product(t_tuple vec1, t_tuple vec2);
t_tuple		normal(t_tuple tuple);
double		magnitude(t_tuple v);
t_tuple		reflect(t_tuple in, t_tuple normal);

// -------------------------  set_get  ----------------------------- //

t_tuple		point(double x, double y, double z);
t_tuple		vector(double x, double y, double z);
t_color		color(double r, double g, double b);
t_sphere	*get_sphere(t_sphere *sp, int id);
t_plane		*get_plane(t_plane *pl, int id);
t_cylinder	*get_cylinder(t_cylinder *cy, int id);

// -------------------------  rays  ----------------------------- //

t_ray		transform_ray(t_ray *ray, double **a);
t_ray		ray_for_pixel(t_camera *camera, int pos_x, int pos_y);
t_tuple		point_sec(t_ray cam, double t);
t_tuple		normal_at(t_obj_draw obj, t_tuple poin, int op);

// -------------------------  ft_malloc  ----------------------------- //

void		*ft_malloc(t_scene *scene, size_t size, bool flag);

// -------------------------  error_free  ----------------------------- //

void		__ft_free(t_scene *scene, int flag, int exit_status);
void		print_scene_err(t_scene *scene, char *msg);
void		_ft_free_all(t_leaks *heap);
void		_ft_free_part(t_scene *scene);
char		**free_split(char **split);
double		**free_matrix(double **matrix);

// -------------------------  transform  ----------------------------- //

double		**identity_matrix(t_scene *scene);
double		**inverse(t_scene *scene, double **a);
t_tuple		mult_mat_point(double **mat, t_tuple point);
double		**mult_matrix(t_scene *scene, double **a, double **b);
double		**_get_trans_rot(t_scene *scene, t_tuple target);
double		**rotation(t_scene *scene, double angle, char axis);
double		**scaling(t_scene *scene, double x, double y, double z);
double		**translation(t_scene *scene, double x, double y, double z);
double		**transpose(t_scene *scene, double **a);

// -------------------------  get_next_line  ----------------------------- //

char		*get_next_line(int fd);
char		*mul_str(char *all, char *str);
char		*copy_line(char *str);
char		*save_free(char *str, char *p);
char		*find_leak(char *all);

#endif