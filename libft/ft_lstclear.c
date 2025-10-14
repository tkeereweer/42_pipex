/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkeerewe <mkeerewe@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:42:22 by mkeerewe          #+#    #+#             */
/*   Updated: 2025/08/30 15:46:59 by mkeerewe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*curr;
	t_list	*next_node;

	if (lst == (void *) 0 || *lst == (void *) 0 || !del)
		return ;
	curr = *lst;
	while (curr->next != (void *) 0)
	{
		next_node = curr->next;
		ft_lstdelone(curr, del);
		curr = next_node;
	}
	ft_lstdelone(curr, del);
	*lst = (void *) 0;
}
