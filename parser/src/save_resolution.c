/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_resolution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jll32 <jll32@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 19:58:03 by mobaz             #+#    #+#             */
/*   Updated: 2021/01/28 18:05:32 by jll32            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../cub.h"
#include "../parser.h"

static int		check_resolution_error(char **resolution, int i)
{
	int j;

	if (i > 2)
	{
		free_double_pointer(resolution);
		return (1);
	}
	j = 0;
	while (resolution[i][j])
	{
		if (resolution[i][j] < '0' || resolution[i][j] > '9')
		{
			free_double_pointer(resolution);
			return (1);
		}
		j++;
	}
	return (0);
}

t_resolution	save_resolution(char **resolution)
{
	// TODO: check for duplication assat
	t_resolution res;
	int i;

	i = 1;
	while (resolution[i])
	{
		if (check_resolution_error(resolution, i))
			ft_error(NULL, "Error\nResolution is invalid");
		if (i == 1)
		{
			res.width = ft_atoi(resolution[1]);
			res.width = res.width > 2560 ? 2560 : res.width;
			if (res.width < 0)
				ft_error(NULL, "Error\nIncorrect resolution");
		}
		else if (i == 2)
		{
			res.height = ft_atoi(resolution[2]);
			res.height = res.height > 1440 ? 1440 : res.height;
			if (res.height < 0)
				ft_error(NULL, "Error\nIncorrect resolution");
		}
		i++;
	}
	free_double_pointer(resolution);
	return (res);
}
