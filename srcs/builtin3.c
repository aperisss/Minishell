/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis <aperis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 19:55:55 by ppajot            #+#    #+#             */
/*   Updated: 2022/09/21 19:58:16 by aperis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_n_option(char *str)
{
	if (!str || *str != '-')
		return (0);
	str++;
	while (*str)
	{
		if (*str != 'n')
			return (0);
		str++;
	}
	return (1);
}

int	ft_echo(char **av, void *arg)
{
	int		endl;

	arg++;
	arg--;
	endl = 1;
	while (is_n_option(av[endl]))
		endl++;
	av += endl;
	while (*av)
	{
		write_protect(*av, (t_data *)arg, -1);
		if (*(av + 1) != 0)
			write_protect(" ", (t_data *)arg, -1);
		av++;
	}
	if (endl == 1)
		write_protect("\n", (t_data *)arg, -1);
	return (0);
}

int	ft_pwd(char **av, void *arg)
{
	char	*pwd;

	pwd = ft_getenv("PWD", ((t_data *)arg)->envp);
	av++;
	write(1, pwd, ft_strlen(pwd));
	write(1, "\n", 1);
	return (0);
}

int	ft_env(char **av, void *arg)
{
	t_data	*data;
	t_list	*tmp;
	t_dict	*entry;

	data = arg;
	av++;
	tmp = data->envp;
	while (tmp)
	{
		entry = tmp->content;
		if (entry->print == 1)
		{
			write_protect(entry->name, data, -1);
			write_protect("=", data, -1);
			write_protect(entry->value, data, -1);
			write_protect("\n", data, -1);
		}
		tmp = tmp->next;
	}
	return (0);
}
