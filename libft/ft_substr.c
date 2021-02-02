/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobaz <mobaz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 23:07:06 by mobaz             #+#    #+#             */
/*   Updated: 2020/11/09 13:13:14 by mobaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int		i;
	char	*ptr;
	size_t	lens;

	if (!s)
		return (0);
	lens = ft_strlen(s);
	if (lens < start)
		len = 0;
	i = 0;
	ptr = (char*)malloc(len + 1);
	if (!ptr)
		return (0);
	while (i < (int)len && start < lens)
		*(ptr + i++) = *(s + start++);
	*(ptr + i) = '\0';
	return (ptr);
}
