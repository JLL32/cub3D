/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:47:30 by mobaz             #+#    #+#             */
/*   Updated: 2019/10/22 18:50:49 by mobaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t				i;
	unsigned char		*ptr;
	const unsigned char	*ptr2;

	ptr = (unsigned char*)dst;
	ptr2 = (unsigned char*)src;
	i = 1;
	if (!ptr && !ptr2)
		return (NULL);
	if (ptr2 < ptr)
		while (i <= len)
		{
			ptr[len - i] = ptr2[len - i];
			i++;
		}
	else
		while (len-- > 0)
			*(ptr++) = *(ptr2++);
	return (dst);
}
