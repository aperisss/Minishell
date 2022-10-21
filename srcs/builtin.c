/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppajot <ppajot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 22:33:48 by pierre-yves       #+#    #+#             */
/*   Updated: 2022/09/21 17:32:12 by ppajot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_number(char *str)
{
	long long	res;
	int			neg;

	neg = 0;
	res = 0;
	while (*str == ' ' || *str == '\t')
		str++;
	if (*str == '-' || *str == '+')
	{
		neg = (*str - 43) / 2 ;
		str++;
	}
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		if ((res == 922337203685477580 && *str > '7' + neg)
			|| res > 922337203685477580)
			return (0);
		res = res * 10 + *str - 48;
		str++;
	}
	return (1);
}

int	ft_exit(char **av, void *arg)
{
	t_data			*data;
	unsigned char	exit_value;

	data = arg;
	if (isatty(2) && isatty(0) && isatty(1))
		write(2, "exit\n", 5);
	if (av[1] != 0 && av[2] != 0)
		return (write(2, "minishell: exit: too many arguments\n", 37), 1);
	if (av[1] != 0)
	{
		if (!is_number(av[1]))
		{
			exit_value = 2;
			write (2, "minishell: ", 12);
			write (2, av[1], ft_strlen(av[1]));
			write(2, ": numeric argument required\n", 29);
		}	
		else
			exit_value = ft_atoi(av[1]);
	}
	else
		exit_value = g_exit_status;
	free_exit(data, av);
	exit(exit_value);
}

void	free_exit(t_data *data, char **av)
{
	free_data(data);
	free(av);
	if (data->tempfd[0] != -1)
		close(data->tempfd[0]);
	if (data->tempfd[1] != -1)
		close(data->tempfd[1]);
}

t_builtin	create_builtin(char *name, int (*f)(char **, void *))
{
	t_builtin	new;

	new.name = ft_strdup(name);
	new.fct = f;
	return (new);
}

int	init_builtin(t_data *data)
{
	data->builtin_tab[0] = create_builtin("echo", &ft_echo);
	data->builtin_tab[1] = create_builtin("cd", &ft_cd);
	data->builtin_tab[2] = create_builtin("pwd", &ft_pwd);
	data->builtin_tab[3] = create_builtin("export", &ft_export);
	data->builtin_tab[4] = create_builtin("unset", &ft_unset);
	data->builtin_tab[5] = create_builtin("env", &ft_env);
	data->builtin_tab[6] = create_builtin("exit", &ft_exit);
	return (1);
}
