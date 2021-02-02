/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobaz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 11:28:55 by mobaz             #+#    #+#             */
/*   Updated: 2019/10/22 14:55:26 by mobaz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*rs;
	t_list	*node;

	node = NULL;
	if (!f || !del)
		return (NULL);
	while (lst != NULL)
	{
		if (node == NULL)
		{
			if (!(rs = ft_lstnew(f(lst->content))) && !f(lst->content))
				return (NULL);
			node = rs;
		}
		else
		{
			if (!(node->next = ft_lstnew(f(lst->content))))
				ft_lstclear(&rs, del);
			node = node->next;
		}
		lst = lst->next;
	}
	return (rs);
}
