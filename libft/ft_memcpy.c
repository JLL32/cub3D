/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:56:50 by mobaz             #+#    #+#             */
/*   Updated: 2019/10/22 19:24:50 by mobaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	int				i;

	if (!dst && !src)
		return (0);
	i = 0;
	s = (unsigned char *)src;
	d = (unsigned char *)dst;
	while ((int)n > i)
	{
		*(d + i) = *(s + i);
		i++;
	}
	return (d);
}
