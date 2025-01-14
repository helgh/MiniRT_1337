/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 15:56:32 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/01/13 17:23:09 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
#include <mlx.h>
# include <time.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>

# ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
#endif


# ifndef RADIAN
# define RADIAN 3.14159265359
#endif

# define OBJ_TO_WORLD 1
# define WORLD_TO_OBJ 2

# define TRANSLATING 1
# define SCALING 2
# define ROTATE_X 3
# define ROTATE_Y 4
# define ROTATE_Z 5
# define EPSILON 0.00001

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

# define ERR_A "  Invalid information for element 'A' in the scene\n"
# define ERR_A_1 "  Bad identifier information for element 'A' in the scene\n"
# define ERR_A_2 "  ambient lighting of element 'A' in the scene out of range [0.0,1.0]\n"
# define ERR_A_3 "  R.G.B for element 'A' in the scene out of range [0-255]\n"

/*------------------------- err Ambient lightning ---------------------------*/

# define ERR_C "  Invalid information for element 'A' in the scene\n"
# define ERR_C_1 "  Cannot convert string to vector for element 'C' in the scene\n"

typedef struct s_mlx
{
	int		bpp;
	int		size_line;
	int		endian;
	char	*pixels;
}				t_mlx;

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
}				t_tuple;

typedef struct s_sphere
{
	int		id;
	char	*type;
	double	diameter;
	double	radius;
	double	**trans;
	t_material	m;
	t_tuple	cord;
	t_color	color;
}				t_sphere;

typedef struct s_intersect
{
	int					nbr_sec;
	double				*point_sec;
	void				*object;
	struct s_intersect	*next;
}				t_intersect;

typedef struct s_ray
{
	t_tuple	origin_p;
	t_tuple	direction_v;
}				t_ray;

typedef struct s_light
{
	char	L;
	double	brightness;
	t_tuple	cord;
	t_color	color;
}				t_light;

typedef struct s_am_light
{
	char	A;
	bool	am_light;
	t_color	color;
}				t_am_light;

typedef struct s_camera
{
	char	C;
	int		FOV;
	t_tuple	cord;
	t_tuple	norm_vector;
}				t_camera;

char	*get_next_line(int fd);
char	*find_leak(char *all);
char	*mul_str(char *all, char *str);
char	*copy_line(char *str);
char	*save_free(char *str, char *p);
int		leng(char *str);
int		lengh(char **str);
char	**ft_split(char const *s, char c);
int		ft_atoi(const char *str);
int		ft_strcmp(char *s1, char *s2);
int		count_size(double **a);
double	**trans_mat(double **a, double det);
double	**inverse(double **a);
t_tuple	mult_mat_point(double **mat, t_tuple point);
t_tuple	mult_mat_vec(double **mat, t_tuple vec);
double	**translation(double x, double y, double z, double w);
double	**scaling(double x, double y, double z, double w);
double	**rotate_x(double angle);
double	**rotate_y(double angle);
double	**rotate_z(double angle);
double	degree_to_rad(double degree);
double	**shearing(double *arr);
t_tuple	position(t_ray *ray, double t);
t_tuple	addition(t_tuple start, t_tuple vec);
double	distance_point(t_tuple p1, t_tuple p2);
t_tuple	subtract(t_tuple ax1, t_tuple ax2);
bool	campare_mat(double **arr1, double **arr2);
double	ft_atof(char *str);
double	dot_product(t_tuple vec1, t_tuple vec2);
t_intersect	*intersect_sphere(t_sphere *sp, t_ray *ray);
t_ray	transform_ray(t_ray *ray, double **a);
double	**transform_sphere(t_sphere *sp, t_tuple *trans);
double	det(double **a);
double	cofactor(double **a, int row, int col);
double	**translation(double x, double y, double z, double w);
double	**identity_matrix(void);
double	**mult_matrix(double **a, double **b);
double	discriminant(t_sphere *sp, t_ray *ray);
double	magnitude(t_tuple tuple);
t_tuple	mult_by_scalar(t_tuple tuple, double scalar);
double	**transpose(double **a);
double	det_minor(double **a);
t_tuple	normal(t_tuple tuple);
void	free_sub_matrix(double **sub);
t_tuple	reflect(t_tuple in, t_tuple normal);
t_tuple	oposite(t_tuple tuple);
t_color	set_color(double r, double g, double b);
t_tuple	create_tuple(double x, double y, double z, double w);
t_tuple	cord_point_sec(t_ray cam, double t);
double	hit(t_intersect *sec);
t_tuple	normal_at(t_sphere sp, t_tuple point);
t_color	lighting(t_material m, t_light light, t_ray eye, t_tuple point, t_tuple vec);

typedef struct s_plane
{
	char	*pl;
	t_tuple	cord;
	t_tuple	norm_vector;
	t_color	color;
}				t_plane;

typedef struct s_cylinder
{
	char	*cy;
	bool	diameter;
	bool	height;
	t_tuple	*cord;
	t_tuple	*norm_vector;
	t_color	*color;
}				t_cylinder;

typedef struct s_scene
{
	t_am_light	*Ambient;
	t_camera	*camera;
	t_light		*light;
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylinder	*cylinder;
}				t_scene;


int	ft_strlen(char *str);

#endif