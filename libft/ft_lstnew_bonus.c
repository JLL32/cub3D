/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 19:23:46 by mobaz             #+#    #+#             */
/*   Updated: 2019/10/18 20:01:09 by mobaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list *li;

	li = malloc(sizeof(t_list));
	if (!li)
		return (0);
	li->content = content;
	li->next = NULL;
	return (li);
}
