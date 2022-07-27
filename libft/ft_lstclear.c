/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppajot <ppajot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:43:53 by ppajot            #+#    #+#             */
/*   Updated: 2022/07/24 18:43:35 by ppajot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*temp;

	current = *lst;
	*lst = 0;
	while (current)
	{
		temp = current->next;
		if (del != 0)
			del(current->content);
		free(current);
		current = temp;
	}
}
