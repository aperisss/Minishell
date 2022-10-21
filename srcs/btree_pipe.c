/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis <aperis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 16:43:16 by aperis            #+#    #+#             */
/*   Updated: 2022/09/10 18:39:40 by aperis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_string(t_btree **cmd, t_list **token_list)
{
	t_token	*token;

	token = (*token_list)->content;
	(*cmd)->content.string = 0;
	(*cmd)->left->content.string = token->string;
}

void	after_par(t_list **token_list)
{
	t_token	*token;

	token = (*token_list)->content;
	while (token->token_type == OPEN_PAR)
	{
		free_and_next(token_list);
		token = (*token_list)->content;
	}
}

int	next_op(t_list *token_list)
{
	t_token	*token;

	while (token_list && !check_op(&token_list))
	{
		token = token_list->content;
		token_list = token_list->next;
	}
	if (token_list)
		token = token_list->content;
	if (token_list)
	{
		if (token->token_type == PIPE)
			return (1);
	}
	return (0);
}

void	shift_pipe(t_list **token_list, t_list **stack, t_data *data)
{
	t_token	*token;

	if (*token_list)
	{
		while (*token_list && !check_op(token_list))
			shift(stack, token_list);
	}
	if (*token_list == 0)
	{
		data->op = 0;
		return ;
	}
	token = (*token_list)->content;
	if (token->token_type == CLOSE_PAR)
	{
		data->par--;
		free_and_next(token_list);
	}
	data->op = 0;
}

t_btree	*tree_pipe(t_list **token_list, t_data *data, int par)
{
	t_list	*stack;
	t_btree	*cmd;
	t_token	*token;

	stack = NULL;
	cmd = NULL;
	while ((*token_list) && next_op(*token_list) && data->par == par)
	{
		token = (*token_list)->content;
		if (token->token_type == CLOSE_PAR)
		{
			free_and_next(token_list);
			data->par--;
		}
		else
		{
			while (!check_op(token_list) && *token_list)
				shift(&stack, token_list);
			if (*token_list)
				shift(&stack, token_list);
		}
	}
	shift_pipe(token_list, &stack, data);
	cmd = btree_create(&stack, data, par);
	return (cmd);
}
