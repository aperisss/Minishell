/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppajot <ppajot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 16:46:47 by aperis            #+#    #+#             */
/*   Updated: 2022/09/20 22:43:31 by ppajot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	only_wildcards(char *str, int k)
{
	while (str[k])
	{
		if (!wc_is_unquote(str, k))
			return (0);
		k++;
	}
	if (wc_is_unquote(str, k - 1))
		return (1);
	return (2);
}

int	wc_is_unquote(char *str, int n)
{
	int	i;
	int	quote;

	quote = 0;
	i = -1;
	while (str[++i])
	{
		if ((str[i] == '\'' || str[i] == - '\'') && quote % '\'' == 0)
			quote = '\'' - quote;
		if ((str[i] == '\"' || str[i] == - '\"') && quote % '\"' == 0)
			quote = '\"' - quote;
		if (!quote && str[i] == '*' && i == n)
			return (1);
	}
	return (0);
}

char	*ft_strjoin2(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*dest;

	i = -1;
	j = 0;
	if (!s1)
	{
		s1 = malloc(sizeof(char));
		if (!s1)
			exit (-1);
		s1[0] = '\0';
	}
	dest = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!dest)
		exit (-1);
	while (s1[++i])
		dest[i] = s1[i];
	dest[i++] = - '/';
	while (s2[j])
		dest[i++] = s2[j++];
	dest[i] = '\0';
	free(s1);
	return (dest);
}

char	**return_wildcards(char **file, char *str)
{
	if (str)
	{
		str++;
		file = ft_split(str, - '/');
		if (!file)
			exit (-1);
	}
	else
		file = 0;
	return (file);
}

void	reinit_wildcards(t_wild *w)
{
	w->i++;
	w->j = -1;
	w->k = 0;
}
