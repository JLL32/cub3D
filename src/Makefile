NAME = cub3D
CC = clang
SRCS = main.c
INCL = cub3D.h

all: $(NAME)

$(NAME): $(SRCS) $(INCL)
	CC $(SRCS) -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean:

fclean:

re:

.PHONY: all clean fclean re
