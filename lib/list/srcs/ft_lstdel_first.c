/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel_first.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis <aperis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 16:59:51 by ppajot            #+#    #+#             */
/*   Updated: 2022/09/12 16:53:06 by aperis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/list.h"

void	ft_lstdel_first(t_list **list, void (*del)(void *))
{
	t_list	*tmp;

	tmp = *list;
	if (*list)
	{
		*list = (*list)->next;
		del(tmp->content);
		free(tmp);
	}
}
