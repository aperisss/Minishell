/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis <aperis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 21:21:12 by ppajot            #+#    #+#             */
/*   Updated: 2022/09/21 19:25:00 by aperis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

unsigned char	g_exit_status;

int	init_envp(t_data *data, char **envp)
{
	char	*shlvl;
	char	*cwd;
	char	*path;

	data->envp = 0;
	cwd = getcwd(0, 0);
	path = ft_strjoin(cwd, "/minishell", "");
	shlvl = getenv("SHLVL");
	if (!shlvl)
		shlvl = ft_strdup("1");
	else
		shlvl = ft_itoa(ft_atoi(shlvl) + 1);
	if (shlvl == 0)
		return (0);
	put_env("PATH", BASE_PATH, 0, data);
	data->envp = tab_to_list(envp, data);
	put_env("PWD", cwd, 1, data);
	data->cwd = cwd;
	put_env("_", path, 1, data);
	put_env("SHLVL", shlvl, 1, data);
	free(path);
	free(shlvl);
	return (1);
}

int	init_data(t_data *data, char **envp)
{
	data++;
	data--;
	envp++;
	envp--;
	g_exit_status = 0;
	init_envp(data, envp);
	data->op = 0;
	data->exit_status = 0;
	init_builtin(data);
	return (1);
}

void	lex_pars_exec(char *str, t_data *data)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
	data->exit_status = 0;
	data->tempfd[0] = -1;
	data->tempfd[1] = -1;
	data->token_list = 0;
	data->op = 0;
	data->par = 0;
	data->ast = 0;
	data->token_list = lexer(str, data);
	if (data->token_list == 0)
		return ;
	data->ast = btree_create(&data->token_list, data, 0);
	data->hd_pfd = 0;
	data->exit_status = 0;
	free(str);
	open_hd(data->ast, data);
	exec_tree(data->ast, data);
	if (WIFEXITED(data->exit_status) && WEXITSTATUS(data->exit_status) == -1)
		exit_error(0, data, -1, 0);
	free_tree(data->ast);
	free_hd_pfd(data, 1);
}

void	sig_error_msg(t_data *data)
{
	if (WIFSIGNALED(data->exit_status)
		&& (WTERMSIG(data->exit_status) == SIGQUIT))
		write(2, "Quit (core dumped)\n", 19);
	if (WIFSIGNALED(data->exit_status)
		&& (WTERMSIG(data->exit_status) == SIGINT))
		write(1, "\n", 1);
}

int	main(int ac, char **av, char **envp)
{
	char	*str;
	t_data	data;

	ac++;
	av++;
	sig_double();
	init_data(&data, envp);
	while (1)
	{
		str = get_input();
		if (!str)
			break ;
		if (check_quote(str))
			lex_pars_exec(str, &data);
		double_sig();
		sig_error_msg(&data);
	}
	last_free(&data);
	if (isatty(2))
		write (2, "exit\n", 6);
	return (rl_clear_history(), g_exit_status);
}
