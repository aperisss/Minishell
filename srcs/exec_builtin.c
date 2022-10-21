/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis <aperis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 19:16:24 by ppajot            #+#    #+#             */
/*   Updated: 2022/09/21 19:49:10 by aperis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_builtin(int builtin_nbr, t_data *data)
{
	signal(SIGPIPE, SIG_IGN);
	return (data->builtin_tab[builtin_nbr].fct(data->cmd_av, data));
}

int	exec_single_builtin(t_btree *root, t_data *data)
{
	int		res;

	data->tempfd[0] = dup(0);
	data->tempfd[1] = dup(1);
	if (data->tempfd[0] < 0 || data->tempfd[1] < 0)
		exit_error(0, data, -1, strerror(errno));
	data->cmd_av = fill_av(root);
	if (redir(root->right, data) == 0)
	{
		data->exit_status = 1;
		return (1);
	}
	res = exec_builtin(is_builtin(data->cmd_av[0], data), data);
	free(data->cmd_av);
	ft_dup(data->tempfd[0], 0, data);
	ft_dup(data->tempfd[1], 1, data);
	close(data->tempfd[0]);
	close(data->tempfd[1]);
	return (res);
}

void	double_sig(void)
{
	signal(SIGPIPE, SIG_DFL);
	signal(SIGINT, sig_handler_int);
	signal(SIGTERM, SIG_DFL);
}

void	sig_double(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_handler_int);
}
