NAME = cub3D
CC = clang
FLAGS = -Wall -Wextra -Werror -g -fsanitize=address
SRCS = main.c
INCL = cub3D.h
MLX = ./mlx/Makefile

all: $(NAME)

$(NAME): $(SRCS) $(INCL)
	make -C ./mlx/
	CC $(SRCS) -L ./mlx/ -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean:
	rm cub3D

fclean:

re: clean all

.PHONY: all clean fclean re
