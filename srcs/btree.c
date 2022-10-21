/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppajot <ppajot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 21:59:35 by ppajot            #+#    #+#             */
/*   Updated: 2022/09/20 22:10:13 by ppajot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_btree	*btree_create(t_list **token_list, t_data *data, int par)
{
	t_token	*token;
	t_btree	*cmd;
	t_btree	*highest;
	int		i;

	i = 0;
	after_par(token_list);
	cmd = btree_cmd(token_list, data, par);
	while (*token_list && data->par == par)
	{
		token = (*token_list)->content;
		if (i == 0 && check_op(token_list))
			highest = node_op(&cmd, token_list, data, par);
		else if (i && check_op(token_list))
			highest = node_op(&highest, token_list, data, par);
		else if (i && token->token_type == CLOSE_PAR)
			free_and_next(token_list);
		i++;
	}
	if (i == 0)
		return (cmd);
	return (highest);
}

t_btree	*node_op(t_btree **cmd, t_list **token_list, t_data *data, int par)
{
	t_token	*token;
	t_btree	*highest;

	highest = create_node_op(cmd, token_list, data);
	token = (*token_list)->content;
	if (token->token_type == OPEN_PAR)
	{
		free_and_next(token_list);
		data->par++;
		data->op = 0;
		highest->right = btree_create(token_list, data, data->par);
	}
	else if (next_op(*token_list) && data->op == 1)
		highest->right = tree_pipe(token_list, data, par);
	else
		highest->right = btree_cmd(token_list, data, par);
	return (highest);
}

t_btree	*create_node_op(t_btree **cmd, t_list **token_list, t_data *data)
{
	t_btree	*op;
	t_btree	*seq;

	op = malloc(sizeof(t_btree));
	if (!op)
		exit (-1);
	seq = malloc(sizeof(t_btree));
	if (!seq)
		exit (-1);
	op->left = *cmd;
	op->right = NULL;
	seq->left = op;
	seq->right = NULL;
	seq = init_node_op(seq, *token_list, data);
	free_and_next(token_list);
	return (seq);
}

t_btree	*init_node_op(t_btree *cmd, t_list *token_list, t_data *data)
{
	t_token	*token;

	token = token_list->content;
	if (token->token_type == PIPE)
	{
		cmd->content.token_type = PIPE_SEQUENCE;
		cmd->left->content.token_type = PIPE;
		init_string(&cmd, &token_list);
	}
	else if (token->token_type == AND)
	{
		cmd->content.token_type = OPERATEUR_SEQUENCE;
		cmd->left->content.token_type = AND;
		init_string(&cmd, &token_list);
		data->op = 1;
	}
	else if (token->token_type == OR)
	{
		cmd->content.token_type = OPERATEUR_SEQUENCE;
		cmd->left->content.token_type = OR;
		init_string(&cmd, &token_list);
		data->op = 1;
	}
	return (cmd);
}

t_btree	*btree_cmd(t_list **token_list, t_data *data, int par)
{
	t_list	*stack;
	t_btree	*cmd;
	t_token	*token;

	stack = NULL;
	cmd = malloc(sizeof(t_btree));
	if (!cmd)
		exit (-1);
	init_cmd(&cmd);
	while ((*token_list) && !check_op(token_list) && data->par == par)
	{
		token = (*token_list)->content;
		if (token->token_type == CLOSE_PAR)
		{
			free_and_next(token_list);
			if (data->par)
				data->par--;
		}
		else
			shift(&stack, token_list);
	}
	cmd = btree_cmd_left(&cmd, &stack);
	cmd = btree_cmd_right(&cmd, &stack);
	free_list(stack);
	return (cmd);
}
