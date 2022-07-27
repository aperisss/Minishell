/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppajot <ppajot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 13:51:02 by ppajot            #+#    #+#             */
/*   Updated: 2022/05/04 12:56:54 by ppajot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

size_t	countword(char const *s, char c)
{
	size_t	count;
	int		i;

	i = 0;
	count = 0;
	while (s[i])
	{
		if ((s[i] != c && i == 0) || (s[i] != c && s[i - 1] == c))
			count++;
		i++;
	}
	return (count);
}

size_t	nextword(char const *s, char c, size_t begin)
{
	while (s[begin] && s[begin] != c)
		begin++;
	while (s[begin] && s[begin] == c)
		begin++;
	return (begin);
}

char	*fillword(char const *s, char *str, size_t begin, size_t end)
{
	size_t	j;

	j = 0;
	while (j < end)
	{
		str[j] = s[begin + j];
		j++;
	}
	str[j] = 0;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	size_t	end;
	size_t	word;
	size_t	start;

	res = (char **)malloc((countword(s, c) + 1) * sizeof(char *));
	if (!res)
		return (0);
	res[countword(s, c)] = 0;
	start = 0;
	while (s[start] && s[start] == c)
		start++;
	word = 0;
	while (s[start])
	{
		end = 0;
		while (s[start + end] && s[start + end] != c)
			end++;
		res[word] = (char *)malloc(end + 1);
		res[word] = fillword(s, res[word], start, end);
		start = nextword(s, c, start);
		word++;
	}
	return (res);
}
/*
int	main(int argc, char **argv)
{
	int i;
	char **test;

	test = ft_split(argv[1], ' ');
	i = 0;
	while (test[i])
	{
		printf(" word[%i] = %s\n", i , test[i]);
		free(test[i]);
		i++;
	}
	free(test);
}*/