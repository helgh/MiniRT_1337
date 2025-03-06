/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:06:07 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/03/06 18:15:01 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "macros.h"
# include "struct.h"

// -------------------------  libft_utils  ----------------------------- //

char		**ft_split(t_scene *scene, char const *s, char c);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strdup(t_scene *scene, const char *s1);
double		ft_atof(char *str);
int			ft_strlen(const char *str);
int			lengh(char **str);
int			ft_isdigit(int c);
double		degree_to_rad(double degree);
int			count_size(double **a);

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

// -------------------------  ft_malloc  ----------------------------- //

void		*ft_malloc(t_scene *scene, size_t size);

// -------------------------  error_free  ----------------------------- //

void		__ft_free(t_scene *scene, int exit_status);
void		print_scene_err(t_scene *scene, char *msg);
void		_ft_free_all(t_leaks *heap);
void		_ft_free_part(t_scene *scene);
char		**free_split(char **split);
double		**free_matrix(double **matrix);

// -------------------------  transform  ----------------------------- //

double		**identity_matrix(t_scene *scene);
double		**inverse(t_scene *scene, double **a);
double		det(t_scene *scene, double **a);
double		cofactor(t_scene *scene, double **a, int row, int col);
t_tuple		mult_mat_point(double **mat, t_tuple point);
double		**mult_matrix(t_scene *scene, double **a, double **b);
double		**_get_trans_rot(t_scene *scene, t_tuple target);
double		**rotation(t_scene *scene, double angle, char axis);
double		**scaling(t_scene *scene, double x, double y, double z);
double		**translation(t_scene *scene, double x, double y, double z);
double		**transpose(t_scene *scene, double **a);

// -------------------------  get_next_line  ----------------------------- //

char		*get_next_line(t_scene *scene, int fd);
char		*mul_str(t_scene *scene, char *all, char *str);
char		*copy_line(t_scene *scene, char *str);
char		*save_free(t_scene *scene, char *str, char *p);
char		*find_leak(char *all);

#endif
