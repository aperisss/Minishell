/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis <aperis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 18:22:21 by ppajot            #+#    #+#             */
/*   Updated: 2022/09/21 19:49:26 by aperis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_retoken_space(t_btree *root, t_btree *prev, int export)
{
	if (root == 0)
		return ;
	if (export && check_name(root->content.string, 0))
		root->content.token_type = root->content.token_type | (1 << 8);
	if (prev && prev->content.token_type == SIMPLE_COMMAND
		&& ft_strcmp(root->content.string, "export") == 0)
		export = 1;
	check_retoken_space(root->left, root, export);
	check_retoken_space(root->right, root, export);
}

int	put_exit_status(t_data *data)
{
	unsigned char	a;

	a = 0;
	if (WIFSIGNALED(data->exit_status)
		&& WTERMSIG(data->exit_status) == SIGINT)
		g_exit_status = 130;
	else if (WIFSIGNALED(data->exit_status)
		&& WTERMSIG(data->exit_status) == SIGQUIT)
		g_exit_status = 131;
	else
	{
		if (WIFEXITED(data->exit_status))
			a = WEXITSTATUS(data->exit_status);
		else
			a = data->exit_status;
		g_exit_status = a;
	}
	return (a);
}

int	ft_check_end_sig(int exit_status)
{
	return (WIFSIGNALED(exit_status) && (WTERMSIG(exit_status) == SIGINT
			|| WTERMSIG(exit_status) == SIGQUIT));
}

int	exec_tree(t_btree *root, t_data *data)
{
	int	a;

	if (WIFEXITED(data->exit_status) && WEXITSTATUS(data->exit_status) == -1)
		exit_error(0, data, -1, 0);
	if (ft_check_end_sig(data->exit_status))
		return (0);
	if (root->content.token_type == OPERATEUR_SEQUENCE)
	{
		exec_tree(root->left->left, data);
		a = put_exit_status(data);
		if ((root->left->content.token_type == AND && a == 0)
			|| (root->left->content.token_type == OR && a != 0))
			exec_tree(root->right, data);
	}
	else
	{
		data->cmd_nbr = count_cmd(root);
		check_retoken_space(root, 0, 0);
		expand_quote(root, data, 0);
		if (root->content.token_type == PIPE_SEQUENCE)
			exec_pipe_seq(root, 0, data);
		else
			exec_pipe_seq(root, -1, data);
	}
	return (put_exit_status(data), 0);
}
