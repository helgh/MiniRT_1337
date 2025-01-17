# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/18 23:24:19 by hael-ghd          #+#    #+#              #
#    Updated: 2025/01/16 18:33:43 by hael-ghd         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

CC = cc

FLAGS = -Wall -Wextra -Werror -g #-fsanitize=address

MLX = -framework OpenGL -framework AppKit libmlx.a

SOURCE = test.c addition.c campare_matrix.c cross_product.c determinant.c distance_point.c dot_product.c hit.c identity_matrix.c intersect.c magnitude.c \
			mult_by_scalar.c mult_mat_point.c mult_mat_vec.c mult_matrix.c normalization.c oposite.c point_or_vector.c position.c \
				rotation.c scaling.c shearing.c subtract.c transform.c translation.c transpose_mat.c degree_to_radian.c inverse.c \
					reflect.c lighting.c normal_at.c create_tuple.c operator_color.c #trans_test.c \
					
OBJ_SRC = $(SOURCE:.c=.o)

all: $(NAME)

$(NAME): $(OBJ_SRC)
	$(CC) $(FLAGS) $(OBJ_SRC) $(MLX) -o $(NAME)

%.o: %.c Minirt.h
	$(CC) $(FLAGS) -c $<

clean:
	rm -f $(OBJ_SRC)

fclean: clean
	rm -f $(NAME)

re: fclean all
