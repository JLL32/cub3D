FLAGS = -Wall -Wextra -Werror
DFLAGS = -g -g3 -fsanitize=address
CC = gcc
SRCS =	src/get_next_line.c \
		src/get_next_line_utils.c \
		src/parse_map.c \
		src/save_color.c \
		src/check_element.c \
		src/save_resolution.c \
		src/parse_file.c \
		src/save_texture.c \
		src/save_player.c \
		src/free_memory.c \
		src/ft_error.c \
		src/map_error.c \
		src/map_error_utils.c \
		src/save_sprite.c
NAME = libparser.a

all: $(NAME)

$(NAME): $(SRCS) ./Makefile
	gcc $(FLAGS) -g $(SRCS) -c
	ar rc $(NAME) *.o

clean:
	rm -rf *.o

fclean: clean
	rm $(NAME)

re: fclean all

test: all
	gcc $(FLAGS) -g main.c cub-parser.a libft/libft.a -o parser

.PHONY: all clean fclean test
