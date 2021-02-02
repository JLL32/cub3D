/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 13:23:42 by mobaz             #+#    #+#             */
/*   Updated: 2019/10/17 17:30:40 by mobaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	x;
	int				i;
	char			*ptr;

	ptr = b;
	i = 0;
	x = c;
	while (i < (int)len)
	{
		*(ptr + i) = x;
		i++;
	}
	return (ptr);
}
