NAME = miniRT

CC = cc

FLAGS = -Wall -Wextra -Werror -fsanitize=address

MLX = -framework OpenGL -framework AppKit libmlx.a

SOURCE = main.c ft_split.c ft_malloc.c get_next_line.c get_next_line_utils.c ft_atof.c ft_atoi.c ft_strcmp.c\
					
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
