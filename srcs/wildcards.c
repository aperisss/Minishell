/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppajot <ppajot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 20:16:11 by aperis            #+#    #+#             */
/*   Updated: 2022/09/20 22:43:05 by ppajot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_str_wild(char *str, t_wild *w)
{
	int		i;
	int		j;
	char	*str_wild;

	i = 0;
	j = w->k;
	str_wild = NULL;
	while (str[j] && !wc_is_unquote(str, w->k))
	{
		j++;
		i++;
	}
	free(w->str_wild);
	str_wild = malloc(sizeof(char) * i + 1);
	if (!str_wild)
		exit (-1);
	i = 0;
	while (!wc_is_unquote(str, w->k) && str[w->k])
		str_wild[i++] = str[(w->k)++];
	str_wild[i] = '\0';
	str_wild = reduce_quote(str_wild);
	return (str_wild);
}

int	str_wild_chr(char *str_wild, char *file, int *k)
{
	int	i;

	i = 0;
	while (file[*k])
	{
		if (str_wild[i] == file[(*k)])
		{
			i++;
			if (!str_wild[i])
				return (1);
		}
		else
			i = 0;
		(*k)++;
	}
	return (0);
}

char	**wildcards(char *str, t_data *data)
{
	char	**file;
	int		mode;

	mode = 0;
	if (str[0] == '.')
		mode += 2;
	if (str[ft_strlen(str) - 1] == '/')
		mode += 1;
	file = read_dir(data, mode);
	file = get_wildcards(file, str, data);
	return (file);
}

int	after_wildcards(t_wild *w, char **file, char *str)
{
	if (only_wildcards(str, w->k) != 0 && w->j == 0)
	{
		w->wild = ft_strjoin2(w->wild, file[w->i]);
		return (1);
	}
	if (wc_is_unquote(str, w->k))
	{
		while (wc_is_unquote(str, w->k))
			w->k++;
	}
	if (str[w->k])
		w->str_wild = get_str_wild(str, w);
	return (0);
}

char	**get_wildcards(char **file, char *str, t_data *d)
{
	init_wild(&(d->w));
	while (file[d->w.i])
	{
		while (file[d->w.i][++d->w.j])
		{
			if (after_wildcards(&(d->w), file, str) == 1)
				break ;
			if (ft_strncmp(d->w.str_wild, file[d->w.i],
					ft_strlen(d->w.str_wild)) != 0
				&& d->w.j == 0 && str[0] != '*')
				break ;
			if (str_wild_chr(d->w.str_wild, file[d->w.i], &(d->w.j)) == 0)
				break ;
			if (only_wildcards(str, d->w.k) == 1 || (!str[d->w.k]
					&& !file[d->w.i][d->w.j + 1]))
			{
				d->w.wild = ft_strjoin2(d->w.wild, file[d->w.i]);
				break ;
			}
		}
		reinit_wildcards(&(d->w));
	}
	free(d->w.str_wild);
	d->ret = return_wildcards(file, d->w.wild);
	return (free_array(file), free(d->w.wild), d->ret);
}
