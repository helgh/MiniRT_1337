NAME = miniRT

CC = cc

C_FLAGS = -Wall -Wextra -Werror

MLX = -lmlx -framework OpenGL -framework Appkit

INC = $(addprefix mandatory_part/inc/, Minirt.h macros.h struct.h)

INC_BONUS = $(addprefix bonus_part/inc/, Minirt_bonus.h macros_bonus.h struct_bonus.h)

SOURCE = $(addprefix mandatory_part/, main.c error_free.c ft_malloc.c) \
			$(addprefix mandatory_part/libft_utils/, ft_atof.c ft_strlen.c ft_split.c ft_strcmp.c \
						get_next_line.c get_next_line_utils.c utils.c) \
			$(addprefix mandatory_part/parse/, ab_light.c spot_light.c camera.c sphere.c plane.c \
						cylinder.c scene.c camera_utils.c utils_parse.c) \
			$(addprefix mandatory_part/render/, draw.c lighting.c mlx.c rays.c shadow.c) \
			$(addprefix mandatory_part/intersect/, hits.c intersect_cy.c \
						intersect_pl.c intersect_sp.c sect_world.c) \
			$(addprefix mandatory_part/transform/, identity_matrix.c inverse.c \
						determinant.c mult_mat_point.c mult_matrix.c rot_utils.c \
						rotation.c transformation.c transpose_matrix.c) \
			$(addprefix mandatory_part/math/, color_scal.c op_color.c op_tuple.c \
						tuple_scal.c op_vector.c set_get.c)

# SOURCE_BONUS = $(addprefix bonus_part/, main_bonus.c error_free_bonus.c ft_malloc_bonus.c) \
# 			$(addprefix bonus_part/libft_utils/, ft_atof_bonus.c ft_strlen_bonus.c ft_split_bonus.c ft_strcmp_bonus.c \
# 						get_next_line_bonus.c get_next_line_utils_bonus.c utils_bonus.c) \
# 			$(addprefix bonus_part/parse/, ab_light_bonus.c spot_light_bonus.c camera_bonus.c sphere_bonus.c plane_bonus.c \
# 						cylinder_bonus.c scene_bonus.c camera_utils_bonus.c utils_parse_bonus.c) \
# 			$(addprefix bonus_part/render/, draw_bonus.c lighting_bonus.c mlx_bonus.c rays_bonus.c shadow_bonus.c) \
# 			$(addprefix bonus_part/intersect/, hits_bonus.c intersect_cy_bonus.c \
# 						intersect_pl_bonus.c intersect_sp_bonus.c sect_world_bonus.c) \
# 			$(addprefix bonus_part/transform/, identity_matrix_bonus.c inverse_bonus.c \
# 						determinant_bonus.c mult_mat_point_bonus.c mult_matrix_bonus.c rot_utils_bonus.c \
# 						rotation_bonus.c transformation_bonus.c transpose_matrix_bonus.c) \
# 			$(addprefix bonus_part/math/, color_scal_bonus.c op_color_bonus.c op_tuple_bonus.c \
# 						tuple_scal_bonus.c op_vector_bonus.c set_get_bonus.c)


RM			= rm -rf

OBJ_SRC = $(SOURCE:.c=.o)

# OBJ_SRC_BONUS = $(SOURCE_BONUS:bonus.c=bonus.o)

all: $(NAME)

$(NAME): $(OBJ_SRC)
	$(CC) $(FLAG) $^ $(MLX) -o $@

# bonus: $(NAME) $(OBJ_SRC_BONUS)
# 	@echo "executable is done for bonus"

# %bonus.o: %bonus.c $(INC_BONUS)
# 	$(CC) $(C_FLAGS) -c -o $@ $<

%.o: %.c $(INC)
	$(CC) $(C_FLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJ_SRC) $(OBJ_SRC_BONUS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
