NAME = cub3D
CC = clang
FLAGS = -Wall -Wextra -Werror
DFLAGS = -g -fsanitize=address
SRCS = src/main.c \
		src/player.c \
		src/player2.c \
		src/game.c \
		src/game2.c \
		src/draw.c \
		src/draw_walls.c \
		src/draw_sprites.c \
		src/raycasting.c \
		src/raycasting2.c \
		src/sprite.c \
		src/sort_sprites.c \
		src/screenshot.c
INCL = src/cub.h
MLX = ./mlx/Makefile

all: $(NAME)

$(NAME): $(SRCS) ./mlx/Makefile ./Makefile
	make -C ./mlx/
	make -C ./libft/
	make -C ./parser/
	CC $(SRCS) -L ./libft -lft -L ./parser -lparser -L ./mlx/ -lmlx -framework OpenGL -framework AppKit -o $(NAME)

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

bonus: all

.PHONY: all clean fclean re bonus
