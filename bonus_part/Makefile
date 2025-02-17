NAME = miniRT

CC = cc

FLAGS = -Wall -Wextra -Werror -Ofast -fsanitize=address

MLX = -framework OpenGL -framework AppKit libmlx.a

INC = $(addprefix inc/, minirt.h macros.h struct.h) \

SOURCE = main.c error_free.c ft_malloc.c \
			$(addprefix libft_utils/, ft_atof.c ft_strlen.c ft_split.c ft_strcmp.c get_next_line.c get_next_line_utils.c utils.c) \
			$(addprefix parse/, ab_light.c spot_light.c camera.c sphere.c plane.c cylinder.c cone.c scene.c \
				camera_utils.c utils_parse.c) \
			$(addprefix render/, draw.c lighting.c mlx.c rays.c shadow.c) \
			$(addprefix intersect/, hits.c intersect_cy.c intersect_pl.c intersect_sp.c intersect_cone.c sect_world.c) \
			$(addprefix transform/, identity_matrix.c inverse.c mult_mat_point.c mult_matrix.c rot_utils.c \
				rotation.c transformation.c transpose_matrix.c) \
			$(addprefix math/, color_scal.c op_color.c op_tuple.c tuple_scal.c op_vector.c set_get.c) \
					
OBJ_SRC = $(SOURCE:.c=.o)

all: $(NAME)

$(NAME): $(OBJ_SRC)
	$(CC) $(FLAGS) $(OBJ_SRC) $(MLX) -o $(NAME)

%.o: %.c $(INC)
	$(CC) $(FLAGS) -c $<

clean:
	rm -f $(OBJ_SRC)

fclean: clean
	rm -f $(NAME)

re: fclean all
