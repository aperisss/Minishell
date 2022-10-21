/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis <aperis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 19:54:07 by ppajot            #+#    #+#             */
/*   Updated: 2022/09/21 20:08:29 by aperis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_name(char *str, int unset)
{
	int	i;

	i = -1;
	if (ft_isdigit(str[0]) || str[0] == '=' || *str == 0)
		return (0);
	while (str[++i] && (str[i] != '=' || unset))
	{
		if (!unset && str[i] == '+' && str[i + 1] && str[i + 1] == '=')
			return (1);
		if (ft_isalnum(str[i]) == 0)
			return (0);
	}	
	return (1);
}

void	export_op(t_data *data, int i, char *av)
{
	char	*str;

	if (av[i - 1] == '+')
	{
		av[i - 1] = 0;
		str = ft_strjoin(ft_getenv(av, data->envp), (av) + i + 1, "");
		put_env(av, str, 1, data);
		free(str);
	}
	else
	{
		av[i] = 0;
		put_env(av, av + i + 1, 1, data);
	}
}

int	export_no_declare(char **av, t_data *data)
{
	int	i;
	int	res;

	res = 0;
	while (1)
	{
		av++;
		if (!(*av))
			break ;
		if (!check_name(*av, 0))
		{
			res = 1;
			write (2, *av, ft_strlen(*av));
			write (2, ": not a valid identifier\n", 26);
			continue ;
		}
		i = 0;
		while ((*av)[i] && (*av)[i] != '=')
			i++;
		if ((*av)[i] == 0)
			continue ;
		export_op(data, i, *av);
	}
	return (res);
}

int	ft_export(char **av, void *arg)
{
	t_data	*data;
	int		res;

	data = arg;
	if (!av[1])
		return (put_declare(data), 0);
	res = export_no_declare(av, data);
	return (res);
}

int	ft_unset(char **av, void *arg)
{
	t_data	*data;
	int		res;

	res = 0;
	data = arg;
	while (1)
	{
		av++;
		if (!(*av))
			break ;
		if (!check_name(*av, 1))
		{
			res = 1;
			write (2, *av, ft_strlen(*av));
			write (2, ": not a valid identifier\n", 26);
			continue ;
		}
		remove_entry(*av, &data->envp);
	}
	return (res);
}
