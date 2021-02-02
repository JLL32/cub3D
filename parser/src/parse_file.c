/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jll32 <jll32@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 12:16:49 by mobaz             #+#    #+#             */
/*   Updated: 2021/01/28 17:59:15 by jll32            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../cub.h"

#include "../parser.h"

static void	check_missing_element(t_config config)
{
	if (!config.res.height || !config.res.width)
		ft_error(config.map,"Error\nMissing resolution information");
	if (!config.colors.ceiling || !config.colors.floor)
		ft_error(config.map,"Error\nMissing color information");
}

static t_args	get_args(int c, char **v)
{
	char *ext;
	t_args args;

	args.is_save = false;
	if (c == 1 || c > 3)
		ft_error(NULL,"Error\ninvalid argument!");
	ext	= ft_strrchr(v[1], '.');
	if (!ext)
		ft_error(NULL,"Error\ninvalid argument!");
	else if (ft_strncmp(ext, ".cub", 5) != 0)
		ft_error(NULL,"Error\ninvalid argument!");
	args.file = v[1];
	if (c == 3)
	{
		if (ft_strncmp("--save", v[2], 7) == 0)
			args.is_save = true;
		else
			ft_error(NULL,"Error\ninvalid argument!");
	}
	return (args);
}

static int		get_elements(t_config *config ,int fd, char *line)
{
	char	**element;
	int		i;

	if (*line)
	{
		i = 0;
		while (line[i] == ' ')
			i++;
		if (line[i] == '1' || line[i] == '0')
		{
			config->map = parse_map(config, fd, line);
			return (1);
		}
		else
		{
			element = ft_split(line, ' ');
			if (!*element)
				ft_error(config->map,"Error\nInvalid file configuration");
			check_element(config, element);
		}
	}
	return (0);
}

t_config	parse_file(int argc, char **argv)
{
	int		fd;
	char	*line;
	int		status;
	t_config config;
	t_args args;

	args = get_args(argc, argv);
    // TODO: init config
	config.is_save = args.is_save;
	config.map = NULL;
	config.player = (t_player_pos){0, 0, '\0'};
	config.res = (t_resolution){0, 0};
	config.tex = (t_textures_paths){NULL, NULL, NULL, NULL, NULL};
	config.colors = (t_colors) {0, 0};
	config.sprite_count = 0;
	status = 0;
	fd = open(args.file, O_RDONLY);
	if (fd > 0)
	{
		while ((status = get_next_line(fd, &line)))
		{
			if (get_elements(&config, fd, line) == 1)
			{
				check_missing_element(config);
				return (config);
			}
			free(line);
		}
		if (status == 0)
			ft_error(config.map,"Error\nInvalid file configuration");
	}
	else
		ft_error(config.map,"Error\ninvalid file\n");

	return config;
}

// struct game{}
// void create_game(int argc, char **argv)
// {
// 	t_args args;
// 	args = get_args(argc, argv);
// 	parse_file(args.file);

// 	// draw();
// 	if (args.is_save)
// 		take_screenshot();
// }
