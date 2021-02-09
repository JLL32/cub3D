/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hach <ael-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 21:46:40 by jll32             #+#    #+#             */
/*   Updated: 2021/02/09 12:53:49 by ael-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		len;
	char	*ptr;
	int		i;

	if (!s)
		return (0);
	len = ft_strlen(s);
	ptr = (char*)malloc(len + 1);
	if (ptr == 0)
		return (0);
	i = 0;
	while (i < len)
	{
		*(ptr + i) = (*f)(i, *(s + i));
		i++;
	}
	*(ptr + i) = '\0';
	return (ptr);
}
