/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strnstr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 11:30:57 by mobaz             #+#    #+#             */
/*   Updated: 2019/10/17 17:32:49 by mobaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (*needle == '\0')
		return ((char*)haystack);
	while (*(haystack + i) != '\0' && i < (int)len)
	{
		while (*(needle + j) == *(haystack + i) && i < (int)len)
		{
			j++;
			i++;
			if (*(needle + j) == '\0')
				return ((char *)haystack + (i - j));
		}
		i = i - j;
		j = 0;
		i++;
	}
	return (0);
}
