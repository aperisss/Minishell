/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre-yves <pierre-yves@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 19:19:15 by ppajot            #+#    #+#             */
/*   Updated: 2022/09/16 21:26:19 by pierre-yves      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_fd(t_data *data)
{
	if (data->pfd[0][0] > -1)
		close(data->pfd[0][0]);
	if (data->pfd[0][1] > -1)
		close(data->pfd[0][1]);
	if (data->pfd[1][0] > -1)
		close(data->pfd[1][0]);
	if (data->pfd[1][1] > -1)
		close(data->pfd[1][1]);
}

void	ft_dup(int fd_in, int fd_out, t_data *data)
{
	if (dup2(fd_in, fd_out) < 0)
		exit_error(0, data, -1, strerror(errno));
}

int	size_left(t_btree *root)
{
	int	i;

	i = 0;
	while (root)
	{
		root = root->left;
		i++;
	}
	return (i);
}

int	count_cmd(t_btree *root)
{
	if (root == 0)
		return (0);
	if (root->content.token_type == SIMPLE_COMMAND)
		return (count_cmd(root->left) + count_cmd(root->right) + 1);
	return (count_cmd(root->left) + count_cmd(root->right));
}

int	is_builtin(char *cmd, t_data *data)
{
	int	i;

	i = -1;
	while (++i < 7)
		if (ft_strcmp(cmd, data->builtin_tab[i].name) == 0)
			return (i);
	return (-1);
}
