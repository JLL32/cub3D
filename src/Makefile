NAME = cub3D
CC = clang
SRCS = main.c
INCL = cub3D.h
MLX = ./mlx/Makefile

all: $(NAME)

$(NAME): $(SRCS) $(INCL)
	make -C ./mlx/
	CC $(SRCS) -L ./mlx/ -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean:

fclean:

re:

.PHONY: all clean fclean re
