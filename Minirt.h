/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 15:56:32 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/11/02 21:19:24 by hael-ghd         ###   ########.fr       */
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
# define BUFFER_SIZE 1
#endif

# ifndef RADIAN
# define RADIAN 3.14159265359
#endif

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

typedef struct s_intersect
{
	int		nbr_sec;
	double	*point_sec;	
}				t_intersect;

typedef struct s_axis
{
	double	x;
	double	y;
	double	z;
	double	w;
}				t_axis;
typedef struct s_ray
{
	t_axis	*origin_p;
	t_axis	*direction_v;
}				t_ray;

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
t_axis	*mult_mat_point(double **mat, t_axis *point);
t_axis	*mult_mat_vec(double **mat, t_axis *vec);
double	**translation(double x, double y, double z, double w);
double	**scaling(double x, double y, double z, double w);
double	**rotate_x(double angle);
double	**rotate_y(double angle);
double	**rotate_z(double angle);
double	degree_to_rad(double degree);
double	**shearing(t_axis *p1, t_axis *p2, t_axis *p3);
t_axis	*position(t_ray *ray, double t);
t_axis	*addition(t_axis *ax1, t_axis *ax2);
double	distance_point(t_axis *p1, t_axis *p2);
t_axis	*subtract(t_axis *ax1, t_axis *ax2);
bool	campare_mat(double **arr1, double **arr2);


typedef struct s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}				t_color;

typedef struct s_am_light
{
	char	A;
	bool	am_light;
	t_color	*color;
}				t_am_light;

typedef struct s_camera
{
	char	C;
	int		FOV;
	t_axis	*cord;
	t_axis	*norm_vector;
}				t_camera;

typedef struct s_light
{
	char	L;
	bool	brightness;
	t_axis	*cord;
	t_color	*color;
}				t_light;

typedef struct s_sphere
{
	char	*sp;
	bool	diameter;
	t_axis	*cord;
	t_color	*color;
}				t_sphere;

typedef struct s_plane
{
	char	*pl;
	t_axis	*cord;
	t_axis	*norm_vector;
	t_color	*color;
}				t_plane;

typedef struct s_cylinder
{
	char	*cy;
	bool	diameter;
	bool	height;
	t_axis	*cord;
	t_axis	*norm_vector;
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