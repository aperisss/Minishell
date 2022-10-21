/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_apply_infix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis <aperis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 16:08:06 by ppajot            #+#    #+#             */
/*   Updated: 2022/09/12 16:56:10 by aperis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/btree.h"

void	btree_apply_infix(t_btree *root, void (*applyf)(void *))
{
	if (!root)
		return ;
	btree_apply_infix(root->left, applyf);
	(*applyf)(root->content);
	btree_apply_infix(root->right, applyf);
}
