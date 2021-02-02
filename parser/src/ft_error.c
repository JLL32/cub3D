/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobaz <mobaz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 13:29:30 by mobaz             #+#    #+#             */
/*   Updated: 2020/11/11 12:59:13 by mobaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../cub.h"
#include "../parser.h"

void	ft_map_error(char **map, int i, int j)
{
	char *row;
	char *col;

	row = ft_itoa(i);
	col = ft_itoa(j);
	ft_putstr_fd("Error\nMap error in row ", 2);
	ft_putstr_fd(row, 2);
	ft_putstr_fd(" column ", 2);
	ft_putstr_fd(col, 2);
	free(row);
	free(col);
	free_memory(map, EXIT_FAILURE);
}

void	ft_error(char **map, char *error)
{
	ft_putstr_fd(error, 2);
	free_memory(map, EXIT_FAILURE);
}
