/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:43:56 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/02/05 18:45:02 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include <mlx.h>
# include <time.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>

# ifndef BUFFER_SIZE
# define BUFFER_SIZE 40
#endif

# define WIDTH 1600
# define HEIGHT 900

# ifndef RADIAN
# define RADIAN 3.14159265358
#endif

# define ALL 1
# define PART 2

# define OBJ_TO_WORLD 1
# define WORLD_TO_OBJ 2

# define TRANSLATING 1
# define SCALING 2
# define ROTATE_X 3
# define ROTATE_Y 4
# define ROTATE_Z 5
# define EPSILON 0.00001

# define MULT 1
# define ADD 2
# define SUB 3
# define DIV 4
# define OPP 5

# define F_MALL "  Allocation failed\n"
# define NORMAL "  Vector not normalized\n"
# define BAD_TYPE "  Bad type of element in the scene\n"
# define REP_TYPE "  Elements defined by capital letter can only be declared once in the scene\n"
# define ERR_l "  Forget information for element 'l' in the scene\n"
# define ERR_pl "  Forget information for element 'pl' in the scene\n"
# define ERR_sp "  Forget information for element 'sp' in the scene\n"
# define ERR_cy "  Forget information for element 'cy' in the scene\n"
# define ERR_tr "  Forget information for element 'tr' in the scene\n"
# define ERR_sq "  Forget information for element 'sq' in the scene\n"

/*------------------------------ err window --------------------------------*/

# define ERR_HW "  Invalid information for element 'Hw' in the scene\n"
# define ERR_HW_1 "  Bad identifier information for element 'Hw' in the scene\n"
# define ERR_HW_2 "  information for element 'Hw' in the scene cannot be negative or zero\n"
# define ERR_HW_3 "  information for element 'Hw' in the scene cannot be over than 1200\n"

/*------------------------- err Ambient lightning ---------------------------*/

# define ERR_A "  Declared more then one element 'A' in the scene\n"
# define ERR_A_1 "  Bad identifier information for element 'A' in the scene\n"
# define ERR_A_2 "  ambient lighting of element 'A' in the scene out of range [0.0,1.0]\n"
# define ERR_A_3 "  R.G.B for element 'A' in the scene out of range [0-255]\n"

/*------------------------- err camera ---------------------------*/

# define ERR_C "  Declared more then one element 'C' in the scene\n"
# define ERR_C_1 "  Bad identifier information for element 'C' in the scene\n"
# define ERR_C_2 "  Normalized vector of element 'C' in the scene out of range [-1.0,1.0]\n"
# define ERR_C_3 "  FOV of element 'A' in the scene out of range [0-180]\n"
# define OPEN_FILE_ERR "  Failed to open file\n"

/*------------------------- err light ---------------------------*/

# define ERR_L "  Declared more then one element 'L' in the scene\n"
# define ERR_L_1 "  Bad identifier information for element 'L' in the scene\n"
# define ERR_L_2 "  Light brightness of element 'L' in the scene out of range [0.0,1.0]\n"

/*------------------------- err sphere ---------------------------*/

# define ERR_SP_1 "  Bad identifier information for element 'sp' in the scene\n"
# define ERR_SP_2 "  R.G.B for element 'sp' in the scene out of range [0-255]\n"

/*------------------------- err plane ---------------------------*/

# define ERR_PL_1 "  Bad identifier information for element 'pl' in the scene\n"
# define ERR_PL_2 "  Normalized vector of element 'pl' in the scene out of range [-1.0,1.0]\n"
# define ERR_PL_3 "  R.G.B for element 'pl' in the scene out of range [0-255]\n"

/*------------------------- err cylinder ---------------------------*/

# define ERR_CY_1 "  Bad identifier information for element 'cy' in the scene\n"
# define ERR_CY_2 "  Normalized vector of element 'cy' in the scene out of range [-1.0,1.0]\n"
# define ERR_CY_3 "  R.G.B for element 'cy' in the scene out of range [0-255]\n"


typedef struct s_mlx
{
	void	*mlx;
	void	*mlx_win;
	void	*mlx_img;
	int		bpp;
	int		s_line;
	int		endian;
	char	*pixels;
}				t_mlx;

typedef struct s_leaks
{
	void			*address;
	void			*_struct;
	bool			is_free;
	struct s_leaks	*next;
}					t_leaks;

typedef struct s_tmp_heap
{
	int		fd;
	char	*line;
	char	**spl;
	char	**split;
	double	**trans;
	double	**scal;
	double	**rot;
	double	**all;
}				t_tmp_heap;

typedef struct s_color
{
	double	r;
	double	g;
	double	b;
}				t_color;

typedef struct s_material
{
	double	ambient;
	double	diffuse;
	double	specular;
	double	shininess;
	t_color	color;
}				t_material;

typedef struct s_tuple
{
	double	x;
	double	y;
	double	z;
	double	w;
}			t_tuple;

typedef	enum e_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	LIGHT
}			t_type;

typedef struct s_sphere
{
	int				id;
	double			radius;
	double			**inv_trans;
	double			**transpose_inv_matrix;
	t_tuple			*pos;
	t_color			*color;
	struct s_sphere	*next;
}				t_sphere;

typedef struct s_intersect
{
	double				point_sec_1;
	double				point_sec_2;
	void				*object;
	double				t;
	int					type;
	int					id;
	struct s_intersect	*next;
}						t_intersect;

typedef struct s_ray
{
	t_tuple	origin_p;
	t_tuple	direction_v;
}			t_ray;

typedef struct s_light
{
	double	intensity;
	t_tuple	*pos;
	t_color	*f_color;
}			t_light;

typedef struct s_am_light
{
	double	am_ratio;
	t_color	*f_color;
}			t_am_light;

typedef struct s_camera
{
	double	FOV;
	double	aspect;
	double	half_width;
	double	half_height;
	double	pixel_size;
	double	**inv_transform;
	t_tuple	*pos;
	t_tuple	*normal_v;
}			t_camera;

typedef struct s_plane
{
	int				id;
	void			*object;
	double			**inv_trans;
	double			**transpose_inv_matrix;
	t_tuple			*pos;
	t_tuple			*normal_v;
	t_color			*color;
	struct s_plane	*next;
}			t_plane;

typedef struct s_cylinder
{
	int					id;
	void				*object;
	double				radius;
	double				**inv_trans;
	double				**transpose_inv_matrix;
	double				max_min;
	t_tuple				*pos;
	t_tuple				*normal_v;
	t_color				*color;
	struct s_cylinder	*next;
}			t_cylinder;

typedef struct s_scene
{
	t_tmp_heap	*tmp_heap;
	t_am_light	*Ambient;
	t_camera	*camera;
	t_light		*light;
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylinder	*cylinder;
	t_intersect	*sect;
	t_leaks		*heap;
}				t_scene;

typedef struct s_obj_draw
{
	int			render;
	bool		shadow;
	bool		inside;
	t_sphere	*sp;
	t_plane		*pl;
	t_cylinder	*cy;
	t_tuple		position;
	t_tuple		ov_p;
	t_tuple		eye_v;
	t_tuple		normal_v;
}				t_obj_draw;

// ----------------------------  mandatory  --------------------------------

void	print_scene_err(t_scene *scene, char *msg);
double	**free_matrix(double **matrix);
char	**free_split(char **split);
void	__ft_free(t_scene *scene, int flag, int exit_status);
char	**ft_split(t_scene *scene, char const *s, char c);
void	*ft_malloc(t_scene *scene, size_t size, bool flag);
int		ft_atoi(const char *str);
double	ft_atof(char *str);
char	*get_next_line(int fd);
char	*find_leak(char *all);
char	*save_free(char *str, char *p);
char	*copy_line(char *str);
char	*mul_str(char *all, char *str);
int		ft_isdigit(int c);
double	**view_transform(t_scene *scene, t_tuple from, t_tuple to, t_tuple up);
double	**identity_matrix(t_scene *scene);
double	**rotation(t_scene *scene, double angle, char axis);
double	**scaling(t_scene *scene, double x, double y, double z);
double	**translation(t_scene *scene, double x, double y, double z);
double	**mult_matrix(t_scene *scene, double **a, double **b);
double	**inverse(t_scene *scene, double **a);
double	**transpose(t_scene *scene, double **a);
t_tuple	mult_mat_point(double **mat, t_tuple point);
t_ray	ray_for_pixel(t_camera *camera, int pos_x, int pos_y);
t_intersect	*intersect_sphere(t_scene *scene, t_sphere *sp, t_ray *ray);
double	choise_point(t_intersect *sec);




//--------------------- op_vector ---------------------//

double	magnitude(t_tuple v);
t_tuple	normal(t_tuple tuple);
t_tuple	reflect(t_tuple in, t_tuple normal);
double	dot_product(t_tuple vec1, t_tuple vec2);
t_tuple	cross_product(t_tuple vec1, t_tuple vec2);

//--------------------- tuple_scal ---------------------//

t_tuple	tuple_scal(t_tuple tuple, double scal, int operator);

//--------------------- color_scal ---------------------//

t_color	color_scal(t_color col, double scal, int operator);

//--------------------- op_tuple ---------------------//

t_tuple	op_tuple(t_tuple tuple1, t_tuple tuple2, int operator);

//--------------------- op_color ---------------------//

t_color	op_color(t_color col1, t_color col2, char operator);

//--------------------- set_get ---------------------//

t_tuple	vector(double x, double y, double z);
t_tuple	point(double x, double y, double z);
t_color	color(double r, double g, double b);

t_tuple	point_sec(t_ray cam, double t);
t_ray	transform_ray(t_ray *ray, double **a);


t_intersect *intersect_plane(t_scene *scene, t_plane *pl, t_ray *ray);
t_intersect	*intersect_cylinder(t_scene *scene, t_cylinder *cy, t_ray *ray);

// ----------------------------  end_mandatory  --------------------------------
// char	*get_next_line(int fd);
// char	*find_leak(char *all);
// char	*mul_str(char *all, char *str);
// char	*copy_line(char *str);
// char	*save_free(char *str, char *p);
// int		leng(char *str);
// int		lengh(char **str);
// char	**ft_split(t_leaks *heap, char const *s, char c);
// int		ft_atoi(const char *str);
// int		ft_strcmp(char *s1, char *s2);
// int		count_size(double **a);
// double	**trans_mat(double **a, double det);
// double	**inverse(double **a);
// t_tuple	mult_mat_point(double **mat, t_tuple point);
// t_tuple	mult_mat_vec(double **mat, t_tuple vec);
// double	**translation(double x, double y, double z);
// double	**scaling(double x, double y, double z);
// double	**rotation(double angle, char axis);
// double	degree_to_rad(double degree);
// double	**shearing(double *arr);
// t_tuple	position(t_ray *ray, double t);
// t_tuple	addition(t_tuple start, t_tuple vec);
// double	distance_point(t_tuple p1, t_tuple p2);
// t_tuple	subtract(t_tuple ax1, t_tuple ax2);
// bool	campare_mat(double **arr1, double **arr2);
// double	ft_atof(char *str);
// double	dot_product(t_tuple vec1, t_tuple vec2);
// t_tuple	cross_product(t_tuple vec1, t_tuple vec2);
// t_intersect	*intersect_sphere(t_sphere *sp, t_ray *ray);
// t_ray	transform_ray(t_ray *ray, double **a);
// double	**transform_sphere(t_sphere *sp, t_tuple *trans);
// double	det(double **a);
// double	cofactor(double **a, int row, int col);
// double	**identity_matrix(void);
// double	**mult_matrix(double **a, double **b);
// double	discriminant(t_sphere *sp, t_ray *ray);
// double	magnitude(t_tuple tuple);
// t_tuple	op_tuple(t_tuple tuple1, t_tuple tuple2, char operator, double scalar);
// double	**transpose(double **a);
// t_tuple	normal(t_tuple tuple);
// void	free_sub_matrix(double **sub);
// t_tuple	reflect(t_tuple in, t_tuple normal);
// t_tuple	oposite(t_tuple tuple);
// t_color	set_color(double r, double g, double b);
// t_tuple	create_tuple(double x, double y, double z, double w);
// t_intersect	*hit(t_intersect *sec);
// t_tuple	normal_at(t_sphere sp, t_tuple point);
// t_color	lighting(t_material m, t_light light, t_tuple eye, t_tuple point, t_tuple vec);
// t_color	op_color(t_color col1, t_color col2, char operator, double scalar);
// t_color	rgb_to_hex(double r, double g, double b);
// t_color	check_col(t_color color);
// t_color	shad_hit(t_world *world, t_ray *ray);
// t_obj_draw	*get_obj(t_intersect *intersect, t_ray *ray);
// double	**view_transform(t_tuple from, t_tuple to, t_tuple up);
// t_camera	_camera(double fov, double width, double height);
// t_ray	ray_for_pixel(t_camera camera, double pos_x, double pos_y);
// int	ft_strlen(char *str);

#endif