# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/18 23:24:19 by hael-ghd          #+#    #+#              #
#    Updated: 2024/10/20 23:48:28 by hael-ghd         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

CC = cc

FLAGS = -Wall -Wextra -Werror #-fsanitize=address

#MLX = -framework OpenGL -framework AppKit libmlx.a

SOURCE = addition.c campare_matrix.c cross_product.c determinant.c distance_point.c dot_product.c hit.c identity_matrix.c intersect.c magnitude.c \
			mult_by_scalar.c mult_mat_point.c mult_mat_vec.c mult_matrix.c normalization.c oposite.c point_or_vector.c position.c \
				rotate_x.c scaling.c shearing.c subtract.c transform.c translation.c transpose_mat.c degree_to_radian.c \

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
