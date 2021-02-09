/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jll32 <jll32@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 09:50:41 by jll32             #+#    #+#             */
/*   Updated: 2020/11/09 13:08:19 by jll32            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

void		*ft_char_calloc(size_t count)
{
	void	*ptr;
	int		i;

	i = 0;
	ptr = malloc(count);
	if (ptr)
	{
		while ((int)(count) > i)
		{
			*(char*)(ptr + i) = 0;
			i++;
		}
		return (ptr);
	}
	return (0);
}
