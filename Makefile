C_FLAGS		= -Ofast -Wall -Wextra -Werror
HEADER		= $(shell find ./mandatory_part -name '*.h')
SRCS		= $(addprefix mandatory_part/, main.c error_free.c ft_malloc.c) \
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

BUILD		= mandatory_part/build
MLX			= -lmlx -framework OpenGL -framework AppKit
OBJS		= $(addprefix $(BUILD)/, $(SRCS:.c=.o))
NAME		= miniRT
RM			= rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(C_FLAGS) $^ $(MLX) -o $@

$(BUILD)/%.o: %.c $(HEADER)
	@mkdir -p $(dir $@)
	$(CC) $(C_FLAGS) -c -o $@ $<

clean:
	@$(RM) $(OBJS) $(BUILD)

fclean: clean
	@$(RM) $(NAME)

re: fclean all
