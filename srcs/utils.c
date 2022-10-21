/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis <aperis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 19:07:05 by ppajot            #+#    #+#             */
/*   Updated: 2022/09/21 19:31:39 by aperis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_prev_slash(char *curpath, int i)
{
	if (i == 0)
		return (0);
	while (--i >= 0)
	{
		if (curpath[i] == '/')
			return (i);
	}
	return (-1);
}

void	sig_handler_int(int signum)
{
	signum++;
	g_exit_status = 130;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

int	check_free(void **tab, int i)
{
	int	j;
	int	need_free;

	need_free = 0;
	j = -1;
	while (++j < i)
		if (!tab[j])
			need_free = 1;
	if (need_free)
		free_array((char **)tab);
	return (need_free);
}

void	exit_error(int av, t_data *data, int exit_status, char *exit_str)
{
	if (exit_str && *exit_str && data->cmd_av)
		write (2, "minishell: ", 12);
	write (2, exit_str, ft_strlen(exit_str));
	if (exit_str && *exit_str && data->cmd_av)
	{
		write (2, ": ", 2);
		write (2, data->cmd_av[0], ft_strlen(data->cmd_av[0]));
		write (2, "\n", 1);
	}
	if (av)
		free(data->cmd_av);
	free_data(data);
	close (0);
	close (1);
	exit (exit_status);
}

void	display(t_btree *ast, int lvl)
{
	if (ast == 0)
	{
		printf("\nEND\n");
		return ;
	}
	printf("\nstring = %s\ntype = %i\nlevel = %i\n",
		ast->content.string, ast->content.token_type, lvl);
	printf("\ngo left\n");
	display(ast->left, lvl + 1);
	printf("\ngo right\n");
	display(ast->right, lvl + 1);
}
