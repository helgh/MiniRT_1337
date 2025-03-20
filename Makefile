NAME = miniRT

NAME_BONUS = miniRT_bonus

CC = cc

C_FLAGS = -Wall -Wextra -Werror

MLX = -lmlx -framework OpenGL -framework Appkit

INC_UTILS = $(addprefix utils/, utils.h macros.h struct.h)

INC = $(addprefix mandatory_part/inc/, Minirt.h)

INC_BONUS = $(addprefix bonus_part/inc/, Minirt_bonus.h)

UTILS = $(addprefix utils/, error_free.c ft_malloc.c) \
		$(addprefix utils/libft_utils/, ft_atof.c ft_strlen.c ft_split.c ft_strcmp.c \
						get_next_line.c get_next_line_utils.c utils.c ft_strdup.c ft_memset.c \
						ft_strncmp.c) \
		$(addprefix utils/transform/, identity_matrix.c inverse.c \
						determinant.c mult_mat_point.c mult_matrix.c rot_utils.c \
						transformation.c transpose_matrix.c) \
		$(addprefix utils/math/, color_scal.c op_color.c op_tuple.c \
						tuple_scal.c op_vector.c set_get.c)

SOURCE = $(addprefix mandatory_part/, main.c) \
			$(addprefix mandatory_part/parse/, ab_light.c spot_light.c camera.c sphere.c plane.c \
						cylinder.c scene.c camera_utils.c utils_parse.c) \
			$(addprefix mandatory_part/render/, draw.c lighting.c mlx.c rays.c shadow.c) \
			$(addprefix mandatory_part/intersect/, hits.c intersect_cy.c \
						intersect_pl.c intersect_sp.c sect_world.c) \

SOURCE_BONUS = $(addprefix bonus_part/, main_bonus.c) \
			$(addprefix bonus_part/parse/, ab_light_bonus.c spot_light_bonus.c camera_bonus.c sphere_bonus.c plane_bonus.c \
						cylinder_bonus.c scene_bonus.c camera_utils_bonus.c utils_parse_bonus.c \
						checker_parse_bonus.c cone_bonus.c texture_parse_bonus.c) \
			$(addprefix bonus_part/render/, draw_bonus.c lighting_bonus.c normal_at.c mlx_bonus.c rays_bonus.c shadow_bonus.c \
						bump_map_sp_bonus.c bump_map_pl_bonus.c bump_map_cy_bonus.c checkerboard_bonus.c) \
			$(addprefix bonus_part/intersect/, hits_bonus.c intersect_cy_bonus.c \
						intersect_pl_bonus.c intersect_sp_bonus.c intersect_cone_bonus.c sect_world_bonus.c) \

RM			= rm -rf

OBJ_UTILS = $(UTILS:.c=.o)
OBJ_SRC = $(SOURCE:.c=.o) $(OBJ_UTILS)
OBJ_SRC_BONUS = $(SOURCE_BONUS:.c=.o) $(OBJ_UTILS)

all: $(NAME)

$(NAME): $(OBJ_SRC)
	$(CC) $(C_FLAGS) $(OBJ_SRC) $(MLX) -o $(NAME)

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJ_SRC_BONUS) $(OBJ_UTILS)
	$(CC) $(C_FLAGS) $(OBJ_SRC_BONUS) $(MLX) -o $(NAME_BONUS)

%.o: %.c $(INC_UTILS) $(INC_BONUS)
	$(CC) $(C_FLAGS) -c $< -o $@

%.o: %.c $(INC) $(INC_UTILS)
	$(CC) $(C_FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ_SRC) $(OBJ_SRC_BONUS)

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)

re: fclean all

re_bonus: fclean bonus
