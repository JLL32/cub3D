/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hach <ael-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:47:30 by jll32             #+#    #+#             */
/*   Updated: 2021/02/09 12:53:49 by ael-hach         ###   ########.fr       */
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
