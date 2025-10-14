/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkeerewe <mkeerewe@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:42:22 by mkeerewe          #+#    #+#             */
/*   Updated: 2025/09/29 18:43:42 by mkeerewe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*curr;
	t_list	*new_lst;
	t_list	*new_node;

	if (!lst || !f || !del)
		return ((void *) 0);
	curr = lst;
	new_node = ft_lstnew(f(curr->content));
	if (new_node == (void *) 0)
		return (new_node);
	new_lst = new_node;
	curr = curr->next;
	while (curr != (void *) 0)
	{
		new_node = ft_lstnew(f(curr->content));
		if (new_node == (void *) 0)
		{
			ft_lstclear(&new_lst, del);
			return ((void *) 0);
		}
		ft_lstadd_back(&new_lst, new_node);
		curr = curr->next;
	}
	return (new_lst);
}
