/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hach <ael-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 12:34:19 by ael-hach          #+#    #+#             */
/*   Updated: 2021/02/09 12:47:42 by ael-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "../libft/libft.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct	s_args
{
	char	*file;
	bool	is_save;
}				t_args;

typedef struct	s_resolution
{
	int	height;
	int	width;
}				t_resolution;

typedef struct	s_textures_paths
{
	char	*no;
	char	*so;
	char	*ea;
	char	*we;
	char	*sp;
}				t_textures_paths;

typedef struct	s_colors
{
	int	ceiling;
	int	floor;
}				t_colors;

typedef struct	s_player_pos
{
	double	pos_x;
	double	pos_y;
	char	dir;
}				t_player_pos;

typedef struct	s_coordinate
{
	double	x;
	double	y;
}				t_coordinate;

typedef struct	s_config
{
	char				**map;
	t_resolution		res;
	t_textures_paths	tex;
	t_colors			colors;
	t_player_pos		player;
	int					sprite_count;
	bool				is_save;
	t_coordinate		sprites[200];
}				t_config;

int		g_prev_len;
size_t	g_player_num;

t_config		parse_file(int argc, char **argv);
void			ft_error(char **map, char *error);
void			raise_map_error(char **map, int i, int j);
void			check_element(t_config *config, char **element);
t_resolution	save_resolution(char **resolution);
int				save_color(char **element);
char			*save_texture(char **texture);
char			**parse_map(t_config *config, int fd, char *line);
void			free_double_pointer(char **ptr);
void			map_error(t_config *config);
void			check_if_valid(t_config *config, int i, int j);
int				is_player(t_config *config, int i, int j);
int				is_sprite(t_config *config, int i, int j);
void			check_next_row(char **map, int i, int j, char c, int curr_len);
void			check_prev_row(char **map, int i, int j, char c, int curr_len);
int				free_memory(char **map, int status);
#endif
