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

FLAGS = -Wall -Wextra -Werror -fsanitize=address

MLX = -framework OpenGL -framework AppKit libmlx.a

SOURCE = main.c bonus.c get_next_line.c get_next_line_utils.c ft_split.c ft_atoi.c ft_strcmp.c

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
