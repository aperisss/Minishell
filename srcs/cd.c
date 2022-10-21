/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis <aperis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 17:38:04 by ppajot            #+#    #+#             */
/*   Updated: 2022/09/21 16:09:16 by aperis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*curpath_trailing_slash(char *av1, t_data *data)
{
	char	*curpath;
	char	*sec_part;

	sec_part = 0;
	if (av1[0] == '/')
	{
		if (av1[ft_strlen(av1) - 1] != '/')
			curpath = ft_strjoin(av1, "/", "");
		else
			curpath = ft_strdup(av1);
	}
	else
	{
		if (av1[ft_strlen(av1) - 1] != '/')
		{
			sec_part = ft_strjoin(av1, "/", "");
			if (!sec_part)
				return (0);
			curpath = ft_strjoin(data->cwd, sec_part, "/");
		}	
		else
			curpath = ft_strjoin(data->cwd, av1, "/");
	}
	free (sec_part);
	return (curpath);
}

char	*get_curpath(int ac, char *av1, t_data *data)
{
	char	*curpath;

	if (ac == 1)
	{
		if (env_var_exists("HOME", data)
			&& ft_getenv("HOME", data->envp)[0] == 0)
			return (ft_strjoin(data->cwd, "/", ""));
		else if (ft_getenv("HOME", data->envp)
			[ft_strlen(ft_getenv("HOME", data->envp)) - 1] == '/')
			curpath = ft_strdup(ft_getenv("HOME", data->envp));
		else
			curpath = ft_strjoin(ft_getenv("HOME", data->envp), "/", "");
	}
	else
		curpath = curpath_trailing_slash(av1, data);
	return (curpath);
}

int	only_points(char *str)
{
	int	slash;

	slash = 0;
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == '/')
			slash = 0;
		if (*str != '/' && *str != '.')
			return (0);
		if (*str == '.')
			slash++;
		if (slash > 2)
			return (0);
		str++;
	}
	return (1);
}

char	*new_cwd(char *curpath, int onlypoints)
{
	char	*cwd;

	if (onlypoints != 2)
		return (curpath);
	cwd = getcwd(0, 0);
	free (curpath);
	return (cwd);
}

int	ft_cd(char **av, void *arg)
{
	char	*curpath;
	t_data	*data;
	int		ac;
	int		onlypoints;

	ac = ft_array_size(av);
	data = (t_data *)arg;
	if (ac > 2)
		return (write (2, "too many arguments\n", 20), 1);
	if (ac == 1 && !env_var_exists("HOME", data))
		return (write (2, "minishell: cd: HOME not set\n", 29), 1);
	curpath = get_curpath(ac, av[1], data);
	if (!curpath)
		exit_error(0, data, -1, 0);
	onlypoints = only_points(av[1]);
	if (!reduce_points(curpath) && onlypoints++ && chdir(av[1]))
		return (free(curpath), perror("cd"), 1);
	if (onlypoints != 2 && chdir(curpath))
		return (free(curpath), perror("cd"), 1);
	if (curpath[ft_strlen(curpath) - 1] == '/' && ft_strlen(curpath) != 1)
		curpath[ft_strlen(curpath) - 1] = 0;
	free(data->cwd);
	data->cwd = new_cwd(curpath, onlypoints);
	put_env("OLDPWD", ft_getenv("PWD", data->envp), 1, data);
	return (put_env("PWD", data->cwd, 1, data), 0);
}
