/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppajot <ppajot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:17:37 by ppajot            #+#    #+#             */
/*   Updated: 2022/07/29 19:05:15 by ppajot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/list.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*newelem;

	newelem = (t_list *)malloc(sizeof(t_list));
	if (newelem == 0)
		return (0);
	newelem->content = content;
	newelem->next = 0;
	return (newelem);
}
