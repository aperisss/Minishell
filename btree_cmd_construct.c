#include "minishell.h"

t_btree *btree_cmd_left(t_btree **cmd, t_list **stack)
{
	t_btree *tmp;
	t_list	*stackless;
	t_list	*tmp_stack;

	tmp = *cmd;
	tmp_stack = *stack;
	if ((*stack)->content.token_type == WORDS)
	{
		add_node_left_and_right(cmd);
		(*cmd)->left->content.token_type = (*stack)->content.token_type;
		(*cmd)->right = NULL;
		*cmd = (*cmd)->left;
	}
	stackless = *stack;
	*stack = (*stack)->next;
	while (*stack)
	{
		if (!check_redir(&stackless) && (*stack)->content.token_type == WORDS)
		{
			add_node_left_and_right(cmd);
			(*cmd)->left->content.token_type = (*stack)->content.token_type;
			(*cmd)->right = NULL;
			*cmd = (*cmd)->left;
		}
		*stack = (*stack)->next;
		stackless = stackless->next;
	}
	(*cmd)->left = NULL;
	(*cmd)->right = NULL;
	*stack = tmp_stack;
	return (tmp);
}

t_btree *btree_cmd_right(t_btree **cmd, t_list **stack)
{
	t_btree *tmp;
	t_list	*stackless;

	tmp = *cmd;
	stackless = *stack;


	
	*stack = (*stack)->next;
	while(*stack)
	{
		if (check_redir(&stackless))
		{
			if (tmp == *cmd)
			{
				add_node_right(cmd);
				(*cmd)->right->content.token_type = stackless->content.token_type;
				*cmd = (*cmd)->right;
			}
			else
			{
				add_node_left(cmd);
				(*cmd)->left->content.token_type = stackless->content.token_type;
				*cmd = (*cmd)->left;
			}
			add_node_right(cmd);
			(*cmd)->right->content.token_type = (*stack)->content.token_type;
			btree_last(cmd);
			stackless = stackless->next;
			*stack = (*stack)->next;
		}
		else
		{
			stackless = stackless->next;
			*stack = (*stack)->next;
		}
	}
	(*cmd)->left = NULL;
	return (tmp);
}
