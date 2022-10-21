/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_readdir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppajot <ppajot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 20:37:39 by ppajot            #+#    #+#             */
/*   Updated: 2022/09/20 22:09:35 by ppajot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_wild(t_wild *w)
{
	w->i = 0;
	w->j = -1;
	w->k = 0;
	w->wild = NULL;
	w->str_wild = NULL;
}

void	mode_conditions(char **file, struct dirent *dir, int mode, int *i)
{
	if (mode == 0 && dir->d_name[0] != '.')
		file[++(*i)] = ft_strdup(dir->d_name);
	else if (mode == 1 && dir->d_name[0] != '.' && dir->d_type == 4)
		file[++(*i)] = ft_strjoin(dir->d_name, "/", "");
	else if (mode == 2)
		file[++(*i)] = ft_strdup(dir->d_name);
	else if (mode == 3 && dir->d_type == 4)
		file[++(*i)] = ft_strjoin(dir->d_name, "/", "");
	if (!file)
		exit (-1);
}

char	**read_dir(t_data *data, int mode)
{
	DIR				*current_dir;
	int				i;
	struct dirent	*dir;
	char			**file;

	i = 0;
	current_dir = opendir(ft_getenv("PWD", data->envp));
	while (readdir(current_dir) != 0)
		i++;
	closedir(current_dir);
	file = ft_calloc(i + 1, sizeof(char *));
	if (!file)
		exit (-1);
	current_dir = opendir(ft_getenv("PWD", data->envp));
	i = -1;
	dir = readdir(current_dir);
	while (dir)
	{
		mode_conditions(file, dir, mode, &i);
		dir = readdir(current_dir);
	}
	if (check_free((void **)file, i) == 1)
		exit (-1);
	closedir(current_dir);
	return (file);
}
