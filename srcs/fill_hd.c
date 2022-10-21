/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_hd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppajot <ppajot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 19:38:48 by ppajot            #+#    #+#             */
/*   Updated: 2022/09/20 21:57:42 by ppajot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fill_hd_child(t_data *data, char *lim, int count)
{
	char	*str;

	signal(SIGTERM, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	str = readline("> ");
	close(data->hd_pfd[count][0]);
	while (str && ft_strcmp(str, lim))
	{	
		write(data->hd_pfd[count][1], str, ft_strlen(str));
		write(data->hd_pfd[count][1], "\n", 1);
		free(str);
		str = readline("> ");
	}
	write (1, "\n", 1);
	close (data->hd_pfd[count][1]);
	free_data(data);
	free (str);
	exit(0);
}

int	fill_hd(t_data *data, char *lim, int count)
{
	int	pid;

	pid = fork();
	if (pid == 0)
		fill_hd_child(data, lim, count);
	else if (pid < 0)
		perror("fork");
	close (data->hd_pfd[count][1]);
	return (pid);
}

void	reinit_root(t_btree **root, int *i)
{
	*root = (*root)->left;
	*i = -1;
}
