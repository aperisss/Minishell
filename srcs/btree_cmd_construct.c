/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_cmd_construct.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis <aperis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 16:03:15 by aperis            #+#    #+#             */
/*   Updated: 2022/09/10 18:00:19 by aperis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cmd_left(t_btree **cmd, t_list **stack, t_list **sless)
{
	t_token	*token;

	*stack = (*stack)->next;
	while (*stack)
	{
		token = (*stack)->content;
		if (!check_redir(sless) && token->token_type == WORDS)
		{
			add_node_left(cmd);
			(*cmd)->left->content.token_type = token->token_type;
			(*cmd)->left->content.string = token->string;
			*cmd = (*cmd)->left;
		}
		*stack = (*stack)->next;
		*sless = (*sless)->next;
	}
	(*cmd)->left = NULL;
	(*cmd)->right = NULL;
}

t_btree	*btree_cmd_left(t_btree **cmd, t_list **stack)
{
	t_token	*token;
	t_btree	*tmp;
	t_list	*stackless;
	t_list	*tmp_stack;

	tmp = *cmd;
	tmp_stack = *stack;
	if (*stack == 0)
		return (tmp);
	token = (*stack)->content;
	if (token->token_type == WORDS)
	{
		add_node_left(cmd);
		(*cmd)->left->content.token_type = token->token_type;
		(*cmd)->left->content.string = token->string;
		(*cmd)->right = NULL;
		*cmd = (*cmd)->left;
	}
	stackless = *stack;
	cmd_left(cmd, stack, &stackless);
	*stack = tmp_stack;
	return (tmp);
}

t_btree	*btree_cmd_right(t_btree **cmd, t_list **stack)
{	
	t_token	*token;
	t_token	*token2;
	t_btree	*tmp;
	t_list	*tmp_list;
	t_list	*stackless;

	tmp = *cmd;
	init_r(&tmp_list, &stackless, stack);
	while (*stack)
	{
		init_token(&token, &token2, *stack, stackless);
		if (check_redir(&stackless))
		{
			cmd_right(cmd, tmp, token2);
			add_node_right(cmd);
			(*cmd)->right->content.token_type = token->token_type;
			(*cmd)->right->content.string = token->string;
			btree_last(cmd);
			stack_up(stack, &stackless);
		}
		else
			stack_up(stack, &stackless);
	}
	*stack = tmp_list;
	return (tmp);
}

void	cmd_right(t_btree **cmd, t_btree *tmp, t_token *token2)
{
	if (tmp == *cmd)
	{
		add_node_right(cmd);
		(*cmd)->right->content.token_type
			= token2->token_type;
		(*cmd)->right->content.string
			= token2->string;
		*cmd = (*cmd)->right;
	}
	else
	{
		add_node_left(cmd);
		(*cmd)->left->content.token_type
			= token2->token_type;
		(*cmd)->left->content.string
			= token2->string;
		*cmd = (*cmd)->left;
	}
}

void	stack_up(t_list **stack, t_list **stackless)
{
	*stack = (*stack)->next;
	*stackless = (*stackless)->next;
}
