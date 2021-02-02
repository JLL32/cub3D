/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jll32 <jll32@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 12:19:09 by mobaz             #+#    #+#             */
/*   Updated: 2021/01/28 18:07:39 by jll32            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../cub.h"
#include "../parser.h"

void	free_double_pointer(char **ptr)
{
	int i;

	i = 0;
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
}

int		free_memory(char **map,int status)
{
	// free(g_rays);
	if (map)
		free_double_pointer(map);
	exit(status);
	return (0);
}
