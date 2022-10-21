/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis <aperis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 20:46:19 by ppajot            #+#    #+#             */
/*   Updated: 2022/09/21 19:55:24 by aperis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_quote(char *str)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (*str == '\"')
			count++;
		str++;
	}
	return (count);
}

char	*fill_export_quote(char *value, char *str)
{
	int	i;
	int	diff;

	i = 0;
	diff = 0;
	while (value[i])
	{
		if (value[i] == '\"')
		{
			str[i + diff] = '\\';
			diff++;
		}
		str [i + diff] = value[i];
		i++;
	}
	return (str);
}

void	put_value_backslash(char *value, t_data *data)
{
	int		i;
	char	*str;

	i = count_quote(value);
	if (i == 0)
	{
		write_protect(value, data, -1);
		return ;
	}	
	str = ft_calloc((i + ft_strlen(value) + 1), sizeof(char));
	str = fill_export_quote(value, str);
	write_protect(str, data, -1);
	free(str);
}

void	put_declare(t_data *data)
{
	t_dict	*entry;
	t_list	*current;

	current = data->envp;
	while (current)
	{
		entry = current->content;
		if (ft_strcmp(entry->name, "_"))
		{
			write_protect("declare -x ", data, -1);
			write_protect(entry->name, data, -1);
			write_protect("=\"", data, -1);
			put_value_backslash(entry->value, data);
			write_protect("\"\n", data, -1);
		}
		current = current->next;
	}
}

void	write_protect(char *str, t_data *data, int len)
{
	if (len < 0)
		len = ft_strlen(str);
	if (write(1, str, len) < 0)
		exit_error(1, data, -1, "");
}
