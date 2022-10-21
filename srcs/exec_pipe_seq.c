/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_seq.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis <aperis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 19:09:49 by ppajot            #+#    #+#             */
/*   Updated: 2022/09/21 19:17:27 by aperis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*btree_list_left_str(t_btree *root)
{
	if (!root)
		return ("");
	if (!root->left)
		return (root->content.string);
	return (btree_list_left_str(root->left));
}

void	exec_pipe_child(t_btree *root, int n, t_data *data)
{
	signal(SIGTERM, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (n > -1 && n + 1 < data->cmd_nbr)
		ft_dup(data->pfd[n % 2][0], 0, data);
	if (n > 0)
		ft_dup(data->pfd[(n + 1) % 2][1], 1, data);
	if (n > -1)
		close_fd(data);
	exec_cmd(root, data);
}

int	exec_pipe(t_btree *root, int n, t_data *data)
{
	int	pid;

	if (n == -1 && root->left != 0
		&& is_builtin(root->left->content.string, data) != -1)
	{
		data->exit_status = exec_single_builtin(root, data);
		return (-1);
	}
	if (n > -1 && n + 1 < data->cmd_nbr)
		pipe(data->pfd[n % 2]);
	pid = fork();
	if (pid == 0)
		exec_pipe_child(root, n, data);
	if (pid < 0)
		return (perror("fork"), 0);
	if (n > 0)
	{
		close(data->pfd[(n + 1) % 2][1]);
		close(data->pfd[(n + 1) % 2][0]);
	}
	return (pid);
}

void	exec_pipe_seq(t_btree *root, int n, t_data *data)
{
	int	pid;

	if (n == 0)
	{
		data->pfd[0][0] = -1;
		data->pfd[0][1] = -1;
		data->pfd[1][0] = -1;
		data->pfd[1][1] = -1;
	}
	if (root->left != 0 && root->left->content.token_type == PIPE)
	{
		pid = exec_pipe(root->right, n, data);
		exec_pipe_seq(root->left->left, n + 1, data);
	}
	else
		pid = exec_pipe(root, n, data);
	if (pid == -1)
		return ;
	if (n == data->cmd_nbr - 1)
		close_fd(data);
	if (pid != -1)
		waitpid(pid, &data->exit_status, 0);
	return ;
}
