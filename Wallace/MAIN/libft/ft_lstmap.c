/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchow <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 20:43:46 by wchow             #+#    #+#             */
/*   Updated: 2023/09/21 14:14:36 by wchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist;
	t_list	*current;
	t_list	*newnode;

	newlist = NULL;
	if (!lst || !f || !del)
		return (NULL);
	current = lst;
	while (current)
	{
		newnode = ft_lstnew(f(current->content));
		if (!newnode)
		{
			if (current)
				del(current);
			ft_lstclear(&newlist, del);
			return (NULL);
		}
		ft_lstadd_back(&newlist, newnode);
		current = current->next;
	}
	return (newlist);
}
