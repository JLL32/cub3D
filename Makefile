NAME = cub3D
CC = clang
FLAGS = -Wall -Wextra -Werror
DFLAGS = -g -fsanitize=address
SRCS = src/main.c src/player.c
INCL = src/cub3D.h
MLX = ./mlx/Makefile

all: $(NAME)

$(NAME): $(SRCS) ./mlx/Makefile ./Makefile
	make -C ./mlx/
	make -C ./libft/
	make -C ./parser/
	CC $(DFLAGS) $(SRCS) -L ./libft -lft -L ./parser -lparser -L ./mlx/ -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean:
	make -C ./mlx/ clean
	make -C ./parser/ clean
	make -C ./libft/ clean

fclean:
	make -C ./mlx/ clean
	make -C ./parser/ fclean
	make -C ./libft/ fclean
	rm cub3D

re: fclean all

.PHONY: all clean fclean re
