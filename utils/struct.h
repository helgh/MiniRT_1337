/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:54:06 by hael-ghd          #+#    #+#             */
/*   Updated: 2025/04/12 22:07:38 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_mlx
{
	void	*mlx;
	void	*mlx_win;
	void	*mlx_img;
	int		bpp;
	int		s_line;
	int		endian;
	char	*pixels;
	bool	init;
}				t_mlx;

typedef struct s_leaks
{
	void			*address;
	void			*_struct;
	bool			is_free;
	struct s_leaks	*next;
}					t_leaks;

typedef struct s_texture
{
	void			*texture;
	int				bpp;
	int				s_line;
	int				endian;
	char			*data;
	int				w;
	int				h;
}				t_texture;	

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

typedef struct s_tuple
{
	double	x;
	double	y;
	double	z;
	double	w;
}			t_tuple;

typedef struct s_color
{
	double	r;
	double	g;
	double	b;
}				t_color;

typedef struct s_checker
{
	bool	exist;
	double	ratio;
	t_color	color;
}				t_checker;

typedef enum e_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	CONE,
	LIGHT
}			t_type;

typedef struct s_ray
{
	t_tuple	origin_p;
	t_tuple	direction_v;
}			t_ray;

typedef struct s_am_light
{
	double	am_ratio;
	t_color	f_color;
}			t_am_light;

typedef struct s_light
{
	double			intensity;
	t_tuple			pos;
	t_color			f_color;
	struct s_light	*next;
}			t_light;

typedef struct s_camera
{
	double	fov;
	double	half_width;
	double	half_height;
	double	pixel_size;
	double	**inv_transform;
	t_tuple	pos;
	t_tuple	normal_v;
}			t_camera;

typedef struct s_sphere
{
	double			radius;
	double			**inv_trans;
	double			**transpose_inv_matrix;
	char			*path;
	t_checker		checker;
	t_texture		text;
	t_tuple			pos;
	t_color			color;
	struct s_sphere	*next;
}				t_sphere;

typedef struct s_plane
{
	double			**inv_trans;
	double			**transpose_inv_matrix;
	char			*path;
	t_checker		checker;
	t_texture		text;
	t_tuple			pos;
	t_tuple			normal_v;
	t_color			color;
	struct s_plane	*next;
}			t_plane;

typedef struct s_cylinder
{
	double				radius;
	double				**inv_trans;
	double				**transpose_inv_matrix;
	double				max_min;
	char				*path;
	t_checker			checker;
	t_texture			text;
	t_tuple				pos;
	t_tuple				normal_v;
	t_color				color;
	struct s_cylinder	*next;
}			t_cylinder;

typedef struct s_cone
{
	double				radius;
	double				**inv_trans;
	double				**transpose_inv_matrix;
	double				max_min;
	t_tuple				pos;
	t_tuple				normal_v;
	t_color				color;
	struct s_cone		*next;
}						t_cone;

typedef struct s_intersect
{
	double				point_sec_1;
	double				point_sec_2;
	bool				exist;
	double				t;
	int					type;
	t_sphere			sp;
	t_plane				pl;
	t_cylinder			cy;
	t_cone				cone;
}						t_intersect;

typedef struct s_obj_draw
{
	bool		shadow;
	t_sphere	*sp;
	t_plane		*pl;
	t_cylinder	*cy;
	t_cone		*cone;
	t_tuple		position;
	t_tuple		ov_p;
	t_tuple		eye_v;
	t_tuple		normal_v;
}				t_obj_draw;

typedef struct s_scene
{
	t_tmp_heap	*tmp_heap;
	t_am_light	*ambient;
	t_camera	*camera;
	t_light		*light;
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylinder	*cylinder;
	t_cone		*cone;
	t_intersect	sect;
	t_leaks		*heap;
	t_mlx		mlx;
}				t_scene;

#endif
