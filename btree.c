/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis <aperis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 21:59:35 by ppajot            #+#    #+#             */
/*   Updated: 2022/07/27 19:33:00 by aperis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_btree *btree_create(t_list **token_list)
{
	int i;
	t_btree *cmd;
	t_btree *highest;

	i = 0;
	cmd = btree_cmd(token_list);
	while(*token_list && i == 0)
	{
		if ((*token_list)->content.token_type == PIPE)
			highest = node_pipe(&cmd, token_list);
		else if ((*token_list)->content.token_type == AND)
			highest = node_and(&cmd, token_list);
		else if ((*token_list)->content.token_type == OR)
			highest = node_or(&cmd, token_list);
		i++;
	}
	while(*token_list)
	{
		if ((*token_list)->content.token_type == PIPE)
			highest = node_pipe(&highest, token_list);
		else if ((*token_list)->content.token_type == AND)
			highest = node_and(&highest, token_list);
		else if ((*token_list)->content.token_type == OR)
			highest = node_or(&highest, token_list);
	}
	// si (pipe)
	// {
	// 	pipe->left = cmd;
	// 	pipeline->left = pipe;
	// 	pipeline->right = btree_cmd(token_list)
	// }
	return (highest);
}

t_btree *node_pipe( t_btree **cmd, t_list **token_list)
{
	t_btree *pipe;
	t_btree *p_seq;
	t_btree *new_cmd;

	*token_list = (*token_list)->next;
	pipe = malloc(sizeof(t_btree));
	p_seq = malloc(sizeof(t_btree));
	p_seq->content.token_type = PIPE_SEQUENCE;
	pipe->content.token_type = PIPE;
	pipe->left = *cmd;
	pipe->right = NULL;
	p_seq->left = pipe;
	new_cmd = btree_cmd(token_list);
	p_seq->right = new_cmd;
	return (p_seq);
}

t_btree *node_and(t_btree **cmd, t_list **token_list)
{
	t_btree *and;
	t_btree *op_seq;
	t_btree *new_cmd;

	*token_list = (*token_list)->next;
	and = malloc(sizeof(t_btree));
	op_seq = malloc(sizeof(t_btree));
	op_seq->content.token_type = OPERATEUR_SEQUENCE;
	and->content.token_type = AND;
	and->left = *cmd;
	and->right = NULL;
	op_seq->left = and;
	new_cmd = btree_cmd(token_list);
	op_seq->right = new_cmd;
	return (op_seq);
}

t_btree *node_or(t_btree **cmd, t_list **token_list)
{
	t_btree *or;
	t_btree *op_seq;
	t_btree *new_cmd;

	*token_list = (*token_list)->next;
	or = malloc(sizeof(t_btree));
	op_seq = malloc(sizeof(t_btree));
	op_seq->content.token_type = OPERATEUR_SEQUENCE;
	or->content.token_type = OR;
	or->left = *cmd;
	or->right = NULL;
	op_seq->left = or;
	new_cmd = btree_cmd(token_list);
	op_seq->right = new_cmd;
	return (op_seq);
}

t_btree	*btree_cmd(t_list **token_list)
{
	t_list *stack;
	t_btree *cmd;
	
	stack = NULL;
	cmd = malloc(sizeof(t_btree));
	cmd->content.token_type = SIMPLE_COMMAND;
	while((*token_list) && !check_op(token_list))
		shift(&stack, token_list);
	cmd = btree_cmd_left(&cmd, &stack);
	cmd = btree_cmd_right(&cmd, &stack);
	return (cmd);
} 