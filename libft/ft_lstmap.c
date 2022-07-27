/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppajot <ppajot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:58:20 by ppajot            #+#    #+#             */
/*   Updated: 2022/07/24 18:43:50 by ppajot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, int (*f)(void *), void (*del)(void *))
{
	t_list	*current;
	t_list	*newlist;
	t_list	*newelem;

	current = lst;
	newlist = 0;
	while (current)
	{
		newelem = ft_lstnew(f(current->content));
		if (newelem == 0)
		{
			ft_lstclear(&newlist, del);
			break ;
		}
		ft_lstadd_back(&newlist, ft_lstnew(f(current->content)));
		current = current->next;
		del(newelem->content);
		free(newelem);
	}
	return (newlist);
}
