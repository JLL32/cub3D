/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 15:53:05 by mobaz             #+#    #+#             */
/*   Updated: 2019/10/15 11:46:22 by mobaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	int		i;

	i = 0;
	ptr = malloc(size * count);
	if (ptr)
	{
		while ((int)(count * size) > i)
		{
			*(char*)(ptr + i) = 0;
			i++;
		}
		return (ptr);
	}
	return (0);
}
