/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis <aperis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 19:12:53 by ppajot            #+#    #+#             */
/*   Updated: 2022/09/21 19:34:58 by aperis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**fill_av(t_btree *root)
{
	int		i;
	char	**av;

	i = size_left(root->left);
	av = (char **)malloc(sizeof(char *) * (i + 1));
	if (!av)
		return (0);
	av[i] = 0;
	root = root->left;
	i = 0;
	while (root)
	{
		av[i] = root->content.string;
		root = root->left;
		i++;
	}
	return (av);
}

int	redir(t_btree *root, t_data *data)
{
	int		fd;
	char	*path;

	if (root == 0)
		return (-1);
	if ((!root->right || root->right->left))
		return (write (2, "ambiguous redirect\n", 20), 0);
	path = root->right->content.string;
	if (root->content.token_type == RET_TO)
		fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 00644);
	if (root->content.token_type == DGREAT)
		fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 00644);
	if (root->content.token_type == RET_FROM)
		fd = open(path, O_RDONLY);
	if ((root->content.token_type & 0xff) == DLESS)
		fd = expand_here_doc(root->content.token_type, data);
	if (fd < 0)
		return (perror(path), 0);
	if ((root->content.token_type & 0xff) % 2 == 1)
		ft_dup(fd, 0, data);
	if (root->content.token_type % 2 == 0)
		ft_dup(fd, 1, data);
	close (fd);
	return (redir(root->left, data));
}

int	is_dir_exec(char **av, t_data *data)
{
	struct stat	buff;

	if (ft_strchr(av[0], '/'))
	{
		if (stat(av[0], &buff))
			exit_error(1, data, 127, "command not found");
		if (S_ISDIR(buff.st_mode))
			exit_error(1, data, 126, "is a directory");
		if (access(av[0], X_OK))
			exit_error(1, data, 126, "permission denied");
		return (0);
	}
	else
		return (1);
}

char	*get_path(char **av, t_data *data)
{
	char	**path_tab;
	int		i;
	char	*cmd_path;

	if (av[0] == 0 || av[0][0] == 0)
		return (av[0]);
	if (is_dir_exec(av, data) == 0)
		return (av[0]);
	path_tab = ft_split(ft_getenv("PATH", data->envp), ':');
	if (path_tab == 0)
		return (0);
	i = -1;
	while (path_tab[++i])
	{
		cmd_path = ft_strjoin(path_tab[i], av[0], "/");
		if (cmd_path == 0)
			return (free_array(path_tab), (void *)0);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
	}
	data->exit_status = 127;
	free_array(path_tab);
	return (0);
}

int	exec_cmd(t_btree *root, t_data *data)
{
	char	*cmd;
	int		ret;

	if (redir(root->right, data) == 0)
		exit_error(0, data, 1, 0);
	free_hd_pfd(data, 0);
	data->cmd_av = fill_av(root);
	if (!data->cmd_av)
		exit_error(0, data, -1, 0);
	if (data->cmd_av[0] == 0)
		exit_error(1, data, 0, 0);
	if (is_builtin(data->cmd_av[0], data) == -1)
	{
		cmd = get_path(data->cmd_av, data);
		if (cmd == 0 || cmd[0] == 0)
			exit_error(1, data, 127, "command not found");
		execve(cmd, data->cmd_av, list_to_tab(data->envp));
	}
	else
		ret = exec_builtin(is_builtin(data->cmd_av[0], data), data);
	if (is_builtin(data->cmd_av[0], data) != -1)
		exit_error(1, data, ret, 0);
	perror("execve");
	exit (1);
}
