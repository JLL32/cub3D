/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memchr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 19:12:44 by mobaz             #+#    #+#             */
/*   Updated: 2019/10/17 17:40:32 by mobaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const	char	*str;
	int				i;

	i = 0;
	str = s;
	while (i < (int)n)
	{
		if (*(unsigned char *)(str + i) == (unsigned char)c)
			return (void*)(str + i);
		i++;
	}
	return (0);
}
