/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppajot <ppajot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 22:14:10 by ppajot            #+#    #+#             */
/*   Updated: 2022/09/20 21:35:37 by ppajot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	has_quote(char *str)
{
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
			return (1);
		str++;
	}
	return (0);
}

void	number_and_fill(t_btree *root, t_data *data, int *count)
{
	int	pid;

	if (root == 0 || (WIFSIGNALED(data->exit_status)
			&& WTERMSIG(data->exit_status) == SIGTERM))
		return ;
	if (root->content.token_type == DLESS)
	{
		root->content.token_type |= (*count << 8);
		if (has_quote(root->right->content.string))
		{
			reduce_quote(root->right->content.string);
			root->content.token_type |= (1 << 24);
		}
		pid = fill_hd(data, root->right->content.string, *count);
		waitpid(pid, &data->exit_status, 0);
		if ((WIFSIGNALED(data->exit_status)
				&& WTERMSIG(data->exit_status) == SIGTERM))
		{
			write (1, "^C\n", 4);
			g_exit_status = 130;
		}	
		(*count)++;
	}
	number_and_fill(root->left, data, count);
	number_and_fill(root->right, data, count);
}

int	count_hd(t_btree *root)
{
	if (root == 0)
		return (0);
	if (root->content.token_type == DLESS)
		return (count_hd(root->left) + count_hd(root->right) + 1);
	return (count_hd(root->left) + count_hd(root->right));
}

void	open_hd(t_btree *root, t_data *data)
{
	int	i;

	data->hd_nbr = count_hd(root);
	if (!data->hd_nbr)
		return ;
	data->hd_pfd = (int **)malloc(sizeof(int *) * data->hd_nbr);
	i = -1;
	while (++i < data->hd_nbr)
	{
		data->hd_pfd[i] = (int *)malloc(sizeof(int) * 2);
		pipe(data->hd_pfd[i]);
	}
	if (check_free((void **)data->hd_pfd, i))
		exit_error(0, data, -1, 0);
	i = 0;
	number_and_fill(root, data, &i);
}
