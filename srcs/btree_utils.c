/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppajot <ppajot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 16:03:37 by aperis            #+#    #+#             */
/*   Updated: 2022/09/20 22:10:26 by ppajot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	shift(t_list **stack_list, t_list **token_list)
{
	t_list	*tmp;

	if (!*token_list)
		return ;
	if (*stack_list)
		ft_listlast(*stack_list)->next = *token_list;
	else
		*stack_list = *token_list;
	tmp = (*token_list)->next;
	(*token_list)->next = 0;
	*token_list = tmp;
}

void	add_node_right(t_btree **cmd)
{
	t_btree	*node_right;

	node_right = malloc(sizeof(t_btree));
	if (!node_right)
		exit (-1);
	node_right->left = 0;
	node_right->right = 0;
	(*cmd)->right = node_right;
}

void	add_node_left(t_btree **cmd)
{
	t_btree	*node;

	node = malloc(sizeof(t_btree));
	if (!node)
		exit (-1);
	node->left = 0;
	node->right = 0;
	(*cmd)->left = node;
}

void	add_node_left_and_right(t_btree **cmd)
{
	t_btree	*node_left;
	t_btree	*node_right;

	node_left = malloc(sizeof(t_btree));
	if (!node_left)
		exit (-1);
	node_right = malloc(sizeof(t_btree));
	if (!node_right)
		exit (-1);
	node_right->left = 0;
	node_right->right = 0;
	node_left->left = 0;
	node_left->right = 0;
	(*cmd)->left = node_left;
	(*cmd)->right = node_right;
}

void	btree_last(t_btree **cmd)
{
	t_btree	*tmp;

	tmp = *cmd;
	*cmd = (*cmd)->right;
	(*cmd)->right = NULL;
	(*cmd)->left = NULL;
	*cmd = tmp;
}
