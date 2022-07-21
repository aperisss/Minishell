/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperis <aperis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 13:39:17 by aperis            #+#    #+#             */
/*   Updated: 2022/07/06 12:54:20 by aperis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strchr2( char d, char c)
{	
	if (c == d)
		return (0);
	return (1);
}

int	ft_lenword(char const *str, char c)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (ft_strchr2(str[i], c) == 1)
		{
			len++;
			i++;
		}
		else
			break ;
	}
	return (len);
}

char	*ft_strdup2(char const *src, char c)
{
	int		i;
	char	*dest;
	int		len;

	i = 0;
	len = ft_lenword(src, c);
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (0);
	while (src[i] && i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	ft_countword(char const *str, char c)
{
	int	nbrword;
	int	i;

	nbrword = 0;
	i = 0;
	while (str[i])
	{
		if ((ft_strchr2(str[i], c) == 1) && (i == 0))
		{
			nbrword++;
			i++;
		}
		if ((ft_strchr2(str[i], c) == 1) && (ft_strchr2(str[i - 1], c) != 1))
			nbrword++;
		i++;
	}
	return (nbrword);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		nbrword;
	char	**tab;

	i = 0;
	nbrword = ft_countword(s, c);
	tab = malloc(sizeof(char *) * (nbrword + 1));
	if (!tab)
		return (NULL);
	while (*s)
	{
		if (ft_strchr2(*s, c) == 1)
		{
			tab[i] = ft_strdup2(s, c);
			if (tab[i] == NULL)
				return (NULL);
			i++;
			s += ft_lenword(s, c);
		}
		else
			s++;
	}
	tab[i] = NULL;
	return (tab);
}
