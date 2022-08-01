/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis <aperis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 21:59:35 by ppajot            #+#    #+#             */
/*   Updated: 2022/08/01 15:53:04 by aperis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_btree	*btree_create(t_list **token_list, t_data *data, int par)
{
	int		i;
	t_btree	*cmd;
	t_btree	*tmp;
	t_btree	*highest;

	i = 0;
	cmd = btree_cmd(token_list, data, par);
	while (*token_list && i == 0)
	{
		if ((*token_list)->content.token_type == PIPE)
			highest = node_pipe(&cmd, token_list, data, par);
		else if ((*token_list)->content.token_type == AND)
			highest = node_and(&cmd, token_list, data, par);
		else if ((*token_list)->content.token_type == OR)
			highest = node_or(&cmd, token_list, data, par);
		i++;
	}
	while (*token_list && data->par == par)
	{
		if ((*token_list)->content.token_type == PIPE)
			highest = node_pipe(&highest, token_list, data, par);
		else if ((*token_list)->content.token_type == AND)
			highest = node_and(&highest, token_list, data, par);
		else if ((*token_list)->content.token_type == OR)
			highest = node_or(&highest, token_list, data, par);
		else if ((*token_list)->content.token_type == CLOSE_PAR)
			*token_list = (*token_list)->next;
	}
	return (highest);
}

t_btree	*node_pipe( t_btree **cmd, t_list **token_list, t_data *data, int par)
{
	t_btree	*pipe;
	t_btree	*p_seq;
	t_btree	*new_cmd;

	*token_list = (*token_list)->next;
	pipe = malloc(sizeof(t_btree));
	p_seq = malloc(sizeof(t_btree));
	p_seq->content.token_type = PIPE_SEQUENCE;
	pipe->content.token_type = PIPE;
	pipe->left = *cmd;
	pipe->right = NULL;
	p_seq->left = pipe;
	if ((*token_list)->content.token_type == OPEN_PAR)
	{
		(*token_list) = (*token_list)->next;
		data->par++;
		new_cmd = btree_create(token_list, data, data->par);
		p_seq->right = new_cmd;
	}
	else
	{	
		new_cmd = btree_cmd(token_list, data, data->par);
		p_seq->right = new_cmd;
	}
	return (p_seq);
}

t_btree	*node_and(t_btree **cmd, t_list **token_list, t_data *data, int par)
{
	t_btree	*and;
	t_btree	*op_seq;
	t_btree	*new_cmd;

	*token_list = (*token_list)->next;
	and = malloc(sizeof(t_btree));
	op_seq = malloc(sizeof(t_btree));
	op_seq->content.token_type = OPERATEUR_SEQUENCE;
	and->content.token_type = AND;
	and->left = *cmd;
	and->right = NULL;
	op_seq->left = and;
	if ((*token_list)->content.token_type == OPEN_PAR)
	{
		(*token_list) = (*token_list)->next;
		data->par++;
		new_cmd = btree_create(token_list, data, data->par);
		op_seq->right = new_cmd;
	}
	else
	{	
		new_cmd = btree_cmd(token_list, data, par);
		op_seq->right = new_cmd;
	}
	return (op_seq);
}

t_btree	*node_or(t_btree **cmd, t_list **token_list, t_data *data, int par)
{
	t_btree	*or;
	t_btree	*op_seq;
	t_btree	*new_cmd;

	*token_list = (*token_list)->next;
	or = malloc(sizeof(t_btree));
	op_seq = malloc(sizeof(t_btree));
	op_seq->content.token_type = OPERATEUR_SEQUENCE;
	or->content.token_type = OR;
	or->left = *cmd;
	or->right = NULL;
	op_seq->left = or;
	if ((*token_list)->content.token_type == OPEN_PAR)
	{
		(*token_list) = (*token_list)->next;
		data->par++;
		new_cmd = btree_create(token_list, data, data->par);
		op_seq->right = new_cmd;
	}
	else
	{	
		new_cmd = btree_cmd(token_list, data, par);
		op_seq->right = new_cmd;
	}
	return (op_seq);
}

t_btree	*btree_cmd(t_list **token_list, t_data *data, int par)
{
	t_list	*stack;
	t_btree	*cmd;

	stack = NULL;
	cmd = malloc(sizeof(t_btree));
	cmd->content.token_type = SIMPLE_COMMAND;
	while ((*token_list) && !check_op(token_list) && data->par == par)
	{
		if ((*token_list)->content.token_type == CLOSE_PAR)
		{
			(*token_list) = (*token_list)->next;
			data->par--;
		}
		else
			shift(&stack, token_list);
	}
	cmd = btree_cmd_left(&cmd, &stack);
	cmd = btree_cmd_right(&cmd, &stack);
	return (cmd);
}
