/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_apply_prefix.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis <aperis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 16:08:06 by ppajot            #+#    #+#             */
/*   Updated: 2022/09/12 16:56:12 by aperis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/btree.h"

void	btree_apply_prefix(t_btree *root, void (*applyf)(void *))
{
	if (!root)
		return ;
	(*applyf)(root->content);
	btree_apply_prefix(root->left, applyf);
	btree_apply_prefix(root->right, applyf);
}
