/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_create_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis <aperis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 22:20:57 by ppajot            #+#    #+#             */
/*   Updated: 2022/09/12 16:56:31 by aperis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/btree.h"

t_btree	*btree_create_node(void	*content)
{
	t_btree	*new_elem;

	new_elem = (t_btree *)malloc(sizeof(t_btree));
	if (new_elem == 0)
		return (0);
	new_elem->content = content;
	new_elem->left = 0;
	new_elem->right = 0;
	return (new_elem);
}
