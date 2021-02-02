/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobaz <mobaz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 13:38:02 by mobaz             #+#    #+#             */
/*   Updated: 2020/11/13 13:40:21 by mobaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strcmp(const char *x, const char *y)
{
	while (*x)
	{
		if (*x != *y)
			break ;
		x++;
		y++;
	}
	return (*(const unsigned char*)x - *(const unsigned char*)y);
}
