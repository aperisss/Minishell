/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis <aperis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:37:19 by ppajot            #+#    #+#             */
/*   Updated: 2022/09/12 16:53:48 by aperis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/list.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current;
	t_list	*tmp;

	current = ft_lstlast(*lst);
	if (current == 0)
		*lst = new;
	else
		current->next = new;
	tmp = *lst;
	while (tmp)
		tmp = tmp->next;
}
