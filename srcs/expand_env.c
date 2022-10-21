/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis <aperis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 19:02:35 by ppajot            #+#    #+#             */
/*   Updated: 2022/09/21 18:30:31 by aperis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	neg_quote_dollar(char *str, int pos_neg)
{
	while (*str)
	{
		if (*str == '\'' * pos_neg || *str == '\"' * pos_neg
			|| *str == '$' * pos_neg)
			*str *= -1;
		str++;
	}
}

void	fill_name(char *name, char *str, int i, int *j)
{
	while (ft_isalnum(str[i + (*j)]) || str[i + (*j)] == '_')
	{
		name[(*j)] = str[i + (*j)];
		(*j)++;
	}
}

char	*replace_env(char **str, int i, t_data *data)
{
	char	*name;
	char	*value;
	char	*res;
	int		j;

	j = 0;
	name = ft_calloc(ft_strlen(*str) + 1, sizeof(char));
	if ((*str)[i + j] == '?')
		name[0] = '?';
	if ((*str)[i + j] == '?')
		j++;
	else if ((*str)[i + j] == 0)
		return ((*str));
	else
		fill_name(name, *str, i, &j);
	value = ft_getenv(name, data->envp);
	neg_quote_dollar(value, 1);
	(*str)[i - 1] = 0;
	res = ft_strjoin((*str), (*str) + i + j, value);
	if (ft_strcmp(name, "?") == 0)
		free(value);
	free(*str);
	if (!res)
		exit_error(0, data, -1, 0);
	return (free(name), res);
}

char	*expand_env(char *str, t_data *data)
{
	int		quote;
	int		i;

	i = -1;
	quote = 0;
	while (str[++i])
	{
		if ((str[i] == '\'' && quote != 2) || (str[i] == '\"' && quote != 1))
		{
			if (str[i] == '\'')
				quote = quote + 1 % 2;
			else if (str[i] == '\"')
				quote = quote + 2 % 4;
		}
		if (quote != 1 && str[i] == '$' && str[i + 1]
			&& !(quote == 2 && str[i + 1] == '\"'))
		{
			str = replace_env(&str, ++i, data);
			i -= 2;
			continue ;
		}
		if (!str[i])
			break ;
	}
	return (str);
}

int	expand_here_doc(int here_doc_data, t_data *data)
{
	int		hd_pipe[2];
	char	*str;
	int		here_doc_fd;

	here_doc_fd = data->hd_pfd[(here_doc_data & 0x00ffff00) >> 8][0];
	if (here_doc_data & (1 << 24))
		return (here_doc_fd);
	pipe(hd_pipe);
	str = get_next_line(here_doc_fd);
	while (str)
	{
		str = expand_env(str, data);
		write (hd_pipe[1], str, ft_strlen(str));
		free(str);
		str = get_next_line(here_doc_fd);
	}
	close(hd_pipe[1]);
	close(here_doc_fd);
	return (hd_pipe[0]);
}
