/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:56:50 by mobaz             #+#    #+#             */
/*   Updated: 2019/10/17 17:25:23 by mobaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	char	*s;
	char	*d;
	int		i;

	i = 0;
	s = (char*)src;
	d = (char*)dst;
	while (i < (int)n)
	{
		*(d + i) = *(s + i);
		if (*(unsigned char *)(s + i) == (unsigned char)c)
			return (d + (i + 1));
		i++;
	}
	return (NULL);
}
