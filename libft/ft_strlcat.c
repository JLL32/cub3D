/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hh.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 12:48:19 by mobaz             #+#    #+#             */
/*   Updated: 2019/10/16 21:16:51 by mobaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		i;
	size_t		v;
	size_t		len;

	len = ft_strlen(src);
	i = 0;
	while (*dst != '\0' && i < size)
	{
		dst++;
		i++;
	}
	v = size - i;
	if (v == 0)
		return (i + ft_strlen(src));
	while (*src != '\0' && v != 1)
	{
		*dst++ = *src;
		v--;
		src++;
	}
	*dst = '\0';
	return (i + len);
}
