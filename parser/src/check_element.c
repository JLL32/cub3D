/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_element.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jll32 <jll32@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 11:59:40 by jll32             #+#    #+#             */
/*   Updated: 2021/02/07 17:07:03 by jll32            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

void	check_element(t_config *config, char **element)
{
	if (ft_strcmp(element[0], "R") == 0)
		config->res = save_resolution(element);
	else if (ft_strcmp(element[0], "NO") == 0)
		config->tex.no = save_texture(element);
	else if (ft_strcmp(element[0], "SO") == 0)
		config->tex.so = save_texture(element);
	else if (ft_strcmp(element[0], "EA") == 0)
		config->tex.ea = save_texture(element);
	else if (ft_strcmp(element[0], "WE") == 0)
		config->tex.we = save_texture(element);
	else if (ft_strcmp(element[0], "S") == 0)
		config->tex.sp = save_texture(element);
	else if (ft_strcmp(element[0], "F") == 0)
		config->colors.floor = save_color(element);
	else if (ft_strcmp(element[0], "C") == 0)
		config->colors.ceiling = save_color(element);
	else
		ft_error(config->map, "Error\nInvalid elements");
}
