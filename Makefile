NAME = cub3D
CC = clang
FLAGS = -Wall -Wextra -Werror -g -fsanitize=address
SRCS = src/main.c src/player.c
INCL = src/cub3D.h
MLX = ./mlx/Makefile

all: $(NAME)

$(NAME): $(SRCS) $(INCL) ./mlx/Makefile
	make -C ./mlx/
	CC $(SRCS) -L ./mlx/ -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean:
	rm cub3D

fclean:

re: clean all

.PHONY: all clean fclean re
