/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jll32 <jll32@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 12:48:09 by mobaz             #+#    #+#             */
/*   Updated: 2021/01/28 18:15:54 by jll32            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../cub.h"
#include "../parser.h"

static char	**ft_reallocate(char **old_map,int i)
{
	char	**new_map;
	int		j;

	j = 0;
	new_map = (char **)malloc((i+1) * sizeof(char *));
	while (j < i)
	{
		new_map[j] = old_map[j];
		j++;
	}
	new_map[j] = 0;
	free(old_map);
	return (new_map);
}

char	**parse_map(t_config *config, int fd, char *line)
{
	int i;
	int j;
	char **map;

	j = 1;
	i = 1;
	map = (char **)malloc((i+1) * sizeof(char *));
	map[0] = line;
	while (j)
	{
		j = get_next_line(fd, &line);
		map[i] = line;
		i += 1;
		map = ft_reallocate(map, i);
	}
	config->map = map;
	// g_num_rows = i;
	map_error(config);
	return (map);
}
