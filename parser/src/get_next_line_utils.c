/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobaz <mobaz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 09:50:41 by mobaz             #+#    #+#             */
/*   Updated: 2020/11/09 13:08:19 by mobaz            ###   ########.fr       */
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
