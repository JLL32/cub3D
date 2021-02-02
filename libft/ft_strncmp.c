/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:14:40 by mobaz             #+#    #+#             */
/*   Updated: 2019/10/22 15:16:35 by mobaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_memncmp(const void *s1, const void *s2, size_t n)
{
	int					i;
	unsigned char		*str1;
	unsigned char		*str2;

	if (n == 0)
		return (0);
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while (i < (int)n - 1 && *(str1 + i) == *(str2 + i))
	{
		if ((*(str1 + i) || *(str2 + i)) == '\0')
			break ;
		i++;
	}
	return (*(str1 + i) - *(str2 + i));
}

int				ft_strncmp(const char *s1, const char *s2, size_t n)
{
	return (ft_memncmp(s1, s2, n));
}
